//
//  ViewController.m
//  TestLibExample
//
//  Created by 聂康 on 2020/9/9.
//  Copyright © 2020 com.nk. All rights reserved.
//

#import "ViewController.h"
#import <TestLib/TestLib.h>
#import <MTFramework/MTFramework.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewDidAppear:(BOOL)animated {
    [NKUtils presentViewController:self];
}



@end
