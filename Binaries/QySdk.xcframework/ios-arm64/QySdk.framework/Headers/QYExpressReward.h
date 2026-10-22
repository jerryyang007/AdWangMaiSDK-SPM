//
//  QYExpressReward.h
//  QySdk
//
//  Created by Peiran Zhang on 2021/1/8.
//  Copyright © 2021 iqiyi. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "QYExpressBase.h"

typedef enum : NSUInteger {
    QYSspPresentStyle_Present = 0,
    QYSspPresentStyle_Push = 1
} QYSspPresentStyle;

NS_ASSUME_NONNULL_BEGIN

@interface QYExpressReward : QYExpressBase

// 没看完情况下的再次曝光，在点击挽留弹窗再看一个时会触发
@property (nonatomic, assign) NSInteger impressionTimesWithoutEnd;
// 奖励的数量
@property (nonatomic, assign) NSInteger rewardAmount;

- (instancetype) initWithSlotId:(NSString *)slotId;
- (instancetype) initWithSlotId:(NSString *)slotId isPreload:(BOOL)isPreload;
- (instancetype) initWithSlotId:(NSString *)slotId channelId:(NSString *)channelId;
- (instancetype) initWithSlotId:(NSString *)slotId channelId:(NSString *)channelId isPreload:(BOOL)isPreload;
- (void) presentFromController:(UIViewController *)controller;
- (void) presentFromController:(UIViewController *)controller presntSytle:(QYSspPresentStyle)style;
- (void) dismiss;
// 设置静音，默认有声播放
- (void) setMute:(BOOL)mute;

// pravite fucntion
- (void)rewardCallbackSubPageSuccess:(QY_PULLING_PAGETYPE)type;
- (void)rewardCallbackSubPageClosed:(QY_PULLING_PAGETYPE)type;

// 传递剩余请求次数
- (void)loadData:(NSInteger)remainTimes;
@end

NS_ASSUME_NONNULL_END
