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
#import "MGCMiniGameConst.h"
#import <UIKit/UIKit.h>

@class LJJumpConfig;

/**功能按钮的样式*/
typedef NS_ENUM(NSInteger,LetoMenuBarType)
{
	/**更多和返回都有*/
	LetoMenuBarType_All,
	/**只有返回*/
	LetoMenuBarType_Back,
	/**只有更多*/
	LetoMenuBarType_More,
	/**都没有*/
	LetoMenuBarType_None,
};

@class WDHAppInfo;
@protocol WDHAppMenuDelegate

@optional

- (void)wdhAppMenuMoreDidSelected:(WDHAppInfo*)info;

@end

@interface WDHAppInfo : NSObject

@property (nonatomic, copy) NSString *appId;

@property (nonatomic, copy) NSString *userId;

@property (nonatomic, copy) NSString *appPath;

/**游戏zip的下载地址*/
@property (nonatomic, copy) NSString *packageUrl;
/**分享说明*/
@property (nonatomic, copy) NSString *share_msg;
/**分享链接*/
@property (nonatomic, copy) NSString *share_url;
/**分享标题*/
@property (nonatomic, copy) NSString *share_title;
/**是否显示猜你喜欢*/
@property (nonatomic, assign) BOOL isShowGuessYouLike;
/**是否显示微信分享*/
@property (nonatomic, assign) BOOL isWeXinShare;

/**菜单的显示样式*/
@property (nonatomic, assign) LetoMenuBarType menuBarType;

/** menu action delegate */
@property (nonatomic, weak) id<WDHAppMenuDelegate> menuDelegate;
/**游戏名字*/
@property (nonatomic, copy) NSString *appName;
/**分享图标*/
@property (nonatomic, copy) NSString *share_icon;
/**版本号*/
@property (nonatomic, copy) NSString *version;
/**游戏的启动场景*/
@property (nonatomic, assign) MgcMiniGameSceneType scene_type;
/**上报需要的ckey*/
@property (nonatomic, copy) NSString *ckey;
/**启动游戏的控制器*/
@property (nonatomic, weak) UIViewController *curVC;
/**是否显示收藏*/
@property (nonatomic, assign) BOOL isShowCollection;


/**当前游戏的控制器*/
@property (nonatomic, weak) UIViewController *curGameVC;

@property (nonatomic, strong) LJJumpConfig *jumpConfig;
@end


