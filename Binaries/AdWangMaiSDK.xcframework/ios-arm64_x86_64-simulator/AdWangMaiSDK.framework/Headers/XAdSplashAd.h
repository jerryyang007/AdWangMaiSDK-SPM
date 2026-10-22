//
//  XAdSplashAd.h
//  WangMaiAdSDK
//
//  Created by 周泽浩 on 2023/2/13.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol XAdSplashDelegate;

@interface XAdSplashAd : NSObject

/// 开屏协议
@property (nonatomic,weak) id<XAdSplashDelegate>delegate;

/// 是否需要满足HTTPS  [可选] 默认为NO
@property (nonatomic, assign) BOOL secure;

/// 是否屏蔽摇一摇，NO或者不赋值，不屏蔽，YES屏蔽
@property (nonatomic, assign) BOOL disableShake;

/// 是否屏蔽扭一扭，NO或者不赋值，不屏蔽，YES屏蔽
@property (nonatomic, assign) BOOL disableTwist;

/// 开屏广告停留时长（仅脉盟预算支持）
@property (nonatomic, assign) NSInteger stayTime;
 
/// 底部自定义窗口  [可选]
@property (nonatomic, weak) UIView *bottomView;

/// 视频类型时，是否静音。默认 YES。loadAdData 前设置。
@property (nonatomic, assign) BOOL videoMuted;

/// 构造方法
/// - Parameter adSlotId: 广告位id
- (instancetype)initWithAdSlotId:(NSString *)adSlotId;

/// 普通广告加载；首次调用后实例固定为普通模式，不能再接收 S2S Response。
/// 请求进行中重复调用不会启动新请求或触发本次 LoadError；启用 Debug 日志时输出提示。
/// 当前请求成功或失败后，允许再次调用同模式加载。
/// 只加载不展示，成功后调用 showAdInWindow:。
- (void)loadAdData;

/// 生成 S2S Token。
- (nullable NSString *)getS2STokenWithAdSlotId:(NSString *)adSlotId;

/// 加载 S2S 广告。接收媒体服务器返回的 S2S JSON。
- (void)loadAdm:(NSString *)adm;

/// 已废弃；该方法不再发起请求并始终返回 nil，同时通过 splashOnError: 返回迁移提示。
/// 请使用 getS2STokenWithAdSlotId: 生成新版 S2S Token。
- (nullable NSString *)getBuyerIdWithAdSlotId:(NSString *)adSlotId __attribute__((deprecated("请使用 getS2STokenWithAdSlotId: 和 loadAdm:")));

/// 已废弃；该方法对 nil 和非 nil 参数均不发起请求，同时通过 splashOnError: 返回迁移提示。
/// 普通加载请使用 loadAdData，S2S 请使用 loadAdm:。
- (void)preloadAdDataWithServerBidToken:(nullable NSString *)serverBidToken __attribute__((deprecated("请使用 loadAdData 或 loadAdm:")));
/**
 广告是否有效
 @return 广告有效返回YES  广告无效返回NO
 */
- (BOOL)isReady;

/// 展示广告
/// @param window 应用的window窗口 [必传]
- (void)showAdInWindow:(UIWindow *)window;

/**
 返回广告的eCPM，单位：分
 
 @return 成功返回一个大于等于0的值，-1表示无权限或后台出现异常
 */
- (NSInteger)eCPM;

/// 竞价成功上报，脉盟平台竞胜之后调用，需要在广告请求成功之后、展示之前调用，winInfo 为可空的竞胜信息；新版 S2S 由服务端完成竞胜竞败，无需调用。
/// @param winInfo 竞胜信息 字典类型
- (void)sendWinNotificationWithInfo:(NSDictionary *_Nullable)winInfo;

/// 获取当前广告物料
// material_url: 素材 url 数组
// adTitle: 标题
// adDescription:描述
// crid:素材id/创意id
- (NSDictionary *)getCurrentAdMaterialsInfo;

/// 获取当前广告请求 ID，请求尚未发起时返回 nil。
- (nullable NSString *)getRequestId;

/// 广告销毁（仅脉盟预算支持）
- (void)destroy;

@end

NS_ASSUME_NONNULL_END
