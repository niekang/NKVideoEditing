//
//  NKVideoEncoder.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/29.
//

#import "NKVideoEncoder.h"
#import <VideoToolbox/VideoToolbox.h>

@interface NKVideoEncoder (){
    int64_t _frameID;
    BOOL _hasSaveSpsPps;
}

@property (nonatomic) VTCompressionSessionRef encodeSesion;
@property (nonatomic, strong) dispatch_queue_t encodeQueue;
@property (nonatomic, strong) dispatch_queue_t callbackQueue;
@property (nonatomic, strong) NSFileHandle *fileHandle;

@end

@implementation NKVideoEncoder

- (NSFileHandle *)fileHandle {
    if (!_fileHandle) {
        [[NSFileManager defaultManager] removeItemAtPath:self.config.filePath error:nil];
        [[NSFileManager defaultManager] createFileAtPath:self.config.filePath contents:nil attributes: nil];
        _fileHandle = [NSFileHandle fileHandleForWritingAtPath:self.config.filePath];
    }
    return _fileHandle;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        self.config = [[NKVideoEncoderConfig alloc] init];
        self.encodeQueue = dispatch_queue_create("com.nk.encode.video.queue", DISPATCH_QUEUE_SERIAL);
        self.callbackQueue = dispatch_queue_create("com.nk.encode.video.callback.queue", DISPATCH_QUEUE_SERIAL);
        [self initCompressionSession];
    }
    return self;
}

- (void)initCompressionSession{
    // 创建CompressionSession对象,该对象用于对画面进行编码
    // kCMVideoCodecType_H264 : 表示使用h.264进行编码
    // didCompressH264 : 当一次编码结束会在该函数进行回调,可以在该函数中将数据,写入文件中
    OSStatus status = VTCompressionSessionCreate(kCFAllocatorDefault, (int32_t)self.config.width, (int32_t)self.config.height, kCMVideoCodecType_H264, NULL, NULL, NULL, videoEncodeCallback, (__bridge void * _Nullable)self, &_encodeSesion);
    if (status != noErr) {
        NSLog(@"VTCompressionSession create failed");
        return;
    }
    // 设置实时编码输出（直播必然是实时输出,否则会有延迟）
    status = VTSessionSetProperty(_encodeSesion, kVTCompressionPropertyKey_RealTime, kCFBooleanTrue);
    NSLog(@"VTSessionSetProperty: set kVTCompressionPropertyKey_RealTime status=%d", (int)status);

    //指定编码比特流的配置文件和级别。直播一般使用baseline，可减少由于b帧带来的延时%d(int)
    status = VTSessionSetProperty(_encodeSesion, kVTCompressionPropertyKey_ProfileLevel, kVTProfileLevel_H264_Baseline_AutoLevel);
    NSLog(@"VTSessionSetProperty: set kVTCompressionPropertyKey_ProfileLevel status=%d", (int)status);
    
    //设置码率均值
    //码率: 编码效率, 码率越高,则画面越清晰, 如果码率较低会引起马赛克,码率高有利于还原原始画面,但是也不利于传输
    CFNumberRef bit = (__bridge CFNumberRef)@(_config.bitrate);
    status = VTSessionSetProperty(_encodeSesion, kVTCompressionPropertyKey_AverageBitRate, bit);
    NSLog(@"VTSessionSetProperty: set kVTCompressionPropertyKey_AverageBitRate status=%d", (int)status);

    //码率限制(只在定时时起作用)
    CFArrayRef limits = (__bridge CFArrayRef)@[@(_config.bitrate / 4), @(_config.bitrate * 4)];
    status = VTSessionSetProperty(_encodeSesion, kVTCompressionPropertyKey_DataRateLimits, limits);
    NSLog(@"VTSessionSetProperty: set kVTCompressionPropertyKey_DataRateLimits status=%d", (int)status);
    
    //设置关键帧间隔(GOPSize)GOP太大图像会模糊
    CFNumberRef maxKeyFrameInterval = (__bridge CFNumberRef)@(_config.fps * 2);
    status = VTSessionSetProperty(_encodeSesion, kVTCompressionPropertyKey_MaxKeyFrameInterval, maxKeyFrameInterval);
    NSLog(@"VTSessionSetProperty: set kVTCompressionPropertyKey_MaxKeyFrameInterval status=%d", (int)status);

    //设置fps
    CFNumberRef expectedFrameRate = (__bridge CFNumberRef)@(_config.fps);
    status = VTSessionSetProperty(_encodeSesion, kVTCompressionPropertyKey_ExpectedFrameRate, expectedFrameRate);
    NSLog(@"VTSessionSetProperty: set kVTCompressionPropertyKey_MaxKeyFrameInterval status=%d", (int)status);

    status = VTCompressionSessionPrepareToEncodeFrames(_encodeSesion);
    NSLog(@"VTCompressionSessionPrepareToEncodeFrames: status=%d", (int)status);

}

