//
//  MGCMiniGameTool.h
//  Leto
//
//  Created by yuan yao on 2019/2/23.
//  Copyright © 2019 ledong. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger,MGCPlayVideoScene) {
    /**普通*/
    MGCPlayVideoScene_Normal = 0,
    /**拆红包*/
    MGCPlayVideoScene_Red = 1,
};


@class LJSmallGameItemListModel;

@interface MGCMiniGameTool : NSObject


+ (UIImage *)lj_imageWithColor:(UIColor *)color;
+ (void)lj_setImageWithView:(UIImageView *)imageView url:(NSString *)url placeHoldImage:(UIImage *_Nullable)plaImage;
+ (void)lj_setImageWithView:(UIImageView *)imageView url:(NSString *)url  sizeBlock:(void(^)(CGSize imageSize))block;
+ (void)lj_setBackgroundImageWithBtn:(UIButton *)btn url:(NSString *)url forState:(UIControlState)state;
+ (void)lj_setBackgroundImageWithBtn:(UIButton *)btn url:(NSString *)url placeholderImage:(UIImage *)placeholderImage forState:(UIControlState)state;
+ (NSArray<NSDictionary*>*)getRecentJumps;
+ (NSArray<NSDictionary*>*)getLocalFavorites;
+ (void)lj_accordingGameInfoToStart:(LJSmallGameItemListModel *)model vc:(UIViewController *)vc sceneType:(MgcMiniGameSceneType)sceneType;

/*获取是否登录*/
+ (BOOL)lj_getIsLogin;
/** 0>image在上，label在下
   1>image在左，label在右
   2>image在下，label在上
   3>image在右，label在左
 */
+ (void)lj_setImageStyleWithBtn:(UIButton *)btn style:(NSInteger)style imageTitleSpace:(CGFloat)space;

+ (void)lj_headerWithView:(UIScrollView *)view block:(void(^)(void))block;
+ (void)lj_headerEndRefreshWithView:(UIScrollView *)view;
+ (void)lj_headerBeginRefreshWithView:(UIScrollView *)view;
+ (void)lj_footerWithView:(UIScrollView *)view block:(void(^)(void))block;
+ (void)lj_footerEndRefreshWithView:(UIScrollView *)view;
+ (void)lj_footerDestroyFromView:(UIScrollView *)view;


+ (NSArray *)lj_objectArrayWithKeyValuesArray:(NSArray *)arr model:(Class)model;
+ (id)lj_objectWithKeyValues:(NSDictionary *)dic model:(Class)model;



+ (void)lj_showBoxWithMessage:(NSString *)message;

+ (NSDictionary *)lj_getCommonParams;
+ (NSDictionary *)lj_getPayCommonParams;
+ (NSDictionary *)lj_getSimpleCommonParams;
+ (NSString *)lj_getCompletedUrl:(NSString *)url;
+ (NSString *)mgc_mobile;

/*
 //没有加载游戏
 0  LJSDKUseType_NoLoad,
 //加载本地游戏
 1 LJSDKUseType_Local,
 //加载远程游戏
 2 LJSDKUseType_Remote,

 */
+ (void)lj_jumpLocalMiniGameWithNa:(UINavigationController *)na;
+ (void)lj_jumpRemoteMiniGameWithNa:(UINavigationController *)na;

+ (void)lj_hideNoNetViewFromView:(UIView *)view;
+ (void)lj_showNoNetViewFromView:(UIView *)view retryBlock:(void(^)(void))block;
+ (void)lj_hideNoDataViewFromView:(UIView *)view;
+ (void)lj_showNoDataViewWithTitle:(NSString *)title fromView:(UIView *)view;


+ (UIViewController *)lj_loginWithIsLandscape:(BOOL)isLandscape status:(void(^)(BOOL isSuccess))status;

+ (void)lj_openGameWithGameId:(NSString *)gameId packageurl:(NSString *)packageurl isLandscape:(BOOL)isLandscape splash:(NSString *)splash verson:(NSString *)version isShowMore:(BOOL)isShowMore conUrl:(NSString *)conUrl isKpAd:(BOOL)isShowKpAd shareMsg:(NSString *)shareMsg shareUrl:(NSString *)shareUrl tags:(NSArray *)tags iconUrl:(NSString *)iconUrl publicity:(NSString *)publicity name:(NSString *)name na:(UINavigationController *)na;
+ (void)lj_openH5GameWithName:(NSString *)name isLandscape:(BOOL)isLandscape packageurl:(NSString *)packageurl gameId:(NSString *)gameId splash:(NSString *)splash isKpAd:(BOOL)isShowKpAd na:(UINavigationController *)na;
+ (void)lj_openWebWithName:(NSString *)name packageurl:(NSString *)packageurl gameId:(NSString *)gameId splash:(NSString *)splash isKpAd:(BOOL)isShowKpAd na:(UINavigationController *)na;
/*
 从上到下
0> LJGradientTypeTopToBottom,
1>从左到右
LJGradientTypeLeftToRight,
2>从左上到右下
LJGradientTypeUpLeftToLowRight,
3>从右上到左下
LJGradientTypeUpRightToLowLeft

 */
