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
    [[NSFileManager defaultManager] removeItemAtURL:url error:nil];
    AVAssetExportSession *exportSession = [AVAssetExportSession exportSessionWithAsset:composition presetName:AVAssetExportPresetPassthrough];
    exportSession.outputFileType = AVFileTypeMPEG4;
    exportSession.outputURL = url;
    exportSession.shouldOptimizeForNetworkUse = YES;
    [exportSession exportAsynchronouslyWithCompletionHandler:^{
        if (exportSession.status == AVAssetExportSessionStatusCompleted) {
            if (completionHandler) {
                completionHandler(YES, nil);
            }
        }else if (exportSession.status == AVAssetExportSessionStatusFailed) {
            if (completionHandler) {
                completionHandler(NO, exportSession.error);
            }
        }
    }];
}

@end
