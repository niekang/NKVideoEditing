//
//  LJJumpConst.h
//  MgcMiniGame
//
//  Created by yuan yao on 2018/11/24.
//  Copyright © 2018 yuan yao. All rights reserved.
//

#import <Foundation/Foundation.h>

/**进入sdk的方式*/
typedef NS_ENUM(NSInteger,LJSDKUseType) {
    //没有加载游戏
    LJSDKUseType_NoLoad,
    //加载本地游戏
    LJSDKUseType_Local,
    //加载远程游戏
    LJSDKUseType_Remote,
};

/**sdk上报类型*/
typedef NS_ENUM(NSInteger,MGCSDKReportType) {
    
    /**启动游戏*/
    MGCSDKReportType_Game_Start = 0,
    /**退出游戏*/
    MGCSDKReportType_Game_Exit = 1,
    /**暂停游戏*/
    MGCSDKReportType_Game_Pause = 2,
    /**继续游戏*/
    MGCSDKReportType_Game_Reuse = 3,
    /**点击游戏*/
    MGCSDKReportType_Game_Click = 4,
    /**心跳*/
    MGCSDKReportType_Heart = 5,
    /**sdk启动*/
    MGCSDKReportType_SDK_Start = 6,
    /**进入游戏大厅*/
    MGCSDKReportType_Game_Center_Begin = 7,
    /**退出游戏大厅*/
    MGCSDKReportType_Game_Center_Exit = 8,
    /**获取游戏信息上报*/
    MGCSDKReportType_Game_Info = 9,
    /**游戏包下载上报*/
    MGCSDKReportType_Game_Download = 10,
    /**取消启动(安卓）*/
    MGCSDKReportType_Game_Force_Close = 11,
    /**zip包解压失败*/
    MGCSDKReportType_Game_Zip_Fail = 12,
    /**请求广告*/
    MGCSDKReportType_Ad_Request = 13,
    /**广告展示*/
    MGCSDKReportType_Ad_Show = 15,
    /**广告点击(废弃)*/
    MGCSDKReportType_Ad_Click = 16,
    /**创建游戏快捷方式*/
    MGCSDKReportType_Game_Shortcut = 17,
    /**游戏曝光(已经废弃了)*/
    MGCSDKReportType_Game_Exposure = 18,
    /**游戏收藏*/
    MGCSDKReportType_Game_Collection = 19,
    /**zip包UTF-8解压失败(安卓)*/
    MGCSDKReportType_Game_Zip_UTF_Fail = 20,
    /**zip包GBK解压失败(安卓)*/
    MGCSDKReportType_Game_Zip_GBK_Fail = 21,
    /**悬浮窗状态上报*/
    MGCSDKReportType_Float_Status = 22,
    /**点击展开悬浮窗*/
    MGCSDKReportType_Float_Click_Open = 23,
    /**关闭展开悬浮窗*/
    MGCSDKReportType_Float_Click_Close = 24,
    /**隐藏悬浮窗*/
    MGCSDKReportType_Float_Hidden = 25,
    /**进入提现页面*/
    MGCSDKReportType_Cash_Entrance = 26,
    /**切换悬浮窗状态*/
    MGCSDKReportType_Float_Change_Status = 27,
    /**清除缓存上报*/
    MGCSDKReportType_Cache_Clear = 28,
    /**看视频收益翻倍上报*/
    MGCSDKReportType_Video_Double = 29,
    /**不看视频领取金币上报*/
    MGCSDKReportType_Receive_No_Video = 30,
    /**游戏中心下拉刷新上报*/
    MGCSDKReportType_Game_Center_Refresh_Down = 31,
    /**激励视频播放完成上报*/
    MGCSDKReportType_Video_Finish = 32,
    /**游戏中心上拉翻页*/
    MGCSDKReportType_Game_Center_Scroll_down = 33,
    /**计时器增加金币*/
    MGCSDKReportType_Float_add_coin = 34,
    /**其他增加金币来源上报*/
    MGCSDKReportType_add_coin_from_other = 35,
    /**高倍金币游戏放弃领取金币上报*/
    MGCSDKReportType_Game_Double_Coin_No_receive = 36,
    /**高倍金币游戏看视频领取金币*/
    MGCSDKReportType_Game_Double_Coin_Video = 37,
    /**锁屏页面点击更多游戏(安卓)*/
    MGCSDKReportType_Lock_Screen_Click_More_Game = 38,
    /**zip md5 校验失败*/
    MGCSDKReportType_Game_Zip_Md5_fail = 39,
    /**zip 解压成功*/
    MGCSDKReportType_Game_Zip_Success = 40,
    /**签到直接领取金币*/
    MGCSDKReportType_Sign_Coin = 41,
    /**签到看视频领取金币*/
    MGCSDKReportType_Sign_Video_Coin = 42,
    /**广告返回*/
    MGCSDKReportType_Ad_Response = 43,
    /**广告加载*/
    MGCSDKReportType_Ad_Load = 44,
    /**广告有效*/
    MGCSDKReportType_Ad_Available = 45,


};

