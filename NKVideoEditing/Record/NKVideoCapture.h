//
//  NKVideoRecoder.h
//  NKVideoEditing
//
//  Created by niekang on 2022/8/29.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NKVideoCapture : NSObject

@property(nonatomic, strong)UIView* preview;
@property(nonatomic, assign)CGSize previewSize;

- (void)start;
- (void)stop;

@end

NS_ASSUME_NONNULL_END
