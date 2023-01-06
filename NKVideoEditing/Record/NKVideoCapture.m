//
//  NKVideoRecoder.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/29.
//

#import "NKVideoCapture.h"
#import <AVFoundation/AVFoundation.h>
#import "NKVideoEncoder.h"

@interface NKVideoCapture ()<AVCaptureVideoDataOutputSampleBufferDelegate, AVCaptureAudioDataOutputSampleBufferDelegate> 

@property(nonatomic, strong)AVCaptureSession *session;
@property(nonatomic, strong)AVCaptureVideoPreviewLayer *previewLayer;
@property(nonatomic, assign)AVCaptureDevicePosition position;
@property(nonatomic, copy)AVCaptureSessionPreset preset;

@property(nonatomic, strong)AVCaptureDeviceInput *videoInput;
@property(nonatomic, strong)AVCaptureVideoDataOutput *videoOutput;
@property(nonatomic, strong)AVCaptureConnection *videoConnection;

@property(nonatomic, strong)AVCaptureDeviceInput *audioInput;
@property(nonatomic, strong)AVCaptureAudioDataOutput *audioOutput;
@property(nonatomic, strong)AVCaptureConnection *audioConnection;

@property(nonatomic, strong)dispatch_queue_t captureQueue;

@property(nonatomic, assign)BOOL isRunning;

@property(nonatomic, strong)NKVideoEncoder *encoder;


@end

@implementation NKVideoCapture

- (instancetype)init {
    self = [super init];
    if (self) {
        self.position = AVCaptureDevicePositionBack;
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidBecomeActiveNotification) name:UIApplicationDidBecomeActiveNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillResignActiveNotification) name:UIApplicationWillResignActiveNotification object:nil];
        [self setupVideoRecorder];
        [self setupAudioRecorder];
        [self setupPreviewLayer];
    }
    return self;
}

- (void)setupVideoRecorder {
    AVCaptureDeviceDiscoverySession *disecoverySession = [AVCaptureDeviceDiscoverySession discoverySessionWithDeviceTypes:@[AVCaptureDeviceTypeBuiltInDualCamera] mediaType:AVMediaTypeVideo position:self.position];
    NSArray<AVCaptureDevice *> *devices = disecoverySession.devices;
    AVCaptureDevice *captureDevice;
    for (AVCaptureDevice *device in devices) {
        if (device.position == self.position) {
            captureDevice = device;
            break;
        }
    }
    self.videoInput = [AVCaptureDeviceInput deviceInputWithDevice:captureDevice error:nil];
    self.videoOutput = [[AVCaptureVideoDataOutput alloc] init];
    [self.videoOutput setSampleBufferDelegate:self queue:self.captureQueue];
    [self.videoOutput setAlwaysDiscardsLateVideoFrames:YES];
    [self.videoOutput setVideoSettings:@{(__bridge  NSString *)kCVPixelBufferPixelFormatTypeKey:@(kCVPixelFormatType_420YpCbCr8BiPlanarFullRange)}];
    [self.session beginConfiguration];
    [self.session addInput:self.videoInput];
    [self.session addOutput:self.videoOutput];
    [self.session setSessionPreset:self.preset];
    [self.session commitConfiguration];
    self.videoConnection = [self.videoOutput connectionWithMediaType:AVMediaTypeVideo];
    self.videoConnection.videoOrientation = AVCaptureVideoOrientationPortrait;
    [self setFPS:25];
    [self setupPreviewLayer];
}

- (void)setupAudioRecorder {
    AVCaptureDevice *audioDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeAudio];
    self.audioInput = [AVCaptureDeviceInput deviceInputWithDevice:audioDevice error:nil];
    self.audioOutput = [[AVCaptureAudioDataOutput alloc] init];
    [self.audioOutput setSampleBufferDelegate:self queue:self.captureQueue];
    [self.session beginConfiguration];
    [self.session addInput:self.audioInput];
    [self.session addOutput:self.audioOutput];
    [self.session commitConfiguration];
    self.audioConnection = [self.audioOutput connectionWithMediaType:AVMediaTypeAudio];
}

