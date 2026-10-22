//
//  QYAssociateVideoInfo.h
//  QySdk
//
//  Created by liuyulei on 2021/12/1.
//  Copyright © 2021 iqiyi. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface QYAssociateVideoInfo : NSObject

@property(nonatomic, copy) NSString *tvId;          // 垂线业务传递奇谱ID（episode id），外部媒体传递自定义剧集ID
@property(nonatomic, copy) NSString *albumId;
@property (nonatomic, assign) NSString *impressionId;
@property (nonatomic, strong) NSDictionary *adnCodeIdRule;
@property (nonatomic, assign) NSString *vvFrom;     // 播放来源，仅站内媒体
@property(nonatomic, copy) NSString *tvToken;       // 扫码激励视频，tv token
@property(nonatomic, copy) NSString *tvTaskGUid;         // 扫码激励视频，tv uid
@property(nonatomic, copy) NSString *tvEncodeUid;   // 扫码激励视频，tv 加密后的uid
@property(nonatomic, strong) NSDictionary *extraParamDic; // 扩展参数字典
@property(nonatomic, assign) NSInteger funType; // 功能类型，1-判断是仅出1个广告场景，2-可以出广告广告的场景

- (instancetype) initWithTvid:(NSString *)tvId albumId:(NSString *)albumId;

/// 初始化vv信息
/// - Parameters:
///   - tvId: 视频Id
///   - albumId: 专辑id
///   - extraParam: 扩展参数 。 示例：@{@"from_impression_id":@"xxxx",@"vv_from":@"s2:xxx;s3:xxx;s4:xxx;ps2:xxx;ps3:xxx;ps4:xxx"};
///     - from_impression_id: 曝光id，微剧传入曝光id。仅站内媒体，外部媒体不需要
///     - vv_from: 来源信息，需要做urlEncode。仅站内媒体，外部媒体不需要
- (instancetype) initWithTvid:(NSString *)tvId albumId:(NSString *)albumId extraParam:(NSString *)extraParam;

@end

NS_ASSUME_NONNULL_END
