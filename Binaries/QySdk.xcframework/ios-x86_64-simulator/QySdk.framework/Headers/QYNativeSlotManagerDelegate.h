//
//  QYNativeSlotManagerDelegate.h
//  QySdk
//
//  Created by Peiran Zhang on 2022/1/28.
//  Copyright © 2022 iqiyi. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "QYNativeAd.h"
#import "QYExpressBase.h"

NS_ASSUME_NONNULL_BEGIN

@class QYNativeSlotManager;

@protocol QYNativeSlotManagerDelegate <NSObject>

- (void) nativeAdsLoadSuccess:(QYNativeSlotManager *)manager nativeAds:(NSArray<id<QYNativeAd>> *)ads;
- (void) nativeAdsLoadFailed:(QYNativeSlotManager *)manager errorCode:(QyAdErrorCode) code;
- (void) nativeAdsPageOpen:(QY_PULLING_PAGETYPE)type;
- (void) nativeAdsPageClose:(QY_PULLING_PAGETYPE)type;
@end

NS_ASSUME_NONNULL_END
