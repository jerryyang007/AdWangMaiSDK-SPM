//
//  XAdLocation.h
//  AdWangMaiSDK
//
//  Created by 周泽浩 on 2023/8/9.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface XAdLocation : NSObject

/// 纬度
@property (nonatomic,copy) NSString *latitude;

/// 经度
@property (nonatomic,copy) NSString *longitude;

@end

NS_ASSUME_NONNULL_END
