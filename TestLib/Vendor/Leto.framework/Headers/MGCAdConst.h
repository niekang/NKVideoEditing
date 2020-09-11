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

@class MGCAdBean;

/**视频广告的状态*/
typedef NS_ENUM(NSInteger,MGCVideoAdStatus) {
    /**加载视频广告成功*/
    MGC_VIDEO_AD_STATUS_LOADED,
    /**加载视频广告失败*/
    MGC_VIDEO_AD_STATUS_FAILED,
    /** 视频广告已显示 */
    MGC_VIDEO_AD_STATUS_EXPOSED,
    /**关闭视频广告*/
    MGC_VIDEO_AD_STATUS_CLOSED,
    /**有效*/
    MGC_VIDEO_AD_STATUS_AVAILABLE,
    /**无效*/
    MGC_VIDEO_AD_STATUS_NO_AVAILABLE,

};

/**banner广告状态*/
typedef NS_ENUM(NSInteger,MGCBannerAdStatus) {
    /**加载banner广告成功*/
    MGC_BANNER_AD_STATUS_LOADED,
    /**加载banner广告失败*/
    MGC_BANNER_AD_STATUS_FAILED,
    /**关闭banner广告*/
    MGC_BANNER_AD_STATUS_CLOSED
};

/**
 广告策略:
 方案1: 使用sdk广告, 或者api广告
 方案2: 使用api广告, 如果没有则使用sdk广告, 如果没有则使用缺省广告
 特殊情况: 亿刻会在没有广告时返回他自己的打底sdk广告, 但是要优先使用mgc的sdk打底广告, 如果mgc没有配置打底的sdk广告,
 则使用亿刻的打底sdk广告
 */
typedef NS_ENUM(NSInteger, MGCAdStrategyType) {
	MGC_AD_STRATEGY_SDK_OR_API = 1,
	MGC_AD_STRATEGY_API_SDK_DEFAULT
};

// 只对方案1有效, 使用sdk还是api
typedef NS_ENUM(NSInteger, MGCAdJointType) {
	MGC_AD_USE_SDK = 1,
	MGC_AD_USE_API
};

// ad platform strings
#define MGC_AD_PLATFORM_STR_ADVIEW @"adview"
#define MGC_AD_PLATFORM_STR_GDT @"gdt"
#define MGC_AD_PLATFORM_STR_TOUTIAO @"toutiao"
#define MGC_AD_PLATFORM_STR_BAIDU @"baidu"
#define MGC_AD_PLATFORM_STR_INMOBI @"inmobi"
#define MGC_AD_PLATFORM_STR_APPLOVIN @"applovin"
#define MGC_AD_PLATFORM_STR_YIKE @"yike"
#define MGC_AD_PLATFORM_STR_FENGFEI @"fengfei"
#define MGC_AD_PLATFORM_STR_JULIANGAPI @"juliangapi"
#define MGC_AD_PLATFORM_STR_KUISHOW @"maplehaze"

/**广告厂商种类*/
typedef NS_ENUM(NSInteger,LJAdFirmType) {
    /**快友*/
    LJAdFirmType_AdView = 1,
    /**广点通*/
    LJAdFirmType_GDT = 2,
    /**穿山甲(头条)*/
    LJAdFirmType_BUAd = 3,
    /**百度*/
    LJAdFirmType_BaiDu = 4,
    /**InMobi*/
    LJAdFirmType_InMobi = 5,
    /**applovin*/
    LJAdFirmType_Applovin = 6,
    /**小米*/
    LJAdFirmType_Mi = 7,
    /**华为*/
    LJAdFirmType_HuaWei = 8,
    /**oppo*/
    LJAdFirmType_Oppo = 9,
    /**vivo*/
    LJAdFirmType_Vivo = 10,
    /**亿刻*/
    LJAdFirmType_YiKe = 11,
    /**快有*/
    LJAdFirmType_KuaiYou = 26,
};

/**广告类型*/
typedef NS_ENUM(NSInteger,MGCAdType) {
    /**banner*/
    MGC_AD_TYPE_BANNER = 0 ,
    /**插屏*/
    MGC_AD_TYPE_INTERSTITIAL = 1,
    /**开屏*/
    MGC_AD_TYPE_SPLASH = 4,
    /**视频*/
    MGC_AD_TYPE_VIDEO = 5,
    /**横屏视频*/
    MGC_AD_TYPE_VIDEO_HORIZONTAL = 11,
    /**feed ad (模板渲染) */
    MGC_AD_TYPE_FEED = 12,
    /** draw feed ad(自渲染) */
    MGC_AD_TYPE_DRAW_FEED = 13,

};

