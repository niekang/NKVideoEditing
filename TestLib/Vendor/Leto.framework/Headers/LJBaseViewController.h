//
//  LJBaseViewController.h
//  mgc_ios_wallet
//
//  Created by yuan yao on 2018/5/19.
//  Copyright © 2018年 yuan yao. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LJBaseViewController : UIViewController

@property (nonatomic, assign) BOOL isHiddenLeftBtn;
@property (nonatomic, assign) BOOL isExistTabbar;
@property (nonatomic, copy) NSString *titleStr;


/**标题*/
@property (nonatomic, weak) UILabel *titleLabel;
/**导航条背景*/
@property (nonatomic, weak) UIView *headerBackView;

/**左边按钮的点击方法*/
- (void)leftBtnClick;
/**设置左边按钮的背景图*/
- (void)settingLeftBtnImage:(UIImage *)image;
/**控制左边按钮的展示和隐藏*/
- (void)hiddenLeftBtn:(BOOL)isHidden;
/**控制右边按钮的展示和隐藏*/
- (void)hiddenRightBtn:(BOOL)isHidden;
/**控制所有按钮是否有效*/
- (void)allBtnIsEnable:(BOOL)enable;
/**将左边的按钮，放到上层视图*/
- (void)bringLeftBtnToFront;
/**将标题放到上层*/
- (void)bringTitleToFront;
/**将右边的安妮，放到上层视图*/
- (void)bringRightBtnToFront;
/**右边按钮的点击方法*/
- (void)rightBtnClick;
/**设置右边按钮的背景图*/
- (void)settingRightBtnImage:(NSString *)imageName;
- (void)settingRightBtnWithImage:(UIImage *)image;

/**设置右边按钮的文字*/
- (void)settingRightBtnTitle:(NSString *)title color:(UIColor *)color font:(CGFloat)font;
- (void)settingRightBtnTitle:(NSString *)title color:(UIColor *)color font:(CGFloat)font length:(NSInteger)length;
- (void)settingRightBtnWithFrame:(CGRect)frame config:(void(^)( UIButton *rightBtn))config;
/**设置左边按钮的圆角和背景颜色*/
- (void)settingLeftBtnWithRadius:(CGFloat)radius bacCor:(UIColor *)bacCor;
@end
