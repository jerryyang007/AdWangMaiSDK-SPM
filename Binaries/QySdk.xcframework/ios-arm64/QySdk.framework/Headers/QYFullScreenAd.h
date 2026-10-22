//
//  QYFullScreenAd.h
//  QySdk
//
//  Created by liuyulei on 2025/4/14.
//  Copyright © 2025 iqiyi. All rights reserved.
//

#import <QySdk/IAdSdk.h>

NS_ASSUME_NONNULL_BEGIN

@interface QYFullScreenAd : QYExpressBase

/// 初始化插屏
/// - Parameters:
///   - slotId: 代码位id
///   - isPreload: 是否预请求
///   - isMute: 是否静音播放
- (instancetype) initWithSlotId:(NSString *)slotId isPreload:(BOOL)isPreload isMute:(BOOL)isMute;

/// 加载广告数据
- (void) loadData;

/// 展示插屏广告
/// - Parameter rootViewController: 当前展示的控制器，用于展示插屏和跳转落地页。请在主线程调用
- (void) showAdFromeRootViewController:(UIViewController *)rootViewController;

// 销毁广告
- (void) dismiss;

@end

NS_ASSUME_NONNULL_END
