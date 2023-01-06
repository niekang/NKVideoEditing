//
//  NKVideoTool.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/25.
//

#import "NKVideoTool.h"

@implementation NKVideoTool

+ (AVMutableComposition *)mergeAssets:(NSArray<AVAsset *> *)assets {
    AVMutableComposition *composition = [AVMutableComposition composition];
    AVMutableCompositionTrack *videoCompositionTrack = [composition addMutableTrackWithMediaType:AVMediaTypeVideo preferredTrackID:kCMPersistentTrackID_Invalid];
    AVMutableCompositionTrack *audioCompositionTrack = [composition addMutableTrackWithMediaType:AVMediaTypeAudio preferredTrackID:kCMPersistentTrackID_Invalid];
    CMTime time = kCMTimeZero;
    for (AVAsset *asset in assets) {
        NSArray <AVAssetTrack *>* videoTracks = [asset tracksWithMediaType:AVMediaTypeVideo];
        NSArray <AVAssetTrack *>* audioTracks = [asset tracksWithMediaType:AVMediaTypeAudio];
        AVAssetTrack *videoTrack = videoTracks.firstObject;
        AVAssetTrack *audioTrack = audioTracks.firstObject;
        [videoCompositionTrack insertTimeRange:CMTimeRangeMake(kCMTimeZero, asset.duration) ofTrack:videoTrack atTime:time error:nil];
        [audioCompositionTrack insertTimeRange:CMTimeRangeMake(kCMTimeZero, asset.duration) ofTrack:audioTrack atTime:time error:nil];
        time = CMTimeAdd(time, asset.duration);
    }
    return composition;
}

+ (void)mergeAssets:(NSArray<AVAsset *> *)assets toURL:(NSURL *)url completionHandler:(nonnull void (^)(BOOL, NSError * _Nonnull))completionHandler{
    AVMutableComposition *composition = [self mergeAssets:assets];
    AVAssetExportSession *exportSession = [AVAssetExportSession exportSessionWithAsset:composition presetName:AVAssetExportPresetPassthrough];
    [self export:exportSession toURL:url completionHandler:completionHandler];
}

+ (void)addWatermarkForAsset:(AVAsset *)asset
               animationTool:(nonnull BaseAVVideoCompositionCoreAnimationTool *)animationTool
                       toURL:(nonnull NSURL *)url
           completionHandler:(nonnull void (^)(BOOL, NSError * _Nonnull))completionHandler{
    AVMutableComposition *composition = [AVMutableComposition composition];
    
    [composition insertTimeRange:CMTimeRangeMake(kCMTimeZero, asset.duration) ofAsset:asset atTime:kCMTimeZero error:nil];
    AVMutableCompositionTrack *videoCompositionTrack = [composition tracksWithMediaType:AVMediaTypeVideo].firstObject;
    CGAffineTransform transform = videoCompositionTrack.preferredTransform;
    CGSize size = videoCompositionTrack.naturalSize;
    NKVideoOrientation orientation = [self orientaionForAssetTrack:videoCompositionTrack];
    switch (orientation) {
        case NKVideoOrientationPortrait:
        {
            transform = CGAffineTransformMakeTranslation(size.height, 0);
            transform = CGAffineTransformRotate(transform, M_PI/2.0);
            break;
        }
        case NKVideoOrientationLandscapeLeft:
        {
            transform = CGAffineTransformMakeTranslation(size.width, size.height);
            transform = CGAffineTransformRotate(transform, M_PI);
            break;
        }
        case NKVideoOrientationPortraitUpsideDown:
        {
            transform = CGAffineTransformMakeTranslation(0, size.width);
            transform = CGAffineTransformRotate(transform, M_PI/2*3);
            break;
        }
        default:
            break;
    }
        
    AVMutableVideoCompositionInstruction *instruction = [AVMutableVideoCompositionInstruction videoCompositionInstruction];
    instruction.timeRange = CMTimeRangeMake(kCMTimeZero, asset.duration);
    

    AVMutableVideoCompositionLayerInstruction *layerInstruction = [AVMutableVideoCompositionLayerInstruction videoCompositionLayerInstructionWithAssetTrack:videoCompositionTrack];
    
    [layerInstruction setTransform:transform atTime:kCMTimeZero];

    instruction.layerInstructions = @[layerInstruction];
    
    AVMutableVideoComposition *videoComposition = [AVMutableVideoComposition videoComposition];
    videoComposition.renderSize = videoCompositionTrack.naturalSize;
    videoComposition.instructions = @[instruction];
    videoComposition.frameDuration = CMTimeMake(1, 30);
    videoComposition.animationTool = [animationTool animationToolWithVideoComposition:videoComposition composition:composition];

    AVAssetExportSession *exportSession = [AVAssetExportSession exportSessionWithAsset:composition presetName:AVAssetExportPresetHighestQuality];
    exportSession.videoComposition = videoComposition;
    [self export:exportSession toURL:url completionHandler:completionHandler];
}

