//
//  FFMEncoder.h
//  NKVideoEditing
//
//  Created by niekang on 2022/9/1.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "NKVideoEncoderConfig.h"

NS_ASSUME_NONNULL_BEGIN

@interface FFMEncoder : NSObject

- (instancetype)initWithConfig:(NKVideoEncoderConfig *)config;

- (void)encodeVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

@end

NS_ASSUME_NONNULL_END
