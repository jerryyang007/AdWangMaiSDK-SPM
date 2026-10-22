//
//  QYExpressSplash.h
//  Cupid_DEMO
//
//  Created by Peiran Zhang on 2020/5/14.
//  Copyright © 2020 iqiyi. All rights reserved.
//

#import "QYExpressBase.h"

// 倒计时样式：0： 不展示倒计时，1：显示倒计时，2：不显示倒计时显示进度
typedef enum : NSUInteger {
    QY_SKIPBUTTON_STYLE_DEFAULT  = 0,
    QY_SKIPBUTTON_STYLE_TIMER    = 1,
    QY_SKIPBUTTON_STYLE_PROGRESS = 2
} QY_SKIPBUTTON_STYLE;

NS_ASSUME_NONNULL_BEGIN

@interface QYExpressSplash : QYExpressBase
@property(nonatomic, strong) UIImage *logo;
@property(nonatomic, assign) QY_SKIPBUTTON_STYLE skipButtonStyle;
- (instancetype) initWithSlotId:(NSString *)slotId;
- (void) presentFromController:(UIViewController *)controller completion:(void (^ __nullable)(void))completion;
- (void) dismiss;
@end

NS_ASSUME_NONNULL_END
