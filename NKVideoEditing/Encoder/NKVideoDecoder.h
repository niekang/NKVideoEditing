//
//  NKVideoDecoder.h
//  NKVideoEditing
//
//  Created by niekang on 2022/8/30.
//

#import <Foundation/Foundation.h>
#import "NKVideoEncoderConfig.h"
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/**h264解码回调代理*/
@protocol NKVideoDecoderDelegate <NSObject>
//解码后H264数据回调
- (void)videoDecodeCallback:(CVPixelBufferRef)imageBuffer;
@end

@interface NKVideoDecoder : NSObject

@property(nonatomic, strong)NKVideoEncoderConfig *config;
@property (nonatomic, weak) id<NKVideoDecoderDelegate> delegate;

- (instancetype)initWithConfig:(NKVideoEncoderConfig *)config;

- (void)decodeNaluData:(NSData *)frame;

@end

NS_ASSUME_NONNULL_END
