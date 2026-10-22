//
//  QYAdnConfigItem.h
//  QySdk
//
//  Created by Peiran Zhang on 2022/4/22.
//  Copyright © 2022 iqiyi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QYAdnConfigItem : NSObject

@property (nonatomic, copy) NSString *adnType; //adn类型，取值和orderitemid相同
@property (nonatomic, copy) NSString *adnAdType; //广告类型
@property (nonatomic, copy) NSString *plt; //1-横版 2-竖版 3-横竖都行
@property (nonatomic, copy) NSString *adnCodeId; //代码位id
@property (nonatomic, assign) int userFlag; //用户标识，0-老用户，1-新用户

-(instancetype)initWithDict:(NSDictionary *)dict;
-(instancetype) initWithAdnType:(NSString *)adnType adType:(NSString *)adnAdType plt:(NSString *)plt codeId:(NSString *)codeId;

@end

NS_ASSUME_NONNULL_END
