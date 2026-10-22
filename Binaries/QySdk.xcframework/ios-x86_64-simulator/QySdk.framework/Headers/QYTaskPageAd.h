//
//  QYTaskPageAd.h
//  QySdk
//
//  Created by liuyulei on 2025/11/10.
//  Copyright © 2025 iqiyi. All rights reserved.
//

#import <QySdk/IAdSdk.h>
#ifdef SUPPORT_ADN_
@class QYAdnModelBase;
#endif

NS_ASSUME_NONNULL_BEGIN

@interface QYTaskPageAd : QYExpressBase

- (instancetype) initWithSlotId:(NSString *)slotId;
- (void) loadData;
- (void) showAdFromeRootViewController:(UIViewController *)rootViewController;
- (void) dismiss;
#ifdef SUPPORT_ADN_
- (nullable QYAdnModelBase *)adnModelForAdId:(NSString *)adId; // 根据 adId 获取 adnModel
#endif

@end

NS_ASSUME_NONNULL_END
