//
//  NKVideoTool.h
//  NKVideoEditing
//
//  Created by niekang on 2022/8/25.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "BaseAVVideoCompositionCoreAnimationTool.h"

typedef NS_ENUM(NSUInteger, NKVideoOrientation) {
    NKVideoOrientationLandscapeRight,
    NKVideoOrientationPortrait,
    NKVideoOrientationLandscapeLeft,
    NKVideoOrientationPortraitUpsideDown,
};

NS_ASSUME_NONNULL_BEGIN

@interface NKVideoTool : NSObject

+ (AVMutableComposition *)mergeAssets:(NSArray <AVAsset *>*)assets;

+ (void)mergeAssets:(NSArray <AVAsset *>*)assets toURL:(NSURL *)url completionHandler:(void(^)(BOOL success, NSError *error))completionHandler;

+ (void)addWatermarkForAsset:(AVAsset *)asset
               animationTool:(BaseAVVideoCompositionCoreAnimationTool *)animationTool
                       toURL:(NSURL *)url
           completionHandler:(void(^)(BOOL success, NSError *error))completionHandler;

+ (void)useMusic:(AVAsset *)asset toAsset:(AVAsset *)toAsset toURL:(NSURL *)url completionHandler:(void(^)(BOOL success, NSError *error))completionHandler;;

+ (NKVideoOrientation)orientaionForAssetTrack:(AVAssetTrack *)assetTrack;

@end

NS_ASSUME_NONNULL_END