- (void)setupPreviewLayer {
    self.previewLayer.frame = CGRectMake(0, 0, self.previewSize.width, self.previewSize.height);
    [self.preview.layer addSublayer:self.previewLayer];
}

- (void)setFPS:(int)fps {
    AVCaptureDevice *device = self.videoInput.device;
    // 当前支持的最大fps
    float maxRate = [[device.activeFormat.videoSupportedFrameRateRanges firstObject] maxFrameRate];
    // 为了确保帧速率恒定，可以将最小与最大的帧时长设置成一样的值
    if (maxRate > fps && [device lockForConfiguration:NULL]) {
        device.activeVideoMinFrameDuration = CMTimeMake(1, fps);
        device.activeVideoMaxFrameDuration = device.activeVideoMinFrameDuration;
        [device unlockForConfiguration];
    }
}

- (void)applicationDidBecomeActiveNotification {
    [self start];
}

- (void)applicationWillResignActiveNotification {
    [self stop];
}

#pragma mark - Public
- (void)start {
    NSAssert(!CGSizeEqualToSize(self.previewSize, CGSizeZero), @"previewSize must be set");
    NSAssert(!CGRectEqualToRect(self.preview.frame, CGRectZero), @"preview size must be set");
    if (self.isRunning) {
        return;
    }
    self.isRunning = YES;
    [self.session startRunning];
}

- (void)stop {
    if (!self.isRunning) {
        return;
    }
    self.isRunning = NO;
    [self.session stopRunning];
}

#pragma mark - Setter
- (void)setPreviewSize:(CGSize)previewSize {
    _previewSize = previewSize;
    self.previewLayer.frame = CGRectMake(0, 0, _previewSize.width, _previewSize.height);
}

#pragma mark - Getter
- (AVCaptureSession *)session {
    if (!_session) {
        _session = [[AVCaptureSession alloc] init];
    }
    return _session;
}

- (UIView *)preview {
    if (!_preview) {
        _preview = [[UIView alloc] init];
    }
    return _preview;
}

- (AVCaptureVideoPreviewLayer *)previewLayer {
    if (!_previewLayer) {
        _previewLayer = [AVCaptureVideoPreviewLayer layerWithSession:self.session];
    }
    return _previewLayer;
}

- (dispatch_queue_t)captureQueue {
    if (!_captureQueue) {
        _captureQueue = dispatch_queue_create("com.nk.video.capture.queue", DISPATCH_QUEUE_SERIAL);
    }
    return _captureQueue;
}

- (AVCaptureSessionPreset)preset {
    if (!_preset) {
        if ([self.session canSetSessionPreset:AVCaptureSessionPreset1920x1080]) {
            _preset = AVCaptureSessionPreset1920x1080;
        }else if ([self.session canSetSessionPreset:AVCaptureSessionPreset1280x720]){
            _preset = AVCaptureSessionPreset1280x720;
        }else {
            _preset = AVCaptureSessionPreset640x480;
        }
    }
    return _preset;
}

- (NKVideoEncoder *)encoder {
    if (!_encoder) {
        _encoder = [[NKVideoEncoder alloc] init];
    }
    return _encoder;
}

#pragma mark - AVCaptureVideoDataOutputSampleBufferDelegate, AVCaptureAudioDataOutputSampleBufferDelegate
- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    if (connection == self.audioConnection) {
        
    }else if (connection == self.videoConnection) {
        // 创建CompressionSession对象,该对象用于对画面进行编码
        // kCMVideoCodecType_H264 : 表示使用h.264进行编码
        // didCompressH264 : 当一次编码结束会在该函数进行回调,可以在该函数中将数据,写入文件中
        [self.encoder encodeVideoSampleBuffer:sampleBuffer];
    }
}


@end
