//
//  FTInterstitialAd.h
//  OneAdSDK
//
//  Created by huankuai on 2025/3/12.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <OneAdSDK/FTAdBidProtocol.h>
NS_ASSUME_NONNULL_BEGIN



@class FTInterstitialAd;
@protocol FTInterstitialAdDelegate<NSObject>

@optional

/// 插屏广告素材加载成功
- (void)interstitialAdLoadSuccess:(FTInterstitialAd *)interstitialAd;

/// 插屏广告素材加载失败
- (void)interstitialAdLoadFail:(FTInterstitialAd *)interstitialAd error:(NSError *_Nullable)error;

/// 插屏广告素材下载到本地成功
- (void)interstitialAdVideoDownloadSuccess:(FTInterstitialAd *)interstitialAd;

/// 插屏广告素材下载到本地失败
- (void)interstitialAdVideoDownloadFail:(FTInterstitialAd *)interstitialAd error:(NSError *_Nullable)error;

/// 插屏广告素材渲染成功
- (void)interstitialAdRenderSuccess:(FTInterstitialAd *)interstitialAd;

/// 插屏广告素材渲染失败
- (void)interstitialAdRenderFail:(FTInterstitialAd *)interstitialAd error:(NSError *_Nullable)error;

/// 插屏广告展示成功
- (void)interstitialAdDidShow:(FTInterstitialAd *)interstitialAd;

/// 插屏广告点击
- (void)interstitialAdDidClick:(FTInterstitialAd *)interstitialAd;

/// 插屏广告关闭
- (void)interstitialAdDidClose:(FTInterstitialAd *)interstitialAd;

/// 插屏广告视频播放完成或者报错.
- (void)interstitialVideoAdDidPlayFinish:(FTInterstitialAd *)interstitialAd didFailWithError:(NSError *_Nullable)error;
/// 落地页即将关闭
- (void)interstitialAdLandingPageWillDisappear:(FTInterstitialAd *)interstitialAd;
/// 落地页已经关闭
- (void)interstitialAdLandingPageDidDisappear:(FTInterstitialAd *)interstitialAd interactionType:(FTAdInteractionType)type;

@end
@interface FTInterstitialAd : NSObject<FTAdBidProtocol>

/// 应用id
@property (nonatomic, copy, nonnull) NSString *appId;
/// 代码位id
@property (nonatomic, copy, nonnull) NSString *slotId;

/**
 可传入插屏背景图色值
 key:kBgColor  value:UIColor
 */
@property (nonatomic, strong, nullable) NSDictionary *extInfo;

@property (nonatomic, weak) id<FTInterstitialAdDelegate> delegate;

/**
 请求广告数据并展示
 */
- (void)loadAndShowInterstitialViewInRootViewController:(UIViewController *)viewController;

/**
 请求广告数据
 */
- (void)loadAdData;

/**
 展示广告
 请在广告素材加载成功之后调用，即interstitialAdLoadSuccess 或者 interstitialAdVideoDownloadSuccess回调之后
 */
- (void)showInterstitialViewInRootViewController:(UIViewController *)viewController;

/**
 获取广告价格，单位：分
 请在广告素材加载成功之后调用，即splashAdLoadSuccess回调之后
 */
- (NSString *)getECPM;

/**
 获取广告数据
 */
- (NSDictionary *)getAdExtInfo;

@end

NS_ASSUME_NONNULL_END
