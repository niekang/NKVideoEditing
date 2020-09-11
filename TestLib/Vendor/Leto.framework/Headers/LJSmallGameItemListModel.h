//
//  LJSmallGameItemListModel.h
//  mgc_ios_wallet
//
//  Created by yuan yao on 2018/10/26.
//  Copyright © 2018年 yuan yao. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LJJumpConfig;

typedef NS_ENUM(NSInteger,LJLoadType) {
    /**小游戏*/
    LJLoadType_MiniGame,
    /**网页*/
    LJLoadType_Web,
    /**h5游戏*/
    LJLoadType_H5Game,
    /**猎豹*/
    LJLoadType_LB,
    /**其他*/
    LJLoadType_Other,
};

typedef NS_ENUM(NSInteger,MGCActionType){
    /**打开游戏*/
    MGCActionType_Game,
    /**打开天梯赛*/
    MGCActionType_Day,
    /**打开周赛*/
    MGCActionType_Week,
    /**打开训练场*/
    MGCActionType_Test,
    /**打开挑战*/
    MGCActionType_Challenge,
    /**没有动作*/
    MGCActionType_None,

};


@interface LJSmallGameItemListModel : NSObject

@property (nonatomic, copy) NSString *id;
/**游戏名称带后缀*/
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *play_num;
@property (nonatomic, copy) NSString *icon;
@property (nonatomic, copy) NSString *publicity;
@property (nonatomic, copy) NSString *type_id;
@property (nonatomic, copy) NSString *packageurl;
/**1 普通推广类游戏  2 cps推广类游戏*/
@property (nonatomic, assign) NSInteger is_cps;
/**启动图*/
@property (nonatomic, copy) NSString *splash_pic;
/**游戏版本*/
@property (nonatomic, copy) NSString *version;

/**玩游戏的等级（1）150万~200万,（2）>100~150万 （3）80~100万 */
@property (nonatomic, assign) NSInteger playNumLever;

/**游戏统称*/
@property (nonatomic, copy) NSString *ass_name;

/**加载的类型*/
@property (nonatomic, assign) NSInteger classify;
/**安卓下载包*/
@property (nonatomic, copy) NSString *apkurl;
/**是否显示跟多 1是 2不是*/
@property (nonatomic, assign) NSInteger is_more;
/**0不是 1是*/
@property (nonatomic, assign) NSInteger is_big_game;
/**广告id*/
@property (nonatomic, copy) NSString *adid;
/**是否是重点推荐 1不是 2是*/
@property (nonatomic, assign) NSInteger is_keynote;
/**是否显示开屏广告 1是 2不是*/
@property (nonatomic, assign) NSInteger is_kp_ad;

/**小游戏收藏链接*/
@property (nonatomic, copy) NSString *add_game_win_page;
/**分享说明*/
@property (nonatomic, copy) NSString *share_msg;
/**分享链接*/
@property (nonatomic, copy) NSString *share_url;
/**分享的标题*/
@property (nonatomic, copy) NSString *share_title;
/**1是开广告 2是关广告*/
@property (nonatomic, assign) NSInteger is_open_ad;
/**[@"在线玩",@"传奇",@"PK"]*/
@property (nonatomic, strong) NSArray *tags;
@property (nonatomic, copy) NSString *show_tags;

/**1展示猜你喜欢 2不展示猜你喜欢*/
@property (nonatomic, assign) NSInteger is_like;
/**1是显示 2是不显示*/
@property (nonatomic, assign) NSInteger is_collect;
/**分享类型控制 1微信分享 2是普通分享*/
@property (nonatomic, assign) NSInteger share_type;
/**分享图标*/
@property (nonatomic, copy) NSString *share_icon;

/**新加字段*/
@property (nonatomic, copy) NSString *pic;
/**新加字段*/
@property (nonatomic, copy) NSString *backgroundcolor;
/**新加字段*/
@property (nonatomic, assign) NSInteger game_type;
/**高倍 1, 0不是高倍*/
@property (nonatomic, assign) NSInteger highrewardcoin;

@property (nonatomic, copy) NSString *zip_md5;

@property (nonatomic, assign) BOOL isRecGame;

/**游戏日期*/
@property (nonatomic, copy) NSString *game_date;
/**左上角角标*/
@property (nonatomic, copy) NSString *marker;
/**二级标题*/
@property (nonatomic, copy) NSString *title;
/**奖励数量*/
@property (nonatomic, copy) NSString *amount;
/**搜索游戏描述*/
@property (nonatomic, copy) NSString *game_desc;
/**分数*/
@property (nonatomic, copy) NSString *grade;
/**其它平台游戏id*/
@property (nonatomic, copy) NSString *classify_game_id;
/**客服*/
@property (nonatomic, copy) NSString *cs_wechat;
/**渠道绑定的小游戏*/
@property (nonatomic, copy) NSString *bind_game_id;




/**n合一*/
@property (nonatomic, copy) NSString *wechat_url;
@property (nonatomic, copy) NSString *APPID;
@property (nonatomic, copy) NSString *wechat_access_type;
@property (nonatomic, copy) NSString *wechat_qrcode;
@property (nonatomic, copy) NSString *path;
@property (nonatomic, copy) NSString *deviceOrientation;

/**计算属性*/
@property (nonatomic, copy) NSString *play_num_str;
@property (nonatomic, copy) NSString *packageurl_download;
@property (nonatomic, assign) BOOL isLandscape;
@property (nonatomic, assign) BOOL isShowMore;
@property (nonatomic, assign) BOOL isShowKpAd;
@property (nonatomic, assign) LJLoadType loadType;

@property (nonatomic, assign) BOOL isShowAd;
@property (nonatomic, assign) BOOL isShowGuessYouLike;
@property (nonatomic, assign) BOOL isShowCollection;
@property (nonatomic, assign) BOOL isWeXinShare;

/**自定义属性*/
@property (nonatomic, assign) NSInteger mgc_position;
/**动作类型*/
@property (nonatomic, assign) MGCActionType actionType;
/**竞技场的排行*/
@property (nonatomic, copy) NSString *competive_rank;

+ (instancetype)modelWithConfig:(LJJumpConfig *)config;

@end
