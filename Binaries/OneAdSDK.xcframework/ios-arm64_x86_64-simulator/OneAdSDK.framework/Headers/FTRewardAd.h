//
//  FTRewardAd.h
//  OneAdSDK
//
//  Created by huankuai on 2025/4/27.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <OneAdSDK/FTAdBidProtocol.h>
NS_ASSUME_NONNULL_BEGIN
@class FTRewardAd;
@protocol FTRewardAdDelegate<NSObject>

@optional

/// 激励广告数据加载成功
- (void)rewardAdLoadSuccess:(FTRewardAd *)rewardAd;

/// 激励广告数据加载失败
- (void)rewardAdLoadFail:(FTRewardAd *)rewardAd error:(NSError *_Nullable)error;

/// 激励广告素材下载到本地成功
- (void)rewardAdVideoDownloadSuccess:(FTRewardAd *)rewardAd;

/// 激励广告素材下载到本地失败
- (void)rewardAdVideoDownloadFail:(FTRewardAd *)rewardAd error:(NSError *_Nullable)error;

/// 激励广告素材渲染成功
- (void)rewardAdRenderSuccess:(FTRewardAd *)rewardAd;

/// 激励广告素材渲染失败
- (void)rewardAdRenderFail:(FTRewardAd *)rewardAd error:(NSError *_Nullable)error;

/// 激励广告展示成功
- (void)rewardAdDidShow:(FTRewardAd *)rewardAd;

/// 激励广告点击
- (void)rewardAdDidClick:(FTRewardAd *)rewardAd;

/// 激励广告关闭
- (void)rewardAdDidClose:(FTRewardAd *)rewardAd;

// 激励广告达成或失败，以此回调作为奖励依据.
- (void)rewardAdDidRewardEffective:(FTRewardAd *)rewardAd error:(NSError *_Nullable)error;;
/// 激励广告视频播放完成或者报错.
- (void)rewardVideoAdDidPlayFinish:(FTRewardAd *)rewardAd didFailWithError:(NSError *_Nullable)error;
/// 落地页即将关闭
- (void)rewardAdLandingPageWillDisappear:(FTRewardAd *)rewardAd;
/// 落地页已经关闭
- (void)rewardAdLandingPageDidDisappear:(FTRewardAd *)rewardAd interactionType:(FTAdInteractionType)type;;

@end
@interface FTRewardAd : NSObject<FTAdBidProtocol>

/// 应用id
@property (nonatomic, copy, nonnull) NSString *appId;
/// 代码位id
@property (nonatomic, copy, nonnull) NSString *slotId;
/**
 奖励文案定制可以传入下面key-value
 leftText:倒计时数字左边文案，eg：奖励将于
 rightText:倒计时数字右边文案，eg：秒后发放
 completeText:奖励达成后的文案，eg：恭喜获取奖励
 exitLeftText:关闭挽留页面，倒计时数字左边文案，eg：奖励将于
 exitRightText:关闭挽留页面，倒计时数字右边文案，eg：秒后发放
 exitCompleteText:关闭挽留页面，奖励达成的文案，eg：恭喜获取奖励
 */
@property (nonatomic, strong, nullable) NSDictionary *extInfo;

@property (nonatomic, weak) id<FTRewardAdDelegate> delegate;

/**
 服务端callback权益解锁参数，按需传入
 */
@property (nonatomic, strong, nullable) NSDictionary *rewardParamDict;
/**
 服务端callback权益解锁返回数据，按需使用
 */
@property (nonatomic, strong, nullable) NSDictionary *rewardResponseDict;

/**
 请求广告数据并展示
 */
- (void)loadAndShowRewardViewInRootViewController:(UIViewController *)viewController;

/**
 请求广告数据
 */
- (void)loadAdData;

/**
 展示广告
 请在广告素材加载成功之后调用，即interstitialAdLoadSuccess 或者 interstitialAdVideoDownloadSuccess回调之后
 */
- (void)showRewardViewInRootViewController:(UIViewController *)viewController;
/**
 获取广告价格，单位：分
 请在广告素材加载成功之后调用，即splashAdLoadSuccess回调之后
 */
- (NSString *)getECPM;

/**
 关闭广告
 */
- (void)rewardAdClose;

/**
 获取广告数据
 */
- (NSDictionary *)getAdExtInfo;

@end

NS_ASSUME_NONNULL_END