+ (UIImage *)lj_gradientColorImageFromColors:(NSArray *)colors type:(NSInteger)type size:(CGSize)size;

+ (BOOL)lj_isShowAd;

+ (void)lj_showBox;
+ (void)lj_dismisBox;
+ (void)lj_showBoxWithDes:(NSString *)des;
+ (NSMutableAttributedString *)lj_frontText:(NSString *)frText frColor:(UIColor *)frColor frCusFont:(UIFont *)frCusFont backText:(NSString *)backText baColor:(UIColor *)baColor baCusFont:(UIFont *)baCusFont parBlock:( void(^__nullable)(NSMutableParagraphStyle *__nullable parStyle))parBlock;
+ (NSString *)lj_jsonStrWithDic:(NSDictionary *)dic;
+ (NSString *)lj_jsonWithData:(id)data;
+ (id)lj_JSONObjectWithStr:(NSString *)str;
+ (NSString *)lj_getMD5WithStr:(NSString *)str;
+ (NSString *)lj_getMicroTimestamp;
+ (NSData *)lj_dataWithBase64EncodedWithStr:(NSString *)str;

+ (void)lj_requestWithUrl:(NSString *)url param:(NSDictionary *)param success:(void(^)(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject))success fail:(void(^)(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error))fail;
+ (void)lj_requestForGetWithUrl:(NSString *)url param:(NSDictionary *)param success:(void(^)(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject))success fail:(void(^)(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error))fail;

+ (void)lj_RequestForGetWithUrl:(NSString *)url param:(NSDictionary *)param handler:(void(^)(id data,BOOL isSuccessed,NSString *code,NSString *message))handler;
+ (void)lj_RequestForPostWithUrl:(NSString *)url param:(NSDictionary *)param handler:(void(^)(id data,BOOL isSuccessed,NSString *code,NSString *message))handler;
+ (void)lj_cancelFavoriteWithAppId:(NSString *)appId result:(void(^)(BOOL isSuccess,NSString *msg))result;
+ (void)lj_cancelRecentWithAppId:(NSString *)appId result:(void(^)(BOOL isSuccess,NSString *msg))result;

+ (NSArray *)lj_getRecentJumpsByModel;

/**游戏中心上报*/
+ (void)lj_reportGameCenterWithCkey:(NSString *)ckey skey:(NSString *)skey loginType:(NSInteger)loginType time_sec:(NSString *)time_sec finish:(void(^)(id data))finish;

/**上报*/
+ (void)lj_reportWithUrl:(NSString *)url;

+ (void)lj_saveGameCenter:(UIViewController *)vc;
+ (void)lj_destroyGameCenter:(UIViewController *)vc;
/**获取是否显示日志*/
+ (BOOL)lj_isShowLog;

/**模型数组转成字典数组*/
+ (NSMutableArray *)mgc_keyValuesArrayWithObjectArray:(NSArray *)array withModelClass:(Class)modelClass;
/**获取游戏中心的类型 0是普通 1是金币*/
+ (NSInteger)mgc_getGameCenterType;
/**清除缓存上报*/
+ (void)lj_cacheClearReport;
+ (void)lj_setImageWithBtn:(UIButton *)btn url:(NSString *)url placeholderImage:(UIImage *)placeholderImage forState:(UIControlState)state;

/**判断当前渠道是否是传入的指定渠道*/
+ (BOOL)mgc_checkSpecialChannelWithType:(NSInteger)type;
/**签到弹框*/
+ (UIView *)mgc_signAlertWithAward:(NSString *)award curView:(UIView *)curView alertType:(NSInteger)alertType funcBlock:(void(^)(NSInteger,id))funcBlock;
+ (void)mgc_updateSignAlert:(UIView *)alert award:(NSString *)award;
+ (void)mgc_hideSignAlert:(UIView *)alert;
/**游戏中心退出*/
+ (void)mgc_gameCenterExit;

/**创建星星视图*/
+ (UIView *)mgc_createStartViewWithFrame:(CGRect)frame number:(CGFloat)num emptyImage:(UIImage *)emptyImage realImage:(UIImage *)realImage;

+ (void)mgc_setScore:(CGFloat)score view:(UIView *)view;

/**获取金币余额*/
+ (void)mgc_getCoinFinish:(void(^)(BOOL isSuccess,NSString *coin,NSString *balance))finish;
+ (NSDictionary *)mgc_getSearchParams;
+ (void)mgc_requestForGetWithUrl:(NSString *)url param:(NSDictionary *)param success:(void(^ )(NSURLSessionDataTask * _Nonnull task, id _Nullable responseObject))success fail:(void(^)(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error))fail;
+ (NSString *)mgc_getMobile;
+ (NSInteger)mgc_getCoinToRmbRate;
/**添加金币*/
+ (void)mgc_addCoinWithCoins_scene_type:(NSInteger)coins_scene_type finish:(void(^)(BOOL isSuccess,NSString *add_coins))finish;
/**我的奖品回调*/
+ (void)mgc_myAwardBlockWithVC:(UIViewController *)vc;

