//
//  QYExpressRoll.h
//  Cupid
//
//  Created by Peiran Zhang on 2020/3/20.
//  Copyright © 2020 iqiyi. All rights reserved.
//
#ifdef SUPPORT_ROLL
#import "QYExpressBase.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef struct {
    CGFloat countDownOffsetVertical;
    CGFloat countDownOffsetHorizontal;
    CGFloat detailOffsetVertical;
    CGFloat detailOffsetHorizontal;
} QYRollDecroOffset;

@interface QYExpressRoll : QYExpressBase

- (instancetype) initWithSlotId:(NSString *)slotId;
- (void) presentFromController:(UIViewController *)controller frame:(CGRect)frame;
- (void) presentInView:(UIView *)view frame:(CGRect)frame;
- (void) start;
- (void) pause;
- (void) dismiss;
- (void) resize:(CGRect)frame parent:(UIView * __nullable)parent;
//设置静音，默认有声播放
- (void) setMute:(BOOL)mute;
- (void) setDecroOffset:(QYRollDecroOffset)offset;
@end



NS_ASSUME_NONNULL_END

#endif
