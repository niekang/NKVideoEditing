//
//  NKVideoEncoder.h
//  NKVideoEditing
//
//  Created by niekang on 2022/8/29.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "NKVideoEncoderConfig.h"

NS_ASSUME_NONNULL_BEGIN

@interface NKVideoEncoder : NSObject

@property(nonatomic, strong)NKVideoEncoderConfig *config;

- (void)encodeVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)reset;

@end

NS_ASSUME_NONNULL_END
