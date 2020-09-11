//
//  MGCMiniGameApi.h
//  MgcMiniGame
//
//  Created by yuan yao on 2018/11/12.
//  Copyright © 2018年 yuan yao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "LJJumpDataCacheManager.h"
#import "MGCMiniGameConst.h"

/**
 * 自定义消息的监听器, 自定义消息由postMessage api触发. postMessage是mgc自定义api, 在
 * framework 2.5.8及之后版本支持
 */
@protocol MGCMessageDelegate
@optional
/**
 * 当js端的postMessage调用时, 该方法触发. data可能是NSString也可能是NSDictionary, 可能为nil
 */
//- (void)mgc_onMessageReceived:(NSString*)msg withData:(id)data;
/**当js端的postMessage调用时, 该方法触发. data可能是NSString也可能是NSDictionary, 可能为nil*/
- (void)mgc_onMessageReceived:(NSString*)msg withData:(id)data appId:(NSString *)appId;

@end

//@class WDHNavigationController;

@interface MGCMiniGameApi : NSObject


/**初始化sdk*/
+ (void)mgc_initSdkWithInfo:(NSDictionary *)infoDic;


/**跳转到小游戏
 param appId 如果zip包放在工程目录下就是zip包的名称
 param path zip的路径，如果在工程路径下 传“”
 vc 当前的控制器
 isHiddenBack 是否隐藏返回按钮 YES隐藏 NO不隐藏
 */
+ (void)mgc_jumpMiniGameWithAppId:(NSString *)appId path:(NSString *)path vc:(UIViewController *)vc isLandscape:(BOOL)isLandscape isHiddenBack:(BOOL)isHiddenBack __attribute__((deprecated("请使用[MGCMiniGameApi mgc_jumpMiniGameWithAppId:path:bindGameId:vc:isLandscape:isHiddenBack]")));
+ (void)mgc_jumpMiniGameWithAppId:(NSString *)appId path:(NSString *)path bindGameId:(NSString *)gameId vc:(UIViewController *)vc isLandscape:(BOOL)isLandscape isHiddenBack:(BOOL)isHiddenBack;
/**打开远程的小游戏
 param appId 游戏id
 param url 小游戏的下载链接
 vc 当前的导航控制器
 isHiddenBack 是否隐藏返回按钮 YES隐藏 NO不隐藏
 */

+ (void)mgc_jumpMiniGameWithAppId:(NSString *)appId url:(NSString *)url vc:(UIViewController *)vc isLandscape:(BOOL)isLandscape isHiddenBack:(BOOL)isHiddenBack;
/**通过appId直接打开游戏
 param appId 游戏id
 vc 当前的控制器
 */
+ (void)mgc_jumpMiniGameWithAppId:(NSString *)appId vc:(UIViewController *)vc;
/**
 通过appId打开游戏(带游戏场景)
 param appId 游戏id
 param vc  当前控制器
 param sceneType 游戏启动场景
 */
+ (void)mgc_jumpMiniGameWithAppId:(NSString *)appId vc:(UIViewController *)vc sceneType:(MgcMiniGameSceneType)sceneType;

/**更多游戏
 param vc 当前的控制器
 */
+ (void)mgc_moreGameWithVc:(UIViewController *)vc;
+ (void)mgc_pushMoreGameWithNa:(UINavigationController *)na;
/**登录
 param isSuccess YES成功 NO失败
 param code 状态码 200成功
 param message 返回的状态信息
 */
+ (void)mgc_loginWithStatusBlock:(LJLoginStatusBlock)statusBlock;
/**外部应用跳转到本地应用触发(兼容在应用内的跳转)
 param url
 */
+ (void)mgc_openUrl:(NSURL *)url;
/**外部应用跳转到本地应用触发(兼容在应用内的跳转)
 param url 游戏中心(mgcgame://mgc.com/gamecenter),
           跳转游戏mgcgame://mgc.com/game?id=364253&scene=FEED
             scene:
             DEFAULT,
             GAMECENTER,
             GAME,
             TAB,
             BANNER,
             FEED,
             CHAT,
             GUESS_YOU_LIKE,
             FAVORITE,
             PLAYED_LIST,
             CATEGORY_LIST,


 vc:当前控制器
 */
+ (void)mgc_openUrl:(NSURL *)url vc:(UIViewController *)vc;


/**设置昵称*/
+ (void)mgc_settingNickname:(NSString *)nickname result:(void(^)(BOOL isSuccess,NSString *message))result;
/**设置头像*/
+ (void)mgc_settingPortrait:(NSString *)portrait result:(void(^)(BOOL isSuccess,NSString *message,id data))result;
/**同步手机号*/
+ (void)mgc_syncAccountWithMobile:(NSString *)mobile result:(void(^)(BOOL isSuccess,NSString *message,NSString *memberId))result __attribute__((deprecated("请使用[MGCMiniGameApi mgc_syncInfo:result:]")));
/**获取sdk的版本号*/
+ (NSString *)mgc_version;
/**获取framework版本号(framework.zip是游戏引擎文件)*/
+ (NSString *)mgc_frameworkVersion;

