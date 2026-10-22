//
//  FantiSDK
//
//  Created by guangkuo.zgk on 2024/11/05.
//  Copyright © 2024 fanti.com. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, FTSDKInitState) {
    FTSDKInitStateDefault = 0,
    FTSDKInitStateLoading = 1,
    FTSDKInitStateSuccessed = 2,
    FTSDKInitStateFailed = 3
};


@class FTSDKParams;
@interface FTSDKConfig : NSObject

@property (nonatomic, assign, readonly, class) FTSDKInitState initState;

/**
 * 启动SDK
 */
+ (void)startWithParams:(nullable FTSDKParams *)params;

//查询sdk版本号
+ (nullable NSString *)getSdkVersion;

/**
 *  获取用于 Server Bidding 请求的竞价 Token。
 *
 *  @note 调用前需确保已进行SDK初始化（详见接入文档）
 *
 *  @param slotId 广告代码位 ID，不可为空
 *  @return 加密后的竞价 Token 字符串；若SDK未初始化或相关参数无效，则会返回 nil
 */
+ (nullable NSString *)getBiddingTokenWithSlotId:(nonnull NSString *)slotId;

@end

