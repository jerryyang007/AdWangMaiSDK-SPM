//
//  FTUnifiedNativeAd.h
//  OneAdSDK
//
//  Created by huankuai on 2025/3/18.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <OneAdSDK/FTAdBidProtocol.h>
#import <OneAdSDK/FTVideoAdProtocol.h>
#import <OneAdSDK/FTAdInfoObject.h>
NS_ASSUME_NONNULL_BEGIN
@class FTUnifiedNativeAd;
@protocol FTUnifiedNativeAdDelegate<NSObject>

@optional

/// 广告素材加载成功
- (void)unifiedNativeAdLoadSuccess:(FTUnifiedNativeAd *)unifiedNativeAd;

/// 广告素材加载失败
- (void)unifiedNativeAdLoadFail:(FTUnifiedNativeAd *)unifiedNativeAd error:(NSError *_Nullable)error;

/// 广告展示成功
- (void)unifiedNativeAdDidShow:(FTUnifiedNativeAd *)unifiedNativeAd;

/// 广告点击
- (void)unifiedNativeAdDidClick:(FTUnifiedNativeAd *)unifiedNativeAd;

/// 落地页即将关闭
- (void)unifiedNativeAdLandingPageWillClose:(FTUnifiedNativeAd *)unifiedNativeAd;
/// 落地页已经关闭
- (void)unifiedNativeAdLandingPageDidClose:(FTUnifiedNativeAd *)unifiedNativeAd interactionType:(FTAdInteractionType)type;

@end
@interface FTUnifiedNativeAd : NSObject<FTAdBidProtocol,FTVideoAdProtocol>

// 应用id
@property (nonatomic, copy, nonnull) NSString *appId;
/// 代码位id
@property (nonatomic, copy, nonnull) NSString *slotId;

@property (nonatomic, strong, nullable) NSDictionary *extInfo;

@property (nonatomic, weak) id<FTUnifiedNativeAdDelegate> delegate;

@property (nonatomic, weak) UIViewController *containerVC;

/**
 请求广告数据
 */
- (void)loadAdData;

- (NSArray<FTAdInfoObject *> *)getAdInfoObjects;

/// 注册原生广告可点击视图
/// @param containerView 原生广告容器视图
/// @param clickableViews 可点击视图
- (void)registerContainer:(__kindof UIView *)containerView clickableViews:(NSArray<UIView *> *)clickableViews;

// 注销可点击视图
- (void)unregisterView;
@end

NS_ASSUME_NONNULL_END