/** get recent jump list for current user */
+ (NSArray<NSDictionary*>*)mgc_getRecentApps;

/** get favorite list for current user */
+ (NSArray<NSDictionary*>*)mgc_getFavorites;
/**cancel favorite*/
+ (void)mgc_cancelFavoriteWithAppId:(NSString *)appId result:(void(^)(BOOL isSuccess,NSString *msg))result;
/**add vavorite*/
+ (void)mgc_addFavoriteWithAppId:(NSString *)appId result:(void(^)(NSDictionary *gameInfo,BOOL isSuccess,NSString *msg))result;
/**清除缓存*/
+ (void)mgc_clearCache;

/**
 强行退出顶层app
 */
+ (void)mgc_forceCloseTopApp;

/**
 重启顶层app
 */
+ (void)mgc_resetTopApp;
/**
 设置第三方的userId,token
 */
+ (void)mgc_setThirdUserId:(NSString *)userId thirdToken:(NSString *)token;
/**
 清空第三方的数据
 */
+ (void)mgc_clearThirdInfo;
/**
 同步信息(不带token)
 mobile:手机号
 userid:用户id
 nickname:昵称
 portrait:头像
 result:结果回调
 mgc_userId 梦工厂的用户id

 */
+ (void)mgc_syncInfoWithMobile:(NSString *)mobile userid:(NSString *)userid nickname:(NSString *)nickname portrait:(NSString *)portrait result:(void(^)(BOOL isSuccess,NSString *message,NSString *mgc_userId))result __attribute__((deprecated("请使用[MGCMiniGameApi mgc_syncInfo:result:]")));
/**
 同步信息(不带token)
 syncInfo:{
 mgc_sync_mobile_key:@"",手机号
 mgc_sync_userid_key:@"",用户id
 mgc_sync_nickname_key:@"",昵称
 mgc_sync_portrait_key:@"",头像
 mgc_sync_loginsign_key:@"",//账号状态 1正式正好 2游客账号
 
 }
  result:结果回调
 message 回调信息
 mgc_userId 梦工厂的用户id
 */

+ (void)mgc_syncInfo:(NSDictionary<NSString *,NSString *> * (^)(void))syncInfo result:(void(^)(BOOL isSuccess,NSString *message,NSString *mgc_userId))result;
/**查看当前是否有游戏运行
 *YES 有游戏运行 NO没有游戏运行
 */
+ (BOOL)mgc_miniGameIsRuning;

/**
 同步信息(带token)
 result:结果回调
 mgc_userId 梦工厂的用户id
 */
+ (void)mgc_syncInfoWithToken:(NSString *)token isEncrypt:(BOOL)isEncrypt result:(void(^)(BOOL isSuccess,NSString *message,NSString *mgc_userId))result;

/**
 * 监听由postMessage触发的自定义消息, postMessage是mgc自定义api, 在
 * framework 2.5.8及之后版本支持.
 */
+ (void)mgc_onMessage:(NSString*)msg delegate:(id<MGCMessageDelegate>)delegate;

/**
 * 取消监听某自定义消息
 */
+ (void)msg_offMessage:(NSString*)msg;

/**
 * 派发postMessage触发的自定义消息
 */
+ (void)mgc_dispatchMessage:(NSString*)msg withData:(id)data;
/**
 *派发postMessage触发的自定义消息 带appId
 */
+ (void)mgc_dispatchMessage:(NSString*)msg withData:(id)data appId:(NSString *)appId;
/**注册回调*/
+ (void)mgc_registerCallBack:(id)callBack key:(NSString *)key;
/**判断有没有正式账号
 *有正式账号 返回YES
 */
+ (BOOL)mgc_checkAccount;
/**通知sdk已经签到*/
+ (void)mgc_notificeSigned;
/**发起签到的回调*/
+ (void)mgc_signCallWithStatus:(BOOL )status;
/**发起登录的回调*/
+ (void)mgc_loginCallWithStatus:(BOOL)status syncInfo:(NSDictionary<NSString *,NSString *> *(^)(void))syncInfo syncResult:(void(^)(BOOL isSyncSuccess,NSString *msg,NSString *mgc_userId))result;
/**发起提现的回调*/
+ (void)mgc_getCashCallWithStatus:(BOOL)status;
/**获取sdk模式*/
+ (void)mgc_getRunPattern:(void(^)(NSInteger runPattern))result;
/**获取sdk运行模式同步*/
+ (NSInteger)mgc_syncGetRunPattern;
/**获取屏幕类型*/
+ (MGCScreenType)mgc_getScreenType;
/**获取当前账号信息*/
+ (NSDictionary *)mgc_getCurrentAccountInfo;


@end
