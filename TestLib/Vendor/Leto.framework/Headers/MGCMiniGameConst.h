//
//  MGCMiniGameConst.h
//  Leto
//
//  Created by yuan yao on 2019/4/19.
//  Copyright © 2019 ledong. All rights reserved.
//

#import <Foundation/Foundation.h>

/**小游戏运行状态*/
typedef NS_ENUM(NSInteger,MgcMiniGameRunStatusType) {
    /**启动游戏*/
    MgcMiniGameRunStatusType_Start = 0,
    /**退出游戏*/
    MgcMiniGameRunStatusType_Exit = 1,

};

/**小游戏启动场景*/
typedef NS_ENUM(NSInteger,MgcMiniGameSceneType) {
    /**未知*/
    MgcMiniGameSceneType_UnKnown = 0,
    /**Tab页*/
    MgcMiniGameSceneType_Tab = 1,
    /**feed流*/
    MgcMiniGameSceneType_Feed = 2,
    /**聊天*/
    MgcMiniGameSceneType_Chat = 3,
    /**banner*/
    MgcMiniGameSceneType_Banner = 4,
    /**猜你喜欢*/
    MgcMiniGameSceneType_GuessLike = 5,
    /**收藏*/
    MgcMiniGameSceneType_Favorite = 6,
    /**玩过的*/
    MgcMiniGameSceneType_Played = 7,
    /**推荐*/
    MgcMiniGameSceneType_Recommend = 8,
    /**游戏中心*/
    MgcMiniGameSceneType_GameCenter = 9,
    /**更多游戏列表*/
    MgcMiniGameSceneType_MoreGame = 10,
    /**视频流*/
    MgcMiniGameSceneType_VideoFeed = 11,
    /**锁屏页面今日爆款(安卓)*/
    MgcMiniGameSceneType_Lock_Hot = 12,
    /**锁屏页面我玩过的游戏(安卓)*/
    MgcMiniGameSceneType_Lock_My = 13,
    /**锁屏页面一天一个小游戏(安卓)*/
    MgcMiniGameSceneType_Lock_OneDay_OneGame = 14,
    /**锁屏页面更多游戏(安卓)*/
    MgcMiniGameSceneType_Lock_More = 15,


};

/**SDK使用场景*/
typedef NS_ENUM(NSInteger,MGCSdkUseSceneType) {
    /**应用层场景(默认场景）*/
    MGCSdkUseSceneType_Apply = 0,
    /**系统层场景*/
    MGCSdkUseSceneType_System = 1,
};

/**SDK转场策略*/
typedef NS_ENUM(NSInteger,MGCSdkTransitionPolicy)
{
    /**一个游戏*/
    MGCSdkTransitionPolicy_OnlyOneGame = 0,
    /**简约版*/
    MGCSdkTransitionPolicy_Simple = 1,
    /**默认的*/
    MGCSdkTransitionPolicy_Default = 2,
};

/**SDK日志等级*/
typedef NS_ENUM(NSInteger,MGCSdkLogLevel) {
    /**调试*/
    MGCSdkLogLevel_Debug = 0,
    /**发布*/
    MGCSdkLogLevel_Release = 1,
};

/**应用类型*/
typedef NS_ENUM(NSInteger,MGCAppType) {
    /**默认类型*/
    MGCAppType_Default = 0,
    /**盒子类型*/
    MGCAppType_Box = 1,
};
/**横屏游戏旋转策略*/
typedef NS_ENUM(NSInteger,MGCHorGameRotatePolicy) {
    /**默认*/
    MGCHorGameRotatePolicy_Default,
    /**旋转视图*/
    MGCHorGameRotatePolicy_RotateView,
};

/**横屏游戏旋转方向*/
typedef NS_ENUM(NSInteger,MGCHorGameRotateDirection) {
    MGCHorGameRotateDirection_Left,
    /**默认是向右旋转*/
    MGCHorGameRotateDirection_Right,
    
};
/**获取token策略*/
typedef NS_ENUM(NSInteger,MGCGetTokenPolicy) {
    /**默认*/
    MGCGetTokenPolicy_Default,
    /**初始化的时候*/
    MGCGetTokenPolicy_Init,
};

/**获取手机屏幕尺寸类型*/
typedef NS_ENUM(NSInteger,MGCScreenType) {
    MGCScreenType_3_5,
    MGCScreenType_4_0,
    MGCScreenType_4_7,
    MGCScreenType_5_5,
    MGCScreenType_5_8,
    MGCScreenType_6_1,
    MGCScreenType_6_5,
};

