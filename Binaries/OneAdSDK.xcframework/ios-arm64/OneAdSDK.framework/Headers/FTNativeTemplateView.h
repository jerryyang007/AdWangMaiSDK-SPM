//
//  FTNativeTemplateView.h
//  OneAdSDK
//
//  Created by huankuai on 2025/7/15.
//

#import <UIKit/UIKit.h>
#import <OneAdSDK/FTAdBidProtocol.h>
NS_ASSUME_NONNULL_BEGIN


@interface FTNativeTemplateView : UIView<FTAdBidProtocol>


/**
 * 是否渲染完毕
 */
@property (nonatomic, assign, readonly) BOOL isReady;

/**
 * 是否是视频模板广告
 */
@property (nonatomic, assign, readonly) BOOL isVideoAd;

/**
 *  viewControllerForPresentingModalView
 *  详解：[必选]开发者需传入用来弹出目标页的ViewController，一般为当前ViewController
 */
@property (nonatomic, weak) UIViewController *rootViewController;

/**
 *  广告是否有效，以下情况会返回NO，建议在调用render之前判断，当为NO时render失败
 *  a.广告过期
 */
@property (nonatomic, readonly) BOOL isAdValid;

/**
 *  扩展参数  [render] 之前配置
 *  配置视频是否自动重播 key : "autoReplay"  value: "1"
 *  沉浸流顶部UI元素距顶部的距离: "immersiveEdgeTop"  value: "80.00"
 */
@property (nonatomic, strong, nullable) NSDictionary *extInfo;

/**
 *[必选]
 *原生模板广告渲染
 */
- (void)render;

/**
 * 视频模板广告时长，单位 ms
 */
- (CGFloat)videoDuration;

/**
 * 视频模板广告已播放时长，单位 ms
 */
- (CGFloat)videoPlayTime;

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
