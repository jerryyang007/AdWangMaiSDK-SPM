//
//  QySdk.h
//  Cupid
//
//  Created by Peiran Zhang on 2020/3/17.
//  Copyright © 2020 iqiyi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QySdk/QYBannerView.h>
#import <QySdk/QYExpressRoll.h>
#import <QySdk/QYExpressBanner.h>
#import <QySdk/QYExpressReward.h>
#import <QySdk/QYExpressSplash.h>
#import <QySdk/QYExpressInterstitial.h>
#import <QySdk/QYFullScreenAd.h>
#import <QySdk/QYTaskPageAd.h>
#import <QySdk/QYNativeBanner.h>
#import <QySdk/QYCupidNative.h>
#import <QySdk/QYIADUserInfo.h>
#import <QySdk/QYAdSlot.h>
#import <QySdk/QYNativeAd.h>
#import <QySdk/QYNativeAdDelegate.h>
#import <QySdk/QYNativeSlotManager.h>
#import <QySdk/QYNativeSlotManagerDelegate.h>
#import <QySdk/QYExpressBase.h>

#define QY_LOG_NONE      0
#define QY_LOG_ERROR     1
#define QY_LOG_DEBUG     2
extern NSString *EXTRA_KEY_COVER_URL;
extern NSString *STATUS_KEY_DEVICE_PRINT;
extern NSString *STATUS_KEY_MOBILE_KEY;
extern NSString *STATUS_KEY_IQID;
extern NSString *STATUS_KEY_SSID;
extern NSString *STATUS_KEY_PERSONALIZED_AD_SWITCH;
extern NSString *STATUS_KEY_ADX_AD_SWITCH;
extern NSString *STATUS_KEY_CIDFA;
extern NSString *STATUS_KEY_WX_OPENSDK_VERSION;
extern NSString *STATUS_KEY_USER_TAG;
extern NSString *STATUS_KEY_NEW_USER_TYPE;

//adc
extern NSString *PROP_KEY_NEXT_REQUEST_ADS;
extern NSString *PROP_KEY_FIRST_AD_INDEX;
extern NSString *PROP_KEY_AD_INTERVAL;

//property相关key
extern NSString *PROP_KEY_REWARD_COUNT; //激励金额
extern NSString *PROP_KEY_CLICK_AREA; //点击区域
extern NSString *PROP_KEY_TVID;
extern NSString *PROP_KEY_ALBUMID;
extern NSString *PROP_KEY_IMPRESSION_ID;
extern NSString *PROP_KEY_REWARD_AMOUNT;
extern NSString *PROP_KEY_REWARD_MSG;
extern NSString *PROP_KEY_REWARD_STATUS;
extern NSString *PROP_KEY_NEW_USER_FLAG;
extern NSString *PROP_KEY_RISK_LEVEL;
extern NSString *PROP_KEY_AD_SOURCE;
extern NSString *PROP_KEY_FROM_CACHE;
extern NSString *PROP_KEY_PRICE;
extern NSString *PROP_KEY_CAN_CACHE;

//广告级别相关Key
extern NSString *INFO_KEY_BOOK_ID;

typedef enum : NSUInteger {
    SSP_AD_EVENT_IMPRESSION = 0,
    SSP_AD_EVENT_CLICK = 1
} SSP_AD_EVENT;

@interface IAdSdk : NSObject

/// 初始化SDK-异步
+ (void) start;

/// 设置媒体id
+ (void) setAppId:(NSString *)appId;

/// 设置日志级别，0-不输出日志，1-仅输出错误日志，2-输出debug日志，建议debug模式开启，方便开发联调
+ (void) setDebugLevel:(NSInteger)lvl;

/// 设置日志路径，建议Document下新建文件夹存储
+ (void) setLogPath:(NSString *)path;

/// 设置idfa
+ (void) setIDFA:(NSString *)idfa;

/// 主动获取idfa，会触发隐私弹窗
+ (void) initService;

/// 设置用户信息，已支持的key如下
/// - Parameter info:
///     @"longitude"，实时的地理位置经度，值为字符串格式的经度值，比如@“116.677653”
///     @"latitude"，实时的地理位置纬度，值为字符串格式的纬度值，比如@"39.365678"
+ (void) setExtInfo:(NSDictionary *)info;

/// 性别
+ (void) setGender:(NSString *)gender;

/// 年龄
+ (void) setAge:(NSInteger)age;

/// App模式，0/不传-普通模式，1-最小功能模式，2-长辈模式，3-无障碍模式，4-少儿模式
+ (void) setAppMode:(NSInteger )appMode;

/// 请求地理位置信息，会触发隐私弹窗
+ (void)requestLocationService __attribute__((deprecated("This method is deprecated.")));

/// 是否开启开机屏预请求，默认为NO
+ (void) setSplashForeRequest:(BOOL)b;

/// 是否测试流量
+ (void) setTestMode:(BOOL)test;

/// 媒体自定义渠道id
+ (void) setChannelId:(NSString *)channelId;

/// 清楚缓存
+ (void) clearCache;

/// 设置屏幕方向
+ (void) setAppOrientation:(UIInterfaceOrientation)orientation;

/// 对于banner、激励广告，可配置静音播放。该接口传入YES，则在静音播放状态下不会打断原有后台音频播放。此时静音时的音频模式会被配置成·AVAudioSessionCategoryAmbient·
+ (void) setAudioMix:(BOOL)mix;

/// App在AppStore中的AppleId
+ (void) setItunesAppleId:(NSString *)appleId;

/// 获取广告SDK的版本号
+ (NSString *) sdkVersion;


/// **  以下参数，外部媒体不需要关注 **
+ (void) setUaaUserId:(NSString *)uaaUserId;
+ (void) setSdkStatus:(NSDictionary *)status;
+ (void) setKeyWords:(NSArray *)words;
+ (NSArray *) getAdLogFilePaths;
+ (void) setUserInfo:(QYIADUserInfo *)usrInfo;
+ (void) reportWaterfallAdEvent:(SSP_AD_EVENT)event express:(QYExpressBase *)express properties:(NSString *)properties;

@end