+ (void)useMusic:(AVAsset *)asset toAsset:(AVAsset *)toAsset toURL:(nonnull NSURL *)url completionHandler:(nonnull void (^)(BOOL, NSError * _Nonnull))completionHandler{
    AVMutableComposition *composition = [AVMutableComposition composition];
    AVMutableCompositionTrack *videoTrack = [composition addMutableTrackWithMediaType:AVMediaTypeVideo preferredTrackID:kCMPersistentTrackID_Invalid];
    AVMutableCompositionTrack *audioTrack = [composition addMutableTrackWithMediaType:AVMediaTypeAudio preferredTrackID:kCMPersistentTrackID_Invalid];
    [videoTrack insertTimeRange:CMTimeRangeMake(kCMTimeZero, toAsset.duration) ofTrack:[toAsset tracksWithMediaType:AVMediaTypeVideo].firstObject atTime:kCMTimeZero error:nil];
    [audioTrack insertTimeRange:CMTimeRangeMake(kCMTimeZero, asset.duration) ofTrack:[asset tracksWithMediaType:AVMediaTypeAudio].firstObject atTime:kCMTimeZero error:nil];
    AVAssetExportSession *exportSession = [AVAssetExportSession exportSessionWithAsset:composition presetName:AVAssetExportPresetPassthrough];
    [self export:exportSession toURL:url completionHandler:completionHandler];
}

+ (void)export:(AVAssetExportSession *)exportSession toURL:(NSURL *)url completionHandler:(void(^)(BOOL, NSError *))completionHandler{
    [[NSFileManager defaultManager] removeItemAtURL:url error:nil];
//    [exportSession determineCompatibleFileTypesWithCompletionHandler:^(NSArray<AVFileType> * _Nonnull compatibleFileTypes) {
//        NSLog(@"%@",compatibleFileTypes);
//    }];
    exportSession.outputFileType = AVFileTypeMPEG4;
    exportSession.outputURL = url;
    exportSession.shouldOptimizeForNetworkUse = YES;
    [exportSession exportAsynchronouslyWithCompletionHandler:^{
        if (exportSession.status == AVAssetExportSessionStatusCompleted) {
            if (completionHandler) {
                completionHandler(YES, nil);
            }
        }else if (exportSession.status == AVAssetExportSessionStatusFailed) {
            NSLog(@"%@", exportSession.error);
            if (completionHandler) {
                completionHandler(NO, exportSession.error);
            }
        }
    }];
}

+ (NKVideoOrientation)orientaionForAssetTrack:(AVAssetTrack *)assetTrack {
    NKVideoOrientation orientation = NKVideoOrientationLandscapeRight;
    CGAffineTransform t = assetTrack.preferredTransform;
    if (t.a == 0 && t.b == 1.0 && t.c == -1 && t.d == 0) {
        orientation = NKVideoOrientationPortrait;
    } else if (t.a == 0 && t.b == -1.0 && t.c == 1.0 && t.d == 0) {
        orientation = NKVideoOrientationPortraitUpsideDown;
    } else if (t.a == 1.0 && t.b == 0 && t.c == 0 && t.d == 1.0) {
        orientation = NKVideoOrientationLandscapeRight;
    } else if (t.a == -1.0 && t.b == 0 && t.c == 0 && t.d == -1.0) {
        orientation = NKVideoOrientationLandscapeLeft;
    }
    return orientation;
}

@end