/** 用户交互操作 */
typedef NS_ENUM(NSInteger, MGCAdInteractionType) {
    MGC_AD_CLICK = 1,
    MGC_AD_CLICK_EXT_BUTTON = 2, // 仅视频广告有该按钮
    MGC_AD_CLICK_LAND_PAGE = 3, // 仅视频广告有落地页
};

// mgc ad error domain
#define MGC_AD_ERROR_DOMAIN @"MGC_AD_ERROR"

// ad callback error code
typedef NS_ENUM(NSInteger,MGCAdError) {
	MGC_AD_ERROR_UNKNOWN = -1,
	MGC_AD_ERROR_NO_SUITABLE_AD = 1004,
	MGC_AD_ERROR_INVALID_RESPONSE = 1005
};

// ad action type
typedef NS_ENUM(NSInteger,MGCAdActionType) {
	MGC_AD_ACTION_END_PAGE = 1 << 0,
	MGC_AD_ACTION_DOWNLOAD = 1 << 1,
	MGC_AD_ACTION_MAP_LOCATION = 1 << 2,
	MGC_AD_ACTION_SMS = 1 << 3,
	MGC_AD_ACTION_EMAIL = 1 << 4,
	MGC_AD_ACTION_PHONE = 1 << 5,
	MGC_AD_ACTION_VIDEO = 1 << 6
};

// ad source type
typedef NS_ENUM(NSInteger,MGCAdSourceType) {
	MGC_AD_FROM_API = 2,//1
	MGC_AD_FROM_SDK = 1,//2
	MGC_AD_FROM_DEFAULT = 3
};

// video format
typedef NS_ENUM(NSInteger,MGCVideoFormat) {
	MGC_VIDEO_FORMAT_VAST = 1,
	MGC_VIDEO_FORMAT_NORMAL = 2
};

// video play status
typedef NS_ENUM(NSInteger,MGCVideoPlayStatus) {
	/**准备播放*/
	MGC_VIDEO_PLAY_READY,
    /** 播放中 */
    MGC_VIDEO_PLAY_PROGRESS,
	/**播放完成*/
	MGC_VIDEO_PLAY_FINISH,
};

/**广告上报类型*/
typedef NS_ENUM(NSInteger,MGCAdReportType) {
    /**曝光上报*/
    MGC_AD_REPORT_EXPOSE = 1,
    /**点击上报*/
    MGC_AD_REPORT_CLICK = 2,
};

// default ad info, use for report
#define MGC_DEFAULT_AD_POSID @"1"
#define MGC_DEFAULT_AD_APPID @"1"
#define MGC_DEFAULT_AD_ORIGIN 0

#define MGCChangeAdStr(type) [MGCAdConst changeAdTypeToAdStr:type]


// callback to get network ad response
typedef void (^MGCAdCallback)(NSArray<MGCAdBean*>* beans, NSError* error);

// callback to get video ad status
typedef void (^MGCVideoAdStatusCallback)(MGCVideoAdStatus status);

// callback to get ad interaction
typedef void (^MGCAdInteractionCallback)(MGCAdInteractionType act);

//callback to get banner ad status
typedef void (^MGCBannerAdStatusCallBack)(MGCBannerAdStatus status);

NS_ASSUME_NONNULL_BEGIN

@interface MGCAdConst : NSObject

@property (class, readonly) NSArray<NSString*>* AD_PLATFORMS_API;
@property (class, readonly) NSArray<NSString*>* AD_PLATFORMS_SDK;

/**广告类型*/
extern LJAdFirmType mgc_ad_firm_type;
/**广告id*/
extern NSString * mgc_ad_id;
/**广告的包名*/
extern NSString * mgc_ad_pack;
/**Banner id*/
extern NSString * mgc_ad_banner_id;
/**开屏 id*/
extern NSString * mgc_ad_splash_id;
/**视频 id*/
extern NSString * mgc_ad_video_id;

/**将广告类型转成字符串*/
+ (NSString *)changeAdTypeToAdStr:(MGCAdType)type;


@end

NS_ASSUME_NONNULL_END
