//
//  SubtitleAnimationTool.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/26.
//

#import "SubtitleAnimationTool.h"

@implementation SubtitleAnimationTool

- (AVVideoCompositionCoreAnimationTool *)animationToolWithVideoComposition:(AVVideoComposition *)videoComposition composition:(nonnull AVComposition *)composition{
    
    CALayer *parentLayer = [CALayer layer];
    parentLayer.frame = CGRectMake(0, 0, composition.naturalSize.width, videoComposition.renderSize.height);
    parentLayer.backgroundColor = UIColor.greenColor.CGColor;
    
    CALayer *videoLayer = [CALayer layer];
    videoLayer.frame = parentLayer.bounds;
    
    [parentLayer addSublayer:videoLayer];

    CGRect frame = CGRectMake(0, 0, composition.naturalSize.width, 60);
    CGFloat duraton = composition.duration.value/composition.duration.timescale;
    for (int i=0; i<floorl(duraton); i++) {
        CATextLayer *layer = [CATextLayer layer];
        layer.frame = frame;
        layer.alignmentMode = kCAAlignmentCenter;
        layer.fontSize = 16;
        layer.string = [NSString stringWithFormat:@"这是第%d条弹幕", i];
        layer.foregroundColor = [UIColor greenColor].CGColor;
        layer.opacity = 0;
        
        CABasicAnimation *opacityAnim = [CABasicAnimation animationWithKeyPath:@"opacity"];
        opacityAnim.fromValue = [NSNumber numberWithFloat:1];
        opacityAnim.toValue = [NSNumber numberWithFloat:1];
        opacityAnim.beginTime = AVCoreAnimationBeginTimeAtZero;
        opacityAnim.duration = 1;
        opacityAnim.removedOnCompletion = NO;
        
        CABasicAnimation *opacityAnim1 = [CABasicAnimation animationWithKeyPath:@"opacity"];
        opacityAnim1.fromValue = [NSNumber numberWithFloat:1];
        opacityAnim1.toValue = [NSNumber numberWithFloat:0];
        opacityAnim1.beginTime = 0.1;
        opacityAnim.duration = 0.1;
        opacityAnim.removedOnCompletion = NO;

        CAAnimationGroup *groupAnima = [CAAnimationGroup animation];
        if(i==0) {
            groupAnima.beginTime = AVCoreAnimationBeginTimeAtZero;
        }else {
            groupAnima.beginTime = 1.1 * i;
        }
        groupAnima.duration = 1.1;
        groupAnima.animations = @[opacityAnim, opacityAnim1];
        groupAnima.removedOnCompletion = NO;
        
        [layer addAnimation:groupAnima forKey:nil];
        [parentLayer addSublayer:layer];
    }
    
    return [AVVideoCompositionCoreAnimationTool videoCompositionCoreAnimationToolWithPostProcessingAsVideoLayer:videoLayer inLayer:parentLayer];
}

@end
