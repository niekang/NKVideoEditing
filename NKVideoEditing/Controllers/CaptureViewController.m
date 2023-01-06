//
//  CaptureViewController.m
//  NKVideoEditing
//
//  Created by niekang on 2022/8/30.
//

#import "CaptureViewController.h"
#import "NKVideoCapture.h"

@interface CaptureViewController ()

@property(nonatomic, strong)NKVideoCapture *capture;

@property (weak, nonatomic) IBOutlet UIView *bottomToolView;

@property (weak, nonatomic) IBOutlet UIView *captureFinishView;

@end

@implementation CaptureViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.capture = [[NKVideoCapture alloc] init];
    self.capture.preview.backgroundColor = UIColor.blackColor;
    self.capture.preview.frame = self.view.bounds;
    self.capture.previewSize = self.view.frame.size;
    [self.view insertSubview:self.capture.preview atIndex:0];
    
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.capture start];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self.capture stop];
}

- (IBAction)captureAction:(UIButton *)sender {
    self.bottomToolView.hidden = YES;
    self.captureFinishView.hidden = NO;
    [self.capture stop];
}

- (IBAction)cancelAction:(UIButton *)sender {
    self.bottomToolView.hidden = NO;
    self.captureFinishView.hidden = YES;
    [self.capture start];
}

@end
