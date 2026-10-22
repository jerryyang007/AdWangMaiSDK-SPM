//
//  QYExpressInterstitial.h
//  QySdk
//
//  Created by liuyulei on 2021/10/14.
//  Copyright © 2021 iqiyi. All rights reserved.
//  注意：当前类仅爱奇艺内部使用，暂时不对外开放，外部媒体不支持接入！！！
#import <QySdk/IAdSdk.h>
#import "QYExpressBase.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

// 暂停广告区域
typedef NS_ENUM(NSInteger, Interstitial_Area) {
    Interstitial_Area_Close_Button                      = 0,  // 关闭按钮
    Interstitial_Area_Episode_Player_Graphic            = 1,  // 盖在暂停max层级上的，缩小到右下角的剧集区域
    Interstitial_Area_BackgroundImg                     = 2,  // 新版暂停Max的背景图
};

@interface QYExpressInterstitial : QYExpressBase

/// 初始化--横屏插屏广告
/// @param rootController 当前控制器，保证正常跳转落地页
/// @param plt 屏幕状态   QY_SPP_PLT_LANDSCAPE-横屏     QY_SPP_PLT_PORTRAIT-竖屏
- (instancetype) initWithRootController:(UIViewController *)rootController plt:(QY_SPP_PLT)plt;

/// 初始化成功后，展示插屏广告
/// @param view 承载视图
/// @param plt 屏幕状态
- (void) presentInView:(UIView *)view plt:(QY_SPP_PLT)plt;

/// 重置广告frame
/// @param view 承载视图
/// @param plt 屏幕状态   QY_SPP_PLT_LANDSCAPE-横屏     QY_SPP_PLT_PORTRAIT-竖屏
- (void) resetFrameInView:(UIView *)view plt:(QY_SPP_PLT)plt;
// 销毁广告
- (void) dismiss;

- (QY_SSP_PAUSE_AD_TYPE) getActionType;    // 获取actionType，0-普通暂停   5-代表暂停Max  6-新版暂停Max
- (CGRect) getInterstitialFrame;// 获取广告的frame，注意，请在presentInView之后调用！！！
- (CGRect) getEpisodePlayerFrame;// 获取暂停Max广告缩小后的播放器frame，仅用于暂停Max播放器需要缩小的场景
- (void) closeInterstitial:(Interstitial_Area)area; // 暂停Max，点击右下角剧集时调用，通知SDK，SDK处理pingback的发送
- (QY_ORDER_ITEM_TYPE) getOrderItemType;

- (void) hidden;                // 广告隐藏
- (void) show;                  // 广告隐藏后重新展示

- (void) setMute:(BOOL)mute;    // 设置静音
- (BOOL) getMute;               // 获取静音状态   YES：静音   NO：非静音

- (void) startVideo;            // 开始视频
- (void) pauseVideo;            // 暂停视频

@end

NS_ASSUME_NONNULL_END