+ (void)mgc_pptvSign:(void(^)(BOOL isSuccess))result;
+ (void)mgc_destroySignAlert:(UIView *)alert;
/**签到上报*/
+ (void)mgc_statisSignWithLoginType:(NSInteger)loginType day:(NSString *)day;
/**校验订单*/
+ (NSString *)lj_getProduceIdWithPrice:(NSInteger)price;

+ (NSString *)mgc_toURLParamsStringWithDic:(NSDictionary *)dic;
+ (void)lj_showBoxWithView:(UIView *)view;
+ (NSString *)mgc_localString:(NSString *)string;
+ (UIImage *)mgc_localImage:(NSString *)string;
+ (void)mgc_requestForPostWithUrl:(NSString *)url param:(NSDictionary *)param handler:(void(^)(id data,BOOL isSuccessed,NSString *code,NSString *message))handler;
+ (NSString *)mgc_environment;
+ (UIViewController *)mgc_getTopController;
+ (void)mgc_loginWithCurVC:(UIViewController *)vc status:(void(^)(BOOL isSuccess, NSString *code, NSString *msg, NSInteger extStatus))status;
+ (void)mgc_payStatus:(BOOL)isSuccess msg:(NSString *)msg;
+ (NSString *)mgc_syncUserId;

/**常用弹框*/
+ (UIView *)mgc_alertWithAward:(NSString *)award curView:(UIView *__nullable)curView alertType:(NSInteger)alertType funcBlock:(void(^)(NSInteger funcType,id alert))funcBlock;
/**任务发放金币*/
+ (void)mgc_rewardTaskWithGame_id:(NSString *)game_id coins_scene_type:(NSInteger)coins_scene_type add_coins:(NSString *)add_coins coins_order_id:(NSString *)coins_order_id finish:(void(^)(BOOL isSuccess,NSString *msg,NSString *coins))finish;
/**普通发放金币*/
+ (void)mgc_sendCoinWithGame_id:(NSString *)game_id coins_scene_type:(NSInteger)coins_scene_type add_coins:(NSString *)add_coins coins_order_id:(NSString *)coins_order_id finish:(void(^)(BOOL isSuccess,NSString *msg,NSString *coins))finish;
/**扣除金币*/
+ (void)mgc_costCoinsWithGame_id:(NSString *)game_id coins_scene:(NSInteger)coins_scene coins_num:(NSString *)coins_num finish:(void(^)(BOOL isSuccessed,NSString *message))finish;


/**获取亿刻平台所需要的公共参数*/
+ (NSDictionary *)mgc_getYiKeCommonParams;

/**缓存图片*/
+ (void)mgc_loadImageWithUrl:(NSString *)url finish:(void(^)(UIImage *image))finish;
/**设置多tap标识*/
+ (void)mgc_settingMoreTabSign;
/**处理加群任务*/
+ (void)mgc_handlerAddGroupTask;
/**存储用户信息信息*/
+ (void)mgc_saveUserInfo:(NSDictionary *)userInfo;
/**获取用户信息*/
+ (NSDictionary *)mgc_getUserInfo;
/**存储登录信息*/
+ (void)mgc_saveLoginInfo:(NSDictionary *)loginInfo;
/**微信登录*/
+ (void)mgc_wechatLoginWithResult:(void(^)(BOOL isSuccess,NSDictionary *userInfo))result;
/**模型转字典*/
+ (NSDictionary *)mgc_keyValuesWithData:(id)data ignoredKeys:(NSArray *)ignoredKeys;
/**统计*/
+ (void)mgc_event:(NSString *)event attributes:(NSDictionary *(^)(void))attributes;
/**账号统计*/
+ (void)mgc_profileSignInWithPUID:(NSString *)puid provider:(NSString *)provier;
/**页面统计*/
+ (void)mgc_beginLogPageView:(NSString *)pageName;
+ (void)mgc_endLogPageView:(NSString *)pageName;


/**用来测试广告展示*/
+ (void)mgc_showVideoAdIsLandscape:(BOOL)isLandscape;
/**获取金币余额*/
+ (void)mgc_wxMemcoinWithHandler:(void(^)(id __nullable data,BOOL isSuccessed,NSString * __nullable code , NSString * __nullable message))handler;
/**获取盒子环境 0是正式环境 1是提审环境*/
+ (NSInteger)mgc_boxEnvironment;
/**将游戏资源文件存到资源路径下*/
+ (void)saveGameSourceWithPath:(NSString *)path appId:(NSString *)appId;
/**将缓存文件拷贝到缓存路径下*/
+ (void)saveGameStorageWithPath:(NSString *)path appId:(NSString *)appId;

@end

NS_ASSUME_NONNULL_END
