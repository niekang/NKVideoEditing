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
#import "MGCAdConst.h"

@class MGCAdBean;
@class MGCAdConfig;
@class MGCAdController;
@class MGCApiVideoAdController;
@class MGCSdkVideoAdController;
@class MGCSdkBannerAdController;
@class MGCApiBannerAdController;

@interface MGCAdManager : NSObject

// 当前激活的api广告配置, 第一优先
@property (nonatomic, strong, nullable) MGCAdConfig* activeApiAdConfig;

// 当前激活的sdk广告配置, 如果api广告没有或者失败, 使用它
@property (nonatomic, strong, nullable) MGCAdConfig* activeSdkAdConfig;
/**当前激活的广告配置,有可能是sdk的也有可能是api的*/
@property (nonatomic, strong,nullable) MGCAdConfig *activeAdConfig;


// 所有的广告配置
@property (nonatomic, strong, nonnull) NSMutableArray<MGCAdConfig*>* adConfigs;

// singleton
+ (instancetype __nonnull)getInstance;
- (void)loadAdConfig;
- (void)loadAdConfig2;

// has config for a ad platform
- (BOOL)hasAdConfig:(NSString* __nonnull)platform;

// get config for a platform
- (MGCAdConfig* __nullable)getAdConfig:(NSString* __nonnull)platform;

// 初始化某个第三方sdk广告平台
- (BOOL)initAdPlatform:(NSString* __nonnull)plt withAppId:(NSString* __nonnull)appId;

// 获取缺省视频广告, 其返回的是adview的格式
- (void)getDefaultVideoAd:(MGCAdCallback __nonnull)cb;

// 为sdk广告创建控制器
- (MGCSdkVideoAdController* __nullable)createSdkVideoControllerForPlatform:(NSString* __nonnull)plt;

// 为api广告创建控制器
- (MGCApiVideoAdController* __nonnull)createApiVideoControllerForBean:(MGCAdBean* __nonnull)bean;

/**为sdk banner广告创建控制器*/
- (MGCSdkBannerAdController * __nullable)createSdkBannerControllerForPlatform:(NSString * __nonnull)plt bean:(MGCAdBean * __nonnull)bean;

/**为api banner广告创建控制器*/
- (MGCApiBannerAdController * __nonnull)createApiBannerControllerForBean:(MGCAdBean * __nonnull)bean;

- (void)confirmActiveConfigWithAdType:(MGCAdType)adType;
/**记录当前广告展示的次数*/
- (void)recordCurAdShowTimeWithPlatform:(NSString *__nullable)platform adType:(MGCAdType)adType;
- (MGCAdConfig *__nullable)nextAdConfig:(MGCAdConfig *__nullable)curAdConfig;



@end
