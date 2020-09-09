//
//  NKUtils.m
//  TestLibExample
//
//  Created by 聂康 on 2020/9/9.
//  Copyright © 2020 com.nk. All rights reserved.
//

#import "NKUtils.h"
#import "NKPresentViewController.h"

@implementation NKUtils

+ (void)presentViewController:(UIViewController *)vc {
    NKPresentViewController *presentVc = [[NKPresentViewController alloc] init];
    presentVc.modalPresentationStyle = UIModalPresentationFullScreen;
    [vc presentViewController:presentVc animated:true completion:nil];
}

@end
