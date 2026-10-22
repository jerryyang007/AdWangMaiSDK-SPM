//
//  OneAdSDK
//
//  Created by guangkuo.zgk on 2024/10/30.
//  Copyright © 2024 fanti.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <OneAdSDK/FTAdBidProtocol.h>

NS_ASSUME_NONNULL_BEGIN

@class FTSplashAd;
@protocol FTSplashAdDelegate<NSObject>

@optional

/// 开屏广告素材加载成功
- (void)splashAdLoadSuccess:(FTSplashAd *)splashAd;

/// 开屏广告素材加载失败
- (void)splashAdLoadFail:(FTSplashAd *)splashAd error:(NSError *_Nullable)error;

/// 开屏广告素材渲染成功
- (void)splashAdRenderSuccess:(FTSplashAd *)splashAd;

/// 开屏广告素材渲染失败
- (void)splashAdRenderFail:(FTSplashAd *)splashAd error:(NSError *_Nullable)error;

/// 开屏广告展示成功
- (void)splashAdDidShow:(FTSplashAd *)splashAd;

/// 开屏广告点击
- (void)splashAdDidClick:(FTSplashAd *)splashAd;

/// 开屏广告跳过
- (void)splashAdDidSkip:(FTSplashAd *)splashAd;

/// 开屏广告倒计时结束（广告自动关闭）
- (void)splashAdDidFinish:(FTSplashAd *)splashAd;

/// 开屏广告关闭（包含点击广告+点击跳过+倒计时结束自动关闭等所有关闭情况）
- (void)splashAdDidClose:(FTSplashAd *)splashAd;

/// 开屏广告落地页已经关闭
- (void)splashAdLandingPageDidDisappear:(FTSplashAd *)splashAd interactionType:(FTAdInteractionType)type;

/// 开屏广告视频播放完成或者报错.
- (void)splashVideoAdDidPlayFinish:(FTSplashAd *)splashAd didFailWithError:(NSError *_Nullable)error;

/**
 * 开屏广告剩余时间回调
 */
- (void)splashAdCountdownTime:(NSUInteger)time;
@end

@interface FTSplashAd : NSObject<FTAdBidProtocol>
/// 媒体id
@property (nonatomic, copy, nullable) NSString *mediaId;
/// 应用id
@property (nonatomic, copy, nonnull) NSString *appId;
/// 代码位id
@property (nonatomic, copy, nonnull) NSString *slotId;

//@property (nonatomic, weak) UIViewController *containerVC;
/**
 1.可传入自定义底部视图，需要设置视图宽高
 key:kBottomView  value:UIView
 2. key:@"autoLocateTopVC" 是否由SDK自主查找顶层VC弹出落地页，  value:@"1" :自主查找,   value值不为@"1"时由传入的viewController弹出落地页
 */
@property (nonatomic, strong, nullable) NSDictionary *extInfo;

@property (nonatomic, weak) id<FTSplashAdDelegate> delegate;

/**
 *  S2S bidding后获取到token再调用此方法加载广告
 *  @param token  通过Server Bidding请求回来的token
 */
- (void)loadAdWithToken:(NSString *)token;

/**
 请求广告数据并展示
 */
- (void)loadAndShowSplashViewInRootViewController:(UIViewController *)viewController;

/**
 请求广告数据
 */
- (void)loadAdData;

/**
 展示开屏广告
 请在广告素材加载成功之后调用，即splashAdLoadSuccess回调之后
 */
- (void)showSplashViewInRootViewController:(UIViewController *)viewController;
/**
 获取广告价格，单位：分
 请在广告素材加载成功之后调用，即splashAdLoadSuccess回调之后
 注意：此方法仅为客户端竞价使用
 */
- (NSString *)getECPM;

/**
 获取广告数据
 */
- (NSDictionary *)getAdExtInfo;

@end


NS_ASSUME_NONNULL_END