/**添加金币来源*/
typedef NS_ENUM(NSInteger,MGCSDKAddCoinType) {
    /**游戏*/
    MGCSDKAddCoinType_Game = 1,
    /**签到*/
    MGCSDKAddCoinType_Sign = 2,
    /**邀请好友*/
    MGCSDKAddCoinType_Invitation = 3,
    /**抽奖*/
    MGCSDKAddCoinType_Draw = 4,
};

/**sdk上报状态*/
typedef NS_ENUM(NSInteger,MGCSDKReportStatus) {
    /**成功*/
    MGCSDKReportStatus_Success = 0,
    /**失败*/
    MGCSDKReportStatus_Fail = 1,
};

/**缓存策略*/
typedef NS_ENUM(NSInteger,LJJumpCacheType) {
    /**1小时清除缓存*/
    LJJumpCacheType_Hour,
    /**1天清除缓存*/
    LJJumpCacheType_Day,
    /**一星期清除缓存*/
    LJJumpCacheType_Week,
    /**一个月清除缓存*/
    LJJumpCacheType_Month,
    /**一年清除缓存*/
    LJJumpCacheType_Year,
};

/**下载类型*/
typedef NS_ENUM(NSInteger,LJJumpDownloadType) {
    /**未知*/
    LJJumpDownloadType_UnKnown = 0,
    /**缓存(已经存在不需要下载)*/
    LJJumpDownloadType_Cache = 1,
    /**下载*/
    LJJumpDownloadType_Download = 2,
    /**更新*/
    LJJumpDownloadType_Update = 3,
};

/**计时器状态*/
typedef NS_ENUM(NSInteger,MGCTimeFloatWindowStatus) {
    /**关闭*/
    MGCTimeFloatWindowStatus_Close = 0,
    /**开启*/
    MGCTimeFloatWindowStatus_Open = 1,
};

/**与梦工厂合作的有特殊需求的渠道*/
typedef NS_ENUM(NSInteger,MGCChannel) {
    /**没有特殊渠道*/
    MGCChannel_None = -1,
    /**wifi万能钥匙*/
    MGCChannel_Wifi = 0,
    /**步数宝*/
    MGCChannel_Bsb = 1,
    /**PPTV*/
    MGCChannel_PPTV = 2,
    /**中华万年历*/
    MGCChannel_Calendar = 3,
    /**手机电视*/
    MGCChannel_MobileTV = 4,
    /**馒头公社*/
    MGCChannel_MTGS = 5,
    

};



/**检查黑名单*/
extern NSString * const system_startupinit_url;
/**检查是否需要换包*/
extern NSString * const mgc_needchangepackage_url;
/**更多游戏点击量*/
extern NSString * const exPlatform_click_url;
/**更多的点击量统计*/
extern NSString * const exPlatform_more_click_url;
/**检查白名单的接口*/
extern NSString * const minigame_check_url;
/**获取sdk配置文件接口*/
extern NSString * const app_conf_url;

@interface LJJumpConst : NSObject

/**获取上报事件*/
+ (NSString *)getReportEventWithLogin_type:(NSInteger)loginType;
/**判断当前渠道是否是传入的指定渠道*/
+ (BOOL)checkSpecialChannelWithType:(MGCChannel)type;
/**获取特殊渠道*/
+ (MGCChannel)getSpecialChannel;
@end


