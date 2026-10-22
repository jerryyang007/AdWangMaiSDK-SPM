//
//  QYAdSlot.h
//  QySdk
//
//  Created by Peiran Zhang on 2022/1/28.
//  Copyright © 2022 iqiyi. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "QYExpressBase.h"

NS_ASSUME_NONNULL_BEGIN


@interface QYAdSlot : NSObject

@property (nonatomic, copy) NSString *slotID;
@property (nonatomic, assign) QY_ALI_SLOT_TYPE adSlotType;
@property (nonatomic, assign) NSInteger loadCount;
@property (nonatomic, assign) NSInteger loadDuration;
@property (nonatomic, assign) NSInteger skipAd;
@property (nonatomic, copy) NSString *channelId;

@end

NS_ASSUME_NONNULL_END