/**SDK运行环境*/
typedef NS_ENUM(NSInteger,MGCSDKRunEnvironment) {
    /**正式环境*/
    MGCSDKRunEnvironment_Release,
    /**调试环境*/
    MGCSDKRunEnvironment_Debug,
    
};

/**头条使用场景*/
typedef NS_ENUM(NSInteger,MGCToutiaoUsePolicy) {
    /**自己使用*/
    MGCToutiaoUsePolicy_Use,
    /**没有使用*/
    MGCToutiaoUsePolicy_NoUse,
};


NS_ASSUME_NONNULL_BEGIN

// 如果在demo中, 设置这个变量以便跳过某些检查
extern BOOL __IN_LETO_DEMO;

extern NSString * const key_cp_order_id ;
extern NSString * const key_product_id ;//商品id
extern NSString * const key_product_name ;//商品名字
extern NSString * const key_product_desc;//商品描述
extern NSString * const key_option_ext;//扩展参数，可选
extern NSString * const key_product_price ;//商品金额
extern NSString * const key_role_id  ;//角色id
extern NSString * const key_role_name; //角色名字
extern NSString * const key_currency_name; //货币名
extern NSString * const key_product_count; //产品数量
extern NSString * const key_exchange_rate; //是 STRING 虚拟币兑换比例（例如100，表示1元购买100虚拟币） 默认为0

/**微信appkey*/
extern NSString * mgc_wechat_appkey_key;
/**微信appsercet*/
extern NSString * mgc_wechat_appsercet_key ;
/**支付类型 1是h5支付 2是苹果内购*/
extern NSString * mgc_happy_type_key;
/**appId*/
extern NSString * mgc_app_id_key;
/**苹果内购*/
extern NSString * mgc_apple_pay_key;
/**价格*/
extern NSString * mgc_apple_pay_price_key;
/**苹果支付环境*/
extern NSString *mgc_apple_pay_environment_key;
/**产品id*/
extern NSString * mgc_apple_pay_produce_id_key;
/**注册=>登录回调*/
extern NSString * mgc_register_login_key;
/**设置返回*/
extern NSString * mgc_hidden_back_key;
/**设置下载动画隐藏*/
extern NSString * mgc_hidden_download_key;
/**设置背景图片*/
extern NSString * mgc_download_image_key;
/**注册=>分享的回调*/
extern NSString * mgc_register_share_key;
/**注册=>监听游戏状态的回调*/
extern NSString * mgc_register_run_status_key;
/**注册=>支付的回调*/
extern NSString * mgc_register_pay_status_key;
/**是否要同步账号*/
extern NSString * mgc_sync_account_key;
/**设置sdk使用场景*/
extern NSString * mgc_use_scene_key;
/**设置sdk的转场策略*/
extern NSString * mgc_transition_policy_key;
/**设置是否开启日志*/
extern NSString * mgc_log_level_key;
/**注册=>发送金币的回调*/
extern NSString * mgc_register_send_coin_key;
/**注册=>提现的回调*/
extern NSString * mgc_register_get_cash_key;
/**是否自带穿山甲*/
extern NSString *mgc_toutiao_use_policy_key;




/**注册提现数量*/
extern NSString *mgc_draw_amount_key ;
/**实际到账数量*/
extern NSString *mgc_draw_real_amount_key ;
/**注册提现数量*/
extern NSString *mgc_draw_coins_key ;
/**金币名*/
extern NSString *mgc_draw_symbol_key;
/**订单id*/
extern NSString *mgc_draw_order_id_key;
/**类型*/
extern NSString *mgc_draw_type_key ;
/**账号*/
extern NSString *mgc_draw_account_key;
/**姓名*/
extern NSString *mgc_draw_real_name_key;
/**银行卡编号*/
extern NSString *mgc_draw_bank_code_key ;
/**流水号*/
extern NSString *mgc_draw_payment_no_key;


/**手机号*/
extern NSString *mgc_sync_mobile_key;
/**userId*/
extern NSString *mgc_sync_userid_key;
/**昵称*/
extern NSString *mgc_sync_nickname_key;
/**头像*/
extern NSString *mgc_sync_portrait_key;
/**登录标识  1正是账号 2.游客账号*/
extern NSString *mgc_sync_loginsign_key;
/**性别*/
extern NSString *mgc_sync_gender_key ;


/**注册步数宝客服回调*/
extern NSString *mgc_register_bsb_service_key;
/**注册骑士助手金币回调*/
extern NSString *mgc_register_qszs_coin_key;
/**注册接收梦工厂登录信息回调*/
extern NSString *mgc_register_receive_login_info_key;
/**注册观看视频完成的回调*/
extern NSString *mgc_register_video_finish_key;
/**注册游戏中心退出的回调*/
extern NSString *mgc_register_game_center_exit_key;
/**注册pptv我的奖品回调*/
extern NSString *mgc_register_pptv_my_award_key;
/**注册pptv签到回调*/
extern NSString *mgc_register_pptv_sign_key;
/**注册pptv提现回调*/
extern NSString *mgc_register_pptv_get_cash_key ;

