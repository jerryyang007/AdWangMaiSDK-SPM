//
//  FTNativeTemplatedAd.h
//  OneAdSDK
//
//  Created by huankuai on 2025/4/25.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <OneAdSDK/FTAdBidProtocol.h>
#import <OneAdSDK/FTVideoAdProtocol.h>
#import <OneAdSDK/FTNativeTemplateView.h>


NS_ASSUME_NONNULL_BEGIN

@class FTNativeTemplatedAd;
@protocol FTNativeTemplatedAdDelegate<NSObject>

@optional

/// 信息流模版广告素材加载成功
- (void)nativeTempAdLoadSuccess:(FTNativeTemplatedAd *)templatedAd views:(NSArray<__kindof FTNativeTemplateView *> *)views;

/// 信息流模版广告素材加载失败
- (void)nativeTempAdLoadFail:(FTNativeTemplatedAd *)templatedAd error:(NSError *_Nullable)error;


/// 信息流模版广告素材渲染成功
- (void)nativeTempAdRenderSuccess:(FTNativeTemplateView *)templateView;

/// 信息流模版广告素材渲染失败
- (void)nativeTempAdRenderFail:(FTNativeTemplateView *)templateView error:(NSError *_Nullable)error;

/// 信息流模版广告展示成功
- (void)nativeTempAdDidShow:(FTNativeTemplateView *)templateView;

/// 信息流模版广告点击
- (void)nativeTempAdDidClick:(FTNativeTemplateView *)templateView;

/// 信息流模版广告关闭
- (void)nativeTempAdDidClose:(FTNativeTemplateView *)templateView;

/// 信息流模版广告视频播放完成或者报错.
- (void)nativeTempVideoAdDidPlayFinish:(FTNativeTemplateView *)templateView didFailWithError:(NSError *_Nullable)error;

/// 落地页已经关闭
- (void)nativeTempAdLandingPageDidDisappear:(FTNativeTemplateView *)templateView  interactionType:(FTAdInteractionType)type;
@end

@interface FTNativeTemplatedAd : NSObject

// 应用id
@property (nonatomic, copy, nonnull) NSString *appId;
/// 代码位id
@property (nonatomic, copy, nonnull) NSString *slotId;

/* 广告视图尺寸
模版信息流的尺寸adSize建议宽度设置为屏宽 高度设置为0或者设置平台勾选的高度 不要随意设置尺寸大小否则有可能出现拉取失败或者广告变形的情况
沉浸流模版尺寸完全按照传入adSize的值去渲染
 */
@property (nonatomic,assign) CGSize adSize;

@property (nonatomic, strong, nullable) NSDictionary *extInfo;

@property (nonatomic, weak) id<FTNativeTemplatedAdDelegate> delegate;

@property (nonatomic, weak) UIViewController *containerVC;
/**
 获取广告价格，单位：分
 请在广告素材加载成功之后调用，即splashAdLoadSuccess回调之后
 */
- (NSString *)getECPM;

/**
 请求广告数据
 */
- (void)loadAdData;


@end

NS_ASSUME_NONNULL_END
