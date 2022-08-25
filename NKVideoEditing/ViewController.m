//
//  ViewController.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/25.
//

#import "ViewController.h"
#import "NKVideoTool.h"

#define kMergeFileURL [NSURL fileURLWithPath:[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES).firstObject stringByAppendingString:@"/merge.mp4"]]

@interface ViewController ()

@property(nonatomic, strong)AVPlayer *player;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    NSURL *lolURL = [[NSBundle mainBundle] URLForResource:@"lol" withExtension:@"mp4"];
    AVAsset *lolAsset = [AVAsset assetWithURL:lolURL];
    NSURL *dogURL = [[NSBundle mainBundle] URLForResource:@"dog" withExtension:@"mp4"];
    AVAsset *dogAsset = [AVAsset assetWithURL:dogURL];
    [self mergeVideo:@[lolAsset, dogAsset]];
}

- (void)play {
    self.player = [AVPlayer playerWithPlayerItem:[AVPlayerItem playerItemWithURL:kMergeFileURL]];
    AVPlayerLayer *playerLayer = [AVPlayerLayer playerLayerWithPlayer:self.player];
    playerLayer.frame = self.view.bounds;
    playerLayer.videoGravity = AVLayerVideoGravityResizeAspect;
    [self.view.layer addSublayer:playerLayer];
    [self.player play];
}

- (void)mergeVideo:(NSArray <AVAsset *> *)assets {
    [NKVideoTool mergeAssets:assets toURL:kMergeFileURL completionHandler:^(BOOL success, NSError * _Nonnull error) {
        if (success) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self play];
            });
        }
    }];
   
}

@end
