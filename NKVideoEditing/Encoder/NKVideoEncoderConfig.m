//
//  NKVideoEncoderConfig.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/29.
//

#import "NKVideoEncoderConfig.h"

@implementation NKVideoEncoderConfig

- (instancetype)init {
    self = [super init];
    if (self) {
        self.width = 480;
        self.height = 640;
        self.bitrate = 640*1000;
        self.fps = 25;
        self.filePath = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES).firstObject stringByAppendingFormat:@"/encode.avc"];
    }
    return self;
}

@end
