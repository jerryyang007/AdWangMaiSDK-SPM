//
//  FTTVScheduleMgr.h
//  OneAdSDK
//
//  Created by huankuai on 2025/4/21.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^FTTVHttpClientComletionHandler)(NSHTTPURLResponse *httpResponse, NSError *error, id responseObject);

@interface FTTVScheduleMgr : NSObject

/**
 @params params
 @{startTime:时间戳字符串;endTime: 时间戳字符串}
 startTime：NSTimeInterval
 endTime：NSTimeInterval
 */
- (void)loadTVScheduleData:(NSDictionary *)params completion:(FTTVHttpClientComletionHandler)completionHandler;

@end

NS_ASSUME_NONNULL_END
