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

#ifndef MGCSdkAdPlatformInterface_h
#define MGCSdkAdPlatformInterface_h

#import <Foundation/Foundation.h>
#import "MGCAdConst.h"

/**
 第三方sdk广告平台管理器需要实现的接口
 */
@protocol MGCSdkAdPlatformInterface

@optional
/**
 初始化sdk广告平台, 这里的appId并不是mgc的小游戏id, 只是取这么个名字, 每个平台可能有不同叫法, 比如
 百度叫publisherId等
 */
+ (void)configWithAppId:(NSString*)appId;

/**
 加载视频广告
 */
+ (void)loadVideoAdWithPosId:(NSString*)posId statusCallback:(MGCVideoAdStatusCallback)cb interactionCallback:(MGCAdInteractionCallback)cb2;

/**
 显示视频广告
 */
+ (void)showVideoAdInViewController:(UIViewController*)vc;
+ (void)showVideoAdInViewController:(UIViewController *)vc isHorShow:(BOOL)isHorShow;

/**显示banner广告*/
+ (void)showBannerAdInViewController:(UIViewController *)vc posId:(NSString *)posId statusCallback:(MGCBannerAdStatusCallBack)cb interactionCallback:(MGCAdInteractionCallback)cb2;

/**销毁banner广告*/
+ (void)destroyBannerAdFromSuperView:(UIView *)superView;

@end

#endif /* MGCSdkAdPlatformInterface_h */