/**应用类型*/
extern NSString *mgc_application_type_key;
/**统计开关*/
extern NSString *mgc_analytics_status_key;
/**横屏游戏旋转策略*/
extern NSString *mgc_hor_game_rotate_policy_key;
/**获取token策略*/
extern NSString *mgc_get_token_policy_key;
/**客服显示开关*/
extern NSString *mgc_service_hidden_key;
/**跳过登录开关*/
extern NSString *mgc_skip_login_key;
/**延长启动时间*/
extern NSString *mgc_splash_delay_time_key;
/**游戏中心的回调*/
extern NSString *mgc_game_center_key;
/**注册游戏退出的回调*/
extern NSString *mgc_game_exit_key;
/**横屏游戏旋转方向*/
extern NSString *mgc_hor_game_rotate_direction_key;

/**sdk运行环境*/
extern NSString *mgc_sdk_run_environment_key;


/**
 param isSuccess 状态 YES成功 NO失败
 param mobile  手机号
 param result 同步账号的回调
 */
typedef void(^MgcCustomLoginCall)(BOOL isSuccess, NSDictionary<NSString *,NSString *> *(^syncInfo)(void),void(^result)(BOOL isSyncSuccess,NSString *msg,NSString *mgc_userId));

typedef void(^MgcCustomLogin)(UIViewController *curVC, MgcCustomLoginCall call);

/**
 param isSuccess 状态 YES成功 NO失败
 param mes 分享的状态信息
 */
typedef void(^MgcCustomShareCall)(BOOL isSuccess,NSString *msg);
typedef void(^MgcCustomShare)(NSString *title,NSString *des,NSString *url,MgcCustomShareCall call);


/**游戏运行状态的回调*/
typedef void(^MgcMiniGameRunStatusBlock)(NSString *name, NSString *gameId,MgcMiniGameRunStatusType runType);

/**登录状态的回调*/
typedef void(^LJLoginStatusBlock)(BOOL isSuccess,NSString *code,NSString *message,NSString *memberId,NSString *mobile);
/**happy回调*/
typedef void(^MgcHappyStatusBlock)(BOOL isSuccess,NSString *message);

/**提现的回调*/
typedef void(^MgcGetCashCall)(BOOL isSuccess,NSString *message,NSDictionary *result);
typedef void(^MgcGetCashBlock)(UIViewController *curVC,MgcGetCashCall);

/**发放金币的回调*/
typedef void (^MgcSendCoinCall)(BOOL isSuccess,NSString *message);
typedef void (^MgcSendCoinBlock)(NSString *gameId, NSString *addCoins,MgcSendCoinCall call);
/**步数宝->客服回调*/
typedef void(^MgcBSBServiceBlock)(UIViewController *curVC);
/**骑士助手->金币回调*/
typedef void(^MgcQSZSCoinBlock)(UIViewController *curVC);
/**接收梦工厂登录信息的回调*/
typedef void(^MgcReceiveLoingInfoBlock)(NSString *mgc_userId,NSString *mobile);
/**视频播放完成的回调*/
typedef void(^MgcVideoAdFinishBlock)(void);
/**游戏中心退出的回调*/
typedef void(^MgcGameCenterExitBlock)(void);
/**pptv->我的奖品回调*/
typedef void(^MgcPPTVMyAwardBlock)(UIViewController *curVC);

typedef void(^MgcPPTVSignCall)(BOOL isSuccess);
/**pptv->签到回调*/
typedef void(^MgcPPTVSignBlock)(MgcPPTVSignCall calll);
/**pptv->提现回调*/
typedef void(^MgcPPTVGetCashBlock)(void);
typedef void(^MgcPPTVGetCashCall)(BOOL isSuccess);

/**中心中心的回调*/
typedef void(^MgcGameCenterBlock)(UIViewController *curVC);

/**退出游戏返回*/
typedef void (^MgcGameExitCall)(BOOL isExit);
/**退出游戏的回调*/
typedef void(^MgcGameExitBlock)(UIViewController *curVC,NSString *gameId, MgcGameExitCall call);

@interface MGCMiniGameConst : NSObject


+ (MgcMiniGameSceneType)mgc_getSceneTypeWithStr:(NSString *)str;

@end

NS_ASSUME_NONNULL_END
