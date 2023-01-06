//
//  GPUCameraViewController.m
//  NKVideoEditing
//
//  Created by niekang on 2022/9/16.
//

#import "GPUCameraViewController.h"
#import <GPUImage/GPUImage.h>

@interface GPUCameraViewController ()<GPUImageVideoCameraDelegate, GPUImageMovieWriterDelegate> {
    GPUImageVideoCamera *camera;
    GPUImageFilterGroup *filterGroup;
    GPUImageNormalBlendFilter *blendFilter;
    GPUImageMovieWriter *movieWriter;
    NSMutableArray *files;
    BOOL isRecording;
}

@property (weak, nonatomic) IBOutlet UIButton *recordBtn;

@end

@implementation GPUCameraViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.recordBtn.layer.borderColor = UIColor.redColor.CGColor;
    self.recordBtn.layer.borderWidth = 3;
    files = [NSMutableArray array];
    [self initCamera];
}

- (void)initCamera {
    camera = [[GPUImageVideoCamera alloc] initWithSessionPreset:AVCaptureSessionPreset1280x720 cameraPosition:AVCaptureDevicePositionFront];
    camera.delegate = self;
    camera.outputImageOrientation = UIInterfaceOrientationPortrait;
    [camera addAudioInputsAndOutputs];
    camera.horizontallyMirrorFrontFacingCamera = YES;
    camera.horizontallyMirrorRearFacingCamera = NO;
    

    filterGroup = [[GPUImageFilterGroup alloc] init];
    [camera addTarget:filterGroup];

    // 磨皮滤镜-- 双边模糊--
    GPUImageBilateralFilter *bilateralFilter = [[GPUImageBilateralFilter alloc] init];
    // 模糊度数值越大越不模糊,默认值是8大于1
    bilateralFilter.distanceNormalizationFactor = 8;
    [self addFilter:bilateralFilter];
    
    // 美白滤镜-- 亮度 亮度：调整亮度（-1.0 - 1.0，默认为0.0）
    GPUImageBrightnessFilter *brightnessFilter = [[GPUImageBrightnessFilter alloc] init];
    brightnessFilter.brightness = 0;
    [self addFilter:brightnessFilter];
    
    UIView* watermarkView = [[UIView alloc] initWithFrame:self.view.bounds];
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(20, 40, 180, 30)];
    label.text = @"com.nk";
    label.textColor = [UIColor whiteColor];
    label.textAlignment = NSTextAlignmentCenter;
    label.font = [UIFont systemFontOfSize:20 weight:UIFontWeightBold];
    [watermarkView addSubview:label];
    
    
    blendFilter = [[GPUImageNormalBlendFilter alloc] init];
    [filterGroup addTarget:blendFilter];

    GPUImageUIElement *uiElement = [[GPUImageUIElement alloc] initWithView:watermarkView];
    [uiElement addTarget:blendFilter];
    
    __block GPUImageUIElement *blockUIElement = uiElement;
    [filterGroup setFrameProcessingCompletionBlock:^(GPUImageOutput *, CMTime) {
        [blockUIElement update];
    }];
    
    
    [blendFilter addTarget:(GPUImageView *)self.view];
    [camera startCameraCapture];

}

- (void)addFilter:(GPUImageOutput<GPUImageInput> *)filter {
    [filterGroup addFilter:filter];
    NSInteger count = filterGroup.filterCount;
    if (count == 1) {
        filterGroup.initialFilters = @[filter];
    }else {
        [filterGroup.terminalFilter addTarget:filter];
    }
    filterGroup.terminalFilter = filter;
}

#pragma mark - Action
- (IBAction)changeCameraPosition:(UIButton *)sender {
    [camera rotateCamera];
}

- (IBAction)flashAction:(UIButton *)sender {
    sender.selected = !sender.selected;
    if (sender.selected) {
        [sender setImage:[UIImage imageNamed:@"camera_flash"] forState:UIControlStateSelected];
    }else {
        [sender setImage:[UIImage imageNamed:@"camera_flash_close"] forState:UIControlStateNormal];
    }
    if ([camera.inputCamera lockForConfiguration:nil]) {
        [camera.inputCamera setTorchMode:sender.selected ? AVCaptureTorchModeOn : AVCaptureTorchModeOff];
        [camera.inputCamera unlockForConfiguration];
    }
}
- (IBAction)recordAction:(UIButton *)sender {
    if (isRecording) {
        [sender.layer removeAnimationForKey:@"scale"];
        [movieWriter finishRecording];
        [filterGroup removeTarget:movieWriter];
    }else {
        static NSInteger index = 0;
        NSString *pathToMovie = [NSHomeDirectory() stringByAppendingPathComponent:[NSString stringWithFormat:@"Documents/Movie_%zd.m4v", index]];
        index += 1;
        unlink([pathToMovie UTF8String]); // If a file already exists, AVAssetWriter won't let you record new frames, so delete the old movie
        NSURL *movieURL = [NSURL fileURLWithPath:pathToMovie];
        movieWriter = [[GPUImageMovieWriter alloc] initWithMovieURL:movieURL size:CGSizeMake(720.0, 1280.0)];
        movieWriter.encodingLiveVideo = YES;
        movieWriter.delegate = self;
        
        [blendFilter addTarget:movieWriter];
        [movieWriter startRecording];
    }
    
    isRecording = !isRecording;
}

#pragma mark - GPUImageVideoCameraDelegate
- (void)willOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer {
    NSLog(@"%@",sampleBuffer);
}

#pragma mark - GPUImageMovieWriterDelegate
- (void)movieRecordingCompleted {
    [files addObject:movieWriter.assetWriter.outputURL];
}

- (void)movieRecordingFailedWithError:(NSError *)error {
    
}

@end
