//
//  FFMEncoder.m
//  NKVideoEditing
//
//  Created by niekang on 2022/9/1.
//

#import "FFMEncoder.h"
#import "avformat.h"
#import <CoreMotion/CoreMotion.h>

@interface FFMEncoder (){
    int64_t _frameID;
}

@property(nonatomic, strong)NKVideoEncoderConfig *config;
@property (nonatomic, strong) dispatch_queue_t encodeQueue;
@property (nonatomic, strong) dispatch_queue_t callbackQueue;
@property(nonatomic)AVFormatContext *avFormatContext;
@property(nonatomic)AVOutputFormat *avOutputFormat;
@property(nonatomic)AVStream *stream;
@property(nonatomic)AVCodecParameters *codecCtx;

@end

@implementation FFMEncoder

- (instancetype)initWithConfig:(NKVideoEncoderConfig *)config {
    self = [super init];
    if (self) {
        _frameID = 0;
        self.config = config;
        self.encodeQueue = dispatch_queue_create("com.nk.encode.video.queue", DISPATCH_QUEUE_SERIAL);
        self.callbackQueue = dispatch_queue_create("com.nk.encode.video.callback.queue", DISPATCH_QUEUE_SERIAL);
        [self setupCoder];
    }
    return self;
}

- (void)setupCoder{
    //注册FFmpeg所有编解码器(无论编码还是解码都需要该步骤)
    av_register_all();
    
    //初始化AVFormatContext: 用作之后写入视频帧并编码成 h264，贯穿整个工程当中(释放资源时需要销毁)
    _avFormatContext = avformat_alloc_context();
    
    //设置输出文件的路径
    const char *outfile = [self.config.filePath cStringUsingEncoding:NSUTF8StringEncoding];
    _avOutputFormat = av_guess_format(NULL, outfile, NULL);
    _avFormatContext->oformat = _avOutputFormat;
    
    //打开文件的缓冲区输入输出，flags 标识为  AVIO_FLAG_READ_WRITE ，可读写
    if (avio_open(&_avFormatContext->pb, outfile, AVIO_FLAG_READ_WRITE) < 0) {
        NSLog(@"FFMEncoder: failed to open output file!");
        return;
    }
    
    //创建新的输出流, 用于写入文件
    _stream = avformat_new_stream(_avFormatContext, 0);
    _stream->time_base.num = 1;
    _stream->time_base.den = 25;
    if (_stream == NULL) {
        NSLog(@"FFMEncoder: failed to create AVStream");
        return;
    }
    
    //用户存储编码所需的参数格式等等
    //从媒体流中获取到编码结构体，他们是一一对应的关系，一个 AVStream 对应一个  AVCodecContext
    _codecCtx = _stream->codecpar;
    
    //设置编码器的编码格式(是一个id)，每一个编码器都对应着自己的 id，例如 h264 的编码 id 就是 AV_CODEC_ID_H264
    _codecCtx->codec_id = _avOutputFormat->video_codec;
    
    //设置编码类型为 视频编码
    _codecCtx->codec_type = AVMEDIA_TYPE_VIDEO;

    //设置像素格式为 yuv 格式
    _codecCtx->format = AV_PIX_FMT_YUV420P;

    //设置视频的宽高
    _codecCtx->width = self.config.width;
    _codecCtx->height = self.config.height;

    //设置帧率
    

    //设置码率（比特率）
    _codecCtx->bit_rate = self.config.bitrate;
//
//    //视频质量度量标准(常见qmin=10, qmax=51)
//    _codecCtx->qmin = 10;
//    _codecCtx->qmax = 51;
//
//    //设置图像组层的大小(GOP-->两个I帧之间的间隔)
//    _codecCtx->level = 250;
//
//        // 9.10.设置 B 帧最大的数量，B帧为视频图片空间的前后预测帧， B 帧相对于 I、P 帧来说，压缩率比较大，也就是说相同码率的情况下，
//        // 越多 B 帧的视频，越清晰，现在很多打视频网站的高清视频，就是采用多编码 B 帧去提高清晰度，
//        // 但同时对于编解码的复杂度比较高，比较消耗性能与时间
//        pCodecCtx->max_b_frames = 5;
}

- (void)encodeVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer {
    
}

@end
