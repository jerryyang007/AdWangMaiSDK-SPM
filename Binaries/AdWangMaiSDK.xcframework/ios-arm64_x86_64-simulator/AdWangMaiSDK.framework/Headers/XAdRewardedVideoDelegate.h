//
//  XAdRewardedVideoDelegate.h
//  AdWangMaiSDK
//
//  Created by 周泽浩 on 2023/3/1.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol XAdRewardedVideoDelegate <NSObject>

@optional
/// 发起请求
- (void)rewardVideoOnAdRequest;

/// 请求成功
- (void)rewardVideoOnAdReady;

/// 请求失败
/// - Parameter error: 错误信息
- (void)rewardVideoOnError:(NSError *)error;

///广告素材下载成功
- (void)rewardVideoOnAdDownloadSuccess;

///广告素材下载失败
///@param error 错误信息
- (void)rewardVideoOnAdDownloadFail:(NSError *)error;

///曝光失败
- (void)rewardVideoOnExposureFail:(NSError *)error;

/// 展示
- (void)rewardVideoOnExposure;

/// 点击
- (void)rewardVideoOnClick;

/// 关闭
/// - Note: 已达标但服务端验证尚未完成时若先触发关闭（或控制器被释放），SDK 丢弃该次在途奖励，不再补发 rewardVideoOnRewarded:。
- (void)rewardVideoOnAdClose;

/// 播放失败
/// - Parameter error: 错误信息
- (void)rewardVideoPlayError:(NSError *)error;

/// 播放完成
- (void)rewardVideoOnVideoComplete;

/// 奖励回调
/// - Parameter rewards: 奖励；开启服务端回调后按 rewards 中的 isVerify 字段判断奖励是否有效。
/// - Note: 仅在控制器关闭前完成验证时回调；先关闭或释放控制器时，已达标奖励会被丢弃且本回调不再补发。
- (void)rewardVideoOnRewarded:(NSDictionary *)rewards;
@end

NS_ASSUME_NONNULL_END
