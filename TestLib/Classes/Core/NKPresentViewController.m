//
//  NKPresentViewController.m
//  TestLibExample
//
//  Created by 聂康 on 2020/9/9.
//  Copyright © 2020 com.nk. All rights reserved.
//

#import "NKPresentViewController.h"
#import <MTFramework/MTFramework.h>

@interface NKPresentViewController ()

@end

@implementation NKPresentViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor redColor];
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    btn.frame = CGRectMake(100, 100, 100, 100);
    [btn setTitle:@"返回" forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [btn addTarget:self action:@selector(dimiss) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:btn];
}

- (void)viewDidAppear:(BOOL)animated {
    [MTUtils showMessage];
}

- (void)dimiss {
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
