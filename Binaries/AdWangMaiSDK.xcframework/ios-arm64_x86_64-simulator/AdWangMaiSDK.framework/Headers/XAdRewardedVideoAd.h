//
//  XAdRewardedVideoAd.h
//  AdWangMaiSDK
//
//  Created by 周泽浩 on 2023/3/1.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@class XAdRewardedVideoModel;
NS_ASSUME_NONNULL_BEGIN
@protocol XAdRewardedVideoDelegate;

@interface XAdRewardedVideoAd : NSObject

/// 代理
@property (nonatomic,weak) id<XAdRewardedVideoDelegate>delegate;

/// 是否需要满足HTTPS  [可选] 默认为NO
@property (nonatomic,assign) BOOL secure;

/// 是否屏蔽摇一摇，NO或者不赋值，不屏蔽，YES屏蔽
@property (nonatomic, assign) BOOL disableShake;

/// 视频物料是否静音，YES 为静音；默认 NO，与普通加载的实际行为保持一致。
@property (nonatomic,assign) BOOL videoMuted;
//激励视频奖励对象，开启服务端时必传
@property (nonatomic,strong) NSString *userId;
//激励任务扩展字段，可选
@property (nonatomic,strong) NSDictionary *rewardExt;

/// 初始化广告
/// - Parameter adSlotId: 广告位id
- (instancetype)initWithAdSlotId:(NSString *)adSlotId;


/// 请求普通广告；首次调用后实例固定为普通模式，不能再接收 S2S Response。
/// 请求进行中重复调用不会启动新请求或触发本次 LoadError；启用 Debug 日志时输出提示。
/// 当前请求成功或失败后，允许再次调用同模式加载。
- (void)loadAdData;

/// 生成 S2S Token。
- (nullable NSString *)getS2STokenWithAdSlotId:(NSString *)adSlotId;

/// 加载 S2S 广告。接收媒体服务器返回的 S2S JSON。
- (void)loadAdm:(NSString *)adm;

/// 获取当前广告请求 ID，请求尚未发起时返回 nil。
- (nullable NSString *)getRequestId;

/**
 广告是否有效
 @return 广告有效返回YES  广告无效返回NO
 */
- (BOOL)isReady;

/// 展示广告方法
/// @param rootViewController 用于 present 激励视频 VC
- (void)showAdFromRootViewController:(UIViewController *)rootViewController;

/**
 返回广告的eCPM，单位：分
 
 @return 成功返回一个大于等于0的值，-1表示无权限或后台出现异常
 */
- (NSInteger)eCPM;

/// 竞价成功上报，脉盟平台竞胜之后调用，需要在广告请求成功之后,展示之前调用，winInfo脉盟平台竞价获胜信息，可为nil。
/// @param winInfo 竞胜信息 字典类型
- (void)sendWinNotificationWithInfo:(NSDictionary *_Nullable)winInfo;

/// 获取当前广告物料
// material_url: 素材 url 数组
// adTitle: 标题
// adDescription:描述
// crid:素材id/创意id
- (NSDictionary *)getCurrentAdMaterialsInfo;

@end

NS_ASSUME_NONNULL_END
