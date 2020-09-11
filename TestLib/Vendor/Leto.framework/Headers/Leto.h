//
// Copyright (c) 2017, ledong.com
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "WDHodoer.h"
#import "MGCMiniGameApi.h"
#import "LJBaseViewController.h"
#import "MGCMiniGameTool.h"
#import "LJJumpDataCacheManager.h"
#import "LJSmallGameItemListModel.h"
#import "MGCAdConst.h"
#import "MGCSdkAdPlatformInterface.h"
//#import "MGCSdkAdManager.h"
#ifdef MGCCoinSystemMark
#import "MGCGameCenterMineViewController.h"
#import "MGCFavoritesAlertView.h"

#endif

#import "MGCWebView.h"

#import "LJBaseNavigationController.h"

extern NSString * const menu_bar_close_click;//关闭按钮方法配置


@class WDHNavigationController;

@interface Leto : NSObject

/// 是否开启日志 默认开启
@property (class, nonatomic, assign) BOOL enableLog;

/// 是否支持pop手势返回 默认支持
@property (class, nonatomic, assign) BOOL enablePopGesture;

/**
 开启小程序

 @param appInfo 小程序配置信息
 @param completion 启动回调 success: YES:启动成功 NO:启动失败 msg:回调信息
 */
+ (void)startAppWithAppInfo:(WDHAppInfo *)appInfo entrance:(WDHNavigationController *)entrance completion:(void(^)(BOOL success, NSString *msg))completion zipFinish:(void(^)(BOOL isZipSuccess))zipFinish;

/**
 获取当前sdk版本号

 @return 当前sdk版本号
 */
+ (NSString *)sdkVersion;

// leto app lifecycle delegate
+ (void)applicationDidEnterBackground:(UIApplication *)application;
+ (void)applicationWillEnterForeground:(UIApplication *)application;

@end

