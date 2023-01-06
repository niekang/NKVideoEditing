//
//  ViewController.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/25.
//

#import "ViewController.h"
#import "NKVideoTool.h"
#import "TestVideoCompositionCoreAnimationTool.h"
#import "SubtitleAnimationTool.h"
#import "NKVideoCapture.h"
#import "avformat.h"

#define kMergeFileURL [NSURL fileURLWithPath:[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES).firstObject stringByAppendingString:@"/merge.mp4"]]
#define kWatermarkFileURL [NSURL fileURLWithPath:[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES).firstObject stringByAppendingString:@"/watermark.mp4"]]
#define kUseMusicFileURL [NSURL fileURLWithPath:[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES).firstObject stringByAppendingString:@"/samemusic.mp4"]]



@interface ViewController ()

@property(nonatomic, strong)AVPlayer *player;
@property(nonatomic, strong)NKVideoCapture *capture;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationController.navigationBar.hidden = YES;
            
}

- (void)testRecord {
    self.capture = [[NKVideoCapture alloc] init];
    self.capture.preview.backgroundColor = UIColor.blackColor;
    self.capture.preview.frame = self.view.bounds;
    self.capture.previewSize = self.view.frame.size;
    [self.view addSubview:self.capture.preview];
    [self.capture start];
}

- (void)testVideo {
    NSURL *lolURL = [[NSBundle mainBundle] URLForResource:@"lol" withExtension:@"mp4"];
    AVAsset *lolAsset = [AVAsset assetWithURL:lolURL];
    NSURL *dogURL = [[NSBundle mainBundle] URLForResource:@"dog" withExtension:@"mp4"];
    AVAsset *dogAsset = [AVAsset assetWithURL:dogURL];
//    [self mergeVideo:@[lolAsset, dogAsset]];
    [self addWatermark:lolAsset];
//    [self userMusic:dogAsset toAsset:lolAsset];
}

- (void)play:(NSURL *)url {
    self.player = [AVPlayer playerWithPlayerItem:[AVPlayerItem playerItemWithURL:url]];
    AVPlayerLayer *playerLayer = [AVPlayerLayer playerLayerWithPlayer:self.player];
    playerLayer.backgroundColor = UIColor.clearColor.CGColor;
    playerLayer.frame = self.view.bounds;
    playerLayer.videoGravity = AVLayerVideoGravityResizeAspect;
    [self.view.layer addSublayer:playerLayer];
    [self.player play];
}

- (void)mergeVideo:(NSArray <AVAsset *> *)assets {
    [NKVideoTool mergeAssets:assets
                       toURL:kMergeFileURL
           completionHandler:^(BOOL success, NSError * _Nonnull error) {
        if (success) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self play:kMergeFileURL];
            });
        }
    }];
   
}

- (void)addWatermark:(AVAsset *)asset {
    [NKVideoTool addWatermarkForAsset:asset
                        animationTool:[SubtitleAnimationTool new]
                                toURL:kWatermarkFileURL
                    completionHandler:^(BOOL success, NSError * _Nonnull error) {
        if (success) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self play:kWatermarkFileURL];
            });
        }
    }];
}

- (void)userMusic:(AVAsset *)asset toAsset:(AVAsset *)toAsset {
    [NKVideoTool useMusic:asset toAsset:toAsset toURL:kUseMusicFileURL completionHandler:^(BOOL success, NSError * _Nonnull error) {
        if (success) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self play:kUseMusicFileURL];
            });
        }
    }];
}

@end
