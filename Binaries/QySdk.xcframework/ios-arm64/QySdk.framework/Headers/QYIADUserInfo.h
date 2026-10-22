//
//  QYIADUserInfo.h
//  QySdk
//
//  Created by Peiran Zhang on 2021/11/3.
//  Copyright © 2021 iqiyi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QYIADUserInfo : NSObject

@property (nonatomic, copy) NSString *passportId;
@property (nonatomic, copy) NSString *passportCookie;
@property (nonatomic, strong) NSArray <NSString *>*vipTypes; //VIP类型: 非会员传递nil; 登录状态传递会员信息数组, 如同时是黄金会员和体育会员，传递@[@"1", @"14"]

- (instancetype) initWithPassportId:(NSString *)passportId passportCookie:(NSString *)passportCookie vipTypes:(NSArray * __nullable)vipTypes;

@end

NS_ASSUME_NONNULL_END
