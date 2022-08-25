//
//  NKVideoTool.h
//  NKVideoEditing
//
//  Created by niekang on 2022/8/25.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NKVideoTool : NSObject

+ (AVMutableComposition *)mergeAssets:(NSArray <AVAsset *>*)assets;

+ (void)mergeAssets:(NSArray <AVAsset *>*)assets toURL:(NSURL *)url completionHandler:(void(^)(BOOL success, NSError *error))completionHandler;

@end

NS_ASSUME_NONNULL_END
