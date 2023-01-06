//
//  BaseAVVideoCompositionCoreAnimationTool.h
//  NKVideoEditing
//
//  Created by niekang on 2022/8/26.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BaseAVVideoCompositionCoreAnimationTool : NSObject

- (AVVideoCompositionCoreAnimationTool *)animationToolWithVideoComposition:(AVVideoComposition *)videoComposition composition:(AVComposition *)composition;

@end

NS_ASSUME_NONNULL_END