- (void)encodeVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer {
    CFRetain(sampleBuffer);
    dispatch_async(self.encodeQueue, ^{
        // 帧数据，将sampleBuffer转成imageBuffer
        CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
        
        // 该帧的时间
        self->_frameID++;
        CMTime time = CMTimeMake(self->_frameID, 1000);
        
        // 持续时间
        CMTime duration = kCMTimeInvalid;
        
        // 编码
        VTEncodeInfoFlags flags;
        OSStatus status = VTCompressionSessionEncodeFrame(self.encodeSesion, imageBuffer, time, duration, NULL, NULL, &flags);
        if (status == kVTInvalidSessionErr) {
            self ->_frameID--;
            VTCompressionSessionInvalidate(self.encodeSesion);
            CFRelease(self.encodeSesion);
            [self initCompressionSession];
        }
        if (status != noErr) {
            NSLog(@"VTCompressionSession encode failed: status=%d",(int)status);
        }
        CFRelease(sampleBuffer);
    });
}

const Byte startCode[] = "\x00\x00\x00\x01";
void videoEncodeCallback(void * CM_NULLABLE outputCallbackRefCon,
                         void * CM_NULLABLE sourceFrameRefCon,
                         OSStatus status,
                         VTEncodeInfoFlags infoFlags,
                         CM_NULLABLE CMSampleBufferRef sampleBuffer) {
    
    if (status != noErr) {
        NSLog(@"VTCompressionSession encode callback:  status = %d", (int)status);
        return;
    }
    if (!CMSampleBufferDataIsReady(sampleBuffer)) {
        NSLog(@"VTCompressionSession encode callback: sampleBuffer data is not ready");
        return;
    }
    // 根据传入的参数获取对象
    NKVideoEncoder *encoder = (__bridge NKVideoEncoder *)outputCallbackRefCon;
    NSUInteger length = sizeof(startCode) - 1;
    
    // 判断是否为关键帧
    BOOL isKeyFrame = NO;
    CFArrayRef attachArray = CMSampleBufferGetSampleAttachmentsArray(sampleBuffer, true);
    isKeyFrame = !CFDictionaryContainsKey(CFArrayGetValueAtIndex(attachArray, 0), kCMSampleAttachmentKey_NotSync);
    // _hasSaveSpsPps 本地只需要在第一个I帧前出现，对于直播每个I帧前都应该插入sps,pps,因为直播时客户端进入的时间是不确定的
    if (isKeyFrame && !encoder->_hasSaveSpsPps) {
        // 获取编码后的信息（存储于CMFormatDescriptionRef中）
        CMFormatDescriptionRef formatDesc = CMSampleBufferGetFormatDescription(sampleBuffer);
        
        // 获取SPS信息
        const uint8_t *spsData;
        size_t spsSize, spsCount;
        OSStatus spsStatus = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(formatDesc, 0, &spsData, &spsSize, &spsCount, 0);

        
        // 获取PPS信息
        const uint8_t *ppsData;
        size_t ppsSize, ppsCount;
        OSStatus ppsStatus = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(formatDesc, 1, &ppsData, &ppsSize, &ppsCount, 0);
        
        if (spsStatus == noErr && ppsStatus == noErr) {
            // sps data
            NSMutableData *sps = [NSMutableData dataWithCapacity:length+spsSize];
            [sps appendBytes:startCode length:length];
            [sps appendBytes:spsData length:spsSize];
            
            // pps data
            NSMutableData *pps = [NSMutableData dataWithCapacity:length+ppsSize];
            [pps appendBytes:startCode length:length];
            [pps appendBytes:ppsData length:ppsSize];
            [encoder.fileHandle writeData:sps];
            [encoder.fileHandle writeData:pps];
            encoder->_hasSaveSpsPps = YES;
        }else {
            NSLog(@"VTCompressionSession: get sps/pps failed: status=%d", (int)status);
        }
    }
    
    // 获取NALU数据
    CMBlockBufferRef blockBuffer = CMSampleBufferGetDataBuffer(sampleBuffer);
    
    size_t lengthAtOffset, totalLength;
    char *dataPointer;
    
    status = CMBlockBufferGetDataPointer(blockBuffer, 0, &lengthAtOffset, &totalLength, &dataPointer);
    if (status != kCMBlockBufferNoErr) {
        NSLog(@"VTCompressionSession: get data pointer failed: status=%d", (int)status);
        return;
    }
    
    //循环获取NALU数据
    size_t offset = 0;
    // 帧长度
    // 返回的nalu数据前四个字节并不是0001的startcode，而是大端模式的帧长度length
    const int AVCCHeaderLength = 4;
    while (offset < totalLength - AVCCHeaderLength) {
        uint32_t naluLength = 0;
        //获取nalu 数据长度
        memcpy(&naluLength, dataPointer+offset, AVCCHeaderLength);
        //大端转系统端
        naluLength = CFSwapInt32BigToHost(naluLength);
        //获取到编码好的视频数据
        NSMutableData *data = [NSMutableData dataWithCapacity:4+naluLength];
        [data appendBytes:startCode length:length];
        [data appendBytes:dataPointer+offset+AVCCHeaderLength length:naluLength];
        
        [encoder.fileHandle writeData:data];
        
        offset += AVCCHeaderLength + naluLength;
    }
    
    NSLog(@"%llu", encoder.fileHandle.offsetInFile);
}

- (void)reset {
    [self.fileHandle closeFile];
    self.fileHandle = nil;
    _hasSaveSpsPps = NO;
    _frameID = 0;
}

@end
