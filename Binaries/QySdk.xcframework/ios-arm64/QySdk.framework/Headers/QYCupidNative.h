//
//  QYCupidNative.h
//  QySdk
//
//  Created by Peiran Zhang on 2021/6/11.
//  Copyright © 2021 iqiyi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class QYCupid;
@class QYUniConverter;

@interface QYCupidNative : NSObject
//主要素材地址
@property(nonatomic, copy, readonly) NSString *creativeUrl;
//title文案
@property(nonatomic, copy, readonly) NSString *title;
//按钮文案
@property(nonatomic, copy, readonly) NSString *buttonTitle;
//推广app名称
@property(nonatomic, copy, readonly) NSString *appName;
//推广app icon
@property(nonatomic, copy, readonly) NSString *appIcon;
//点击跳转类型
@property(nonatomic, assign, readonly) int clickThroughType;
//激励数额
@property(nonatomic, assign, readonly) NSInteger rewardCount;
//激励时间点
@property(nonatomic, assign, readonly) NSInteger rewardTiming;
//激励状态
@property(nonatomic, copy, readonly) NSString *rewardState;

- (instancetype) initWithCupid:(QYCupid *)cupid converter:(QYUniConverter *)converter;
@end

NS_ASSUME_NONNULL_END
