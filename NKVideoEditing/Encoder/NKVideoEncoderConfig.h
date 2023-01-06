//
//  NKVideoEncoderConfig.h
//  NKVideoEditing
//
//  Created by niekang on 2022/8/29.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NKVideoEncoderConfig : NSObject

@property (nonatomic, assign) NSInteger width;//可选，系统支持的分辨率，采集分辨率的宽
@property (nonatomic, assign) NSInteger height;//可选，系统支持的分辨率，采集分辨率的高
@property (nonatomic, assign) NSInteger bitrate;//码率，自由设置
@property (nonatomic, assign) NSInteger fps;//自由设置 25

@property (nonatomic, strong) NSString *filePath; //编码文件路径

@end

NS_ASSUME_NONNULL_END
