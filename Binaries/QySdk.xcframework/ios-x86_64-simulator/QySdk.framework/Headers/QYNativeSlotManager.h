//
//  QYNativeSlotManager.h
//  QySdk
//
//  Created by Peiran Zhang on 2022/1/28.
//  Copyright © 2022 iqiyi. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "QYAdSlot.h"
#import "QYNativeSlotManagerDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@interface QYNativeSlotManager : NSObject

@property (nonatomic, weak) id<QYNativeSlotManagerDelegate> delegate;
@property (nonatomic, weak) UIViewController *rootController;

- (void) loadNativeAdWithSlot:(QYAdSlot *)adSlot;
@end

NS_ASSUME_NONNULL_END
