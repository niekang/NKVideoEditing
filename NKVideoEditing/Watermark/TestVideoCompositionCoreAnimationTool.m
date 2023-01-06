//
//  NKVideoCompositionCoreAnimationTool.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/26.
//

#import "TestVideoCompositionCoreAnimationTool.h"

@implementation TestVideoCompositionCoreAnimationTool

- (AVVideoCompositionCoreAnimationTool *)animationToolWithVideoComposition:(AVVideoComposition *)videoComposition composition:(nonnull AVComposition *)composition{
    CALayer *parentLayer = [CALayer layer];
    parentLayer.frame = CGRectMake(0, 0, composition.naturalSize.width, videoComposition.renderSize.height);
    parentLayer.backgroundColor = UIColor.greenColor.CGColor;
    
    CALayer *videoLayer = [CALayer layer];
    videoLayer.frame = parentLayer.bounds;
    
    CALayer *watermarkLayer = [CALayer layer];
    watermarkLayer.frame = CGRectMake(0, composition.naturalSize.height-200, 200, 200);
    
    CALayer *imageLayer = [CALayer layer];
    imageLayer.frame = watermarkLayer.bounds;
    imageLayer.contents = (id)[UIImage imageNamed:@"image1"].CGImage;

    CATextLayer *layer = [CATextLayer layer];
    layer.frame = watermarkLayer.bounds;
    layer.alignmentMode = kCAAlignmentCenter;
    layer.fontSize = 16;
    layer.string = @"niekang";
    layer.foregroundColor = [UIColor greenColor].CGColor;
    
    [watermarkLayer addSublayer:imageLayer];
    [watermarkLayer addSublayer:layer];

    [parentLayer addSublayer:videoLayer];
    [parentLayer addSublayer:watermarkLayer];

    AVVideoCompositionCoreAnimationTool *animationTool = [AVVideoCompositionCoreAnimationTool videoCompositionCoreAnimationToolWithPostProcessingAsVideoLayer:videoLayer inLayer:parentLayer];

    return animationTool;
}

@end
