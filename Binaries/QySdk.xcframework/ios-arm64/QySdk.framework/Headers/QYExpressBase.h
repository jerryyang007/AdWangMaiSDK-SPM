//
//  QYExpressBase.h
//  Cupid_DEMO
//
//  Created by Peiran Zhang on 2020/5/15.
//  Copyright © 2020 iqiyi. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "QYAssociateVideoInfo.h"
#import "QYCommonDef.h"

NS_ASSUME_NONNULL_BEGIN

@class QYWrapperHolder;
@class QYCupidWrapper;
@class QYCupidSlot;
@class QYCupid;
@class QYNetProtocol;

typedef NS_ENUM(NSInteger, QY_JUMP_STYLE) {
    QY_JUMP_STYLE_NORMAL        = 0, // 普通跳转
    QY_JUMP_STYLE_SECOND_PAGE   = 1  // 跳转二级页
};

//交互类型
typedef NS_ENUM(NSInteger, AdInteractiveType) {
    CLICK_CLOSE_BUTTON              = 0,  // 暂停Max点击关闭按钮
    CLICK_FOR_CONTINUE              = 1,  // 暂停Max点击广告内容区域
    REWARD_LOAD_NEXT                = 2,  // 激励视频再看一个
};

typedef NS_ENUM(NSInteger, QY_PULLING_PAGETYPE) { //三方拉起类型
    QY_PULLING_TYPE_NONE          = 0, // 落地页类型未知
    QY_PULLING_TYPE_WEBVIEW       = 1, // WEBVIEW
    QY_PULLING_TYPE_STORE         = 2, // app store
    QY_PULLING_TYPE_DPLINK        = 3, // 第三方应用
    QY_PULLING_TYPE_SAFARI        = 4, // 第三方应用
    QY_PULLING_TYPE_REGISTER      = 5, // 注册制
};

typedef NS_ENUM(NSInteger, QY_ALI_SLOT_TYPE) {
    QY_ALI_SLOT_TYPE_UNKNOWN            = 0,
    QY_ALI_SLOT_TYPE_ROLL               = 1,
    QY_ALI_SLOT_TYPE_BANNER             = 2,
    QY_ALI_SLOT_TYPE_SPLASH             = 3,
    QY_ALI_SLOT_TYPE_REWARD             = 4,
    QY_ALI_SLOT_TYPE_NATIVE_BANNER      = 5,
    QY_ALI_SLOT_TYPE_INTERSTITIAL       = 6,
    QY_ALI_SLOT_TYPE_FULLSCREEN         = 7,
    QY_ALI_SLOT_TYPE_TASKPAGE           = 8,
};

//广告错误码
typedef NS_ENUM(NSInteger, QyAdErrorCode) {
    QyAdErrorUnknown = 0, //未知错误
    QyAdErrorRequestError = 1, //网络请求失败
    QyAdErrorParseError = 2, // 数据解析失败
    QyAdErrorNoAds = 3, //没有广告
    QyAdErrorCreativeError = 4 //广告素材加载失败
};

@class QYExpressBase;

@protocol QYExpressDelegate <NSObject>
@optional

#pragma mark - 回调中带有实例对象
- (void) onExpressLoadSuccess:(QYExpressBase *)express;
- (void) onExpressLoadFailed:(QYExpressBase *)express;
- (void) onExpressShow:(QYExpressBase *)express;
- (void) onExpressPlayStart:(QYExpressBase *)express;
- (void) onExpressPlayEnd:(QYExpressBase *)express;
- (void) onExpressPlayError:(QYExpressBase *)express;
- (void) onExpressClosed:(QYExpressBase *)express;
- (void) onExpressClicked:(QYExpressBase *)express obj:(id __nullable)obj;
- (void) onExpressInteractived:(QYExpressBase *)express type:(AdInteractiveType)type;
//子页面关闭回调：仅支持QY_PULLING_TYPE_WEBVIEW和QY_PULLING_TYPE_STORE两种类型
- (void) onExpressSubPageClosed:(QYExpressBase *)express type:(QY_PULLING_PAGETYPE)type;
- (void) onExpressSubPageOpen:(QYExpressBase *)express type:(QY_PULLING_PAGETYPE)type;
- (void) onExpressPreReward:(QYExpressBase *)express extraInfo:(NSDictionary *)extraInfo;
- (void) onExpressReward:(QYExpressBase *)express extraInfo:(NSDictionary *)extraInfo;
- (void) onExpressGoBack:(QYExpressBase *)express;

#pragma mark - 即将废弃接口
- (void) onExpressLoadFailed __attribute__((deprecated("即将废弃，请使用 onExpressLoadFailed: 替代")));
- (void) onExpressShow __attribute__((deprecated("即将废弃，请使用 onExpressShow: 替代")));
- (void) onExpressPlayStart __attribute__((deprecated("即将废弃，请使用 onExpressPlayStart: 替代")));
- (void) onExpressPlayEnd __attribute__((deprecated("即将废弃，请使用 onExpressPlayEnd: 替代")));
- (void) onExpressPlayError __attribute__((deprecated("即将废弃，请使用 onExpressPlayError: 替代")));
- (void) onExpressClosed __attribute__((deprecated("即将废弃，请使用 onExpressClosed: 替代")));
- (void) onExpressClicked:(id __nullable)obj __attribute__((deprecated("即将废弃，请使用 onExpressClicked:obj: 替代")));
- (void) onExpressInteractived:(AdInteractiveType)type __attribute__((deprecated("即将废弃，请使用 onExpressInteractived:type: 替代")));
- (void) onExpressSubPageClosed:(QY_PULLING_PAGETYPE)type __attribute__((deprecated("即将废弃，请使用 onExpressSubPageClosed:type: 替代")));
- (void) onExpressSubPageOpen:(QY_PULLING_PAGETYPE)type __attribute__((deprecated("即将废弃，请使用 onExpressSubPageOpen:type: 替代")));
- (void) onExpressReward:(NSDictionary *)extraInfo __attribute__((deprecated("即将废弃，请使用 onExpressReward:extraInfo: 替代")));

@end

@interface QYExpressBase : NSObject
@property(nonatomic, weak) UIViewController *rootController;
@property(nonatomic, copy) NSString *bundleId;      //identifier of unique ad obj
@property(nonatomic, copy) NSString *slotId;        //ali slot id
@property(nonatomic, copy) NSString *channelId;     //频道ID，极速版激励视频要传入不同的频道值，v2.8.5
@property(nonatomic, copy) NSString *wrapperId;     //identifier of unique resp, as m-key
@property(nonatomic, copy) NSString *videoId;       //video id defined by media
@property(nonatomic, copy) NSString *videoEventId;  //video event id defined by i
@property(nonatomic, copy) NSString *sessionId;
@property(nonatomic, assign) NSInteger price;

@property(nonatomic, assign) QY_ALI_SLOT_TYPE iSlotType;    //ali slot type
@property(nonatomic, assign) NSInteger requestCount; //how many ads to req
@property(nonatomic, assign) NSInteger reqDuration;  //time req spend
@property(nonatomic, assign) NSInteger reqTimeOut;  //how long to req
@property(nonatomic, assign) NSInteger retryTimes;  //how many times to req
@property(nonatomic, assign) NSInteger skipAds;     //跳过的广告个数，对应mixer sk字段
@property(nonatomic, assign) BOOL isAdReady;
@property(nonatomic, assign) NSInteger funType; //联盟SDK根据这个字段，1-判断是仅出1个广告场景，2-可以出广告广告的场景
@property(nonatomic, strong) NSDictionary *extraInfo;
@property(nonatomic, strong) QYAssociateVideoInfo *videoInfo;
@property(nonatomic, assign) BOOL isNativeAd;
@property(nonatomic, assign) BOOL isPreload;
@property(nonatomic, assign) BOOL isNewEmpty;
@property(nonatomic, assign) QY_SPP_PLT plt;
@property(nonatomic, assign) NSInteger rixCount;                // 广告的位次--暂停
@property(nonatomic, assign) NSInteger ptCount;                 // 当次暂停请求的次数--暂停
@property(nonatomic, assign) NSInteger siCount;                 // 当次vv暂停的次数--暂停
@property(nonatomic, strong) NSMutableArray *clickableViews;
@property(nonatomic, strong) UIView *container;
@property(nonatomic, assign) NSInteger currentAdIndex;
@property(nonatomic, assign) NSInteger totalAdCount;
@property(nonatomic, strong) NSArray<QYCupid *> *playableAds;

@property(nonatomic, strong) NSMutableSet *realRidRecord;
@property(nonatomic, weak) id<QYExpressDelegate> delegate;

- (NSInteger) getPrice;//价格信息，单位：分/千次曝光
- (NSDictionary *) getExtra;//获取额外信息
- (void) loadData;
- (void) loadDataWithToken:(NSString *)token;
- (void) loadDataRealTime:(BOOL)realtime;
- (void) loadDataRealTime:(BOOL)realtime withToken:(NSString *)token;
// 当前广告是否有效
- (BOOL) isValid;
- (BOOL) isLastAd;
- (BOOL) isFirstAd;
- (void) playNextAd;
- (void) dealWithClickEvent:(QYCupid *)ad prop:(NSDictionary *)prop jumpStyle:(QY_JUMP_STYLE)jStyle extend:(NSDictionary * __nullable)ext;
- (void) handleEmptyTracking:(QYCupidSlot *)slot;
- (void) cacheStoreController:(QYCupid *)cupid;
- (nullable QYCupidWrapper *)processMixerResponse:(nonnull NSString *)url andRid:(nonnull NSString *)rid resp:(nonnull NSData *)response;
- (void) schemePull:(NSString *)scheme callback:(nullable void(^)(BOOL result))callback;
- (void) handleEmptyTrackingsShowClientAd:(BOOL)showClientAd;
- (void) win:(NSDictionary *)properties;
- (void) lose:(NSDictionary *)properties;



#pragma mark 回调
- (void) callbackReady;
- (void) callbackStart;
- (void) callbackFailed;
- (void) callbackError;
- (void) callbackEnd;
- (void) callbackClosed;
- (void) callbackClicked:(id __nullable)obj;
- (void) callbackShow;

- (void) callbackSubPageSuccess:(QY_PULLING_PAGETYPE)type; //应用内页面拉起成功
- (void) callbackSubPageFailed;
- (void) callbackSubPageClosed:(QY_PULLING_PAGETYPE)type;
- (void) callbackReward:(NSDictionary *)extraInfo;
- (void) callbackPreReward:(NSDictionary *)extraInfo;
- (void) callbackInteraction;
- (void)setObjectToMutExtraWithKey:(NSString *)key value:(id)value;

#pragma mark QYCupidBuilderDelegate

#pragma mark - 子类处理网络回调数据
- (void) onCupidSuccess:(NSString *)wrapperId;
- (void) onCupidFailed;
- (void) onCupidFailedWithErrorCode:(QyAdErrorCode)errorCode;

#pragma mark fore&back ground
- (void) doEnterForeground;
- (void) doEnterBackground;

- (void)dealWithClickPointWithCupid:(QYCupid *)cupid
                         parentView:(UIView *)parentView
                         recognizer:(UIGestureRecognizer *)recognizer;

#pragma mark - ADN
- (void) registAdnViewsWithContainer:(UIView *)container clickableViews:(NSArray *)clickableViews rootViewController:(UIViewController *)rootViewController;
- (void) unregisterAdnViews;

@end

NS_ASSUME_NONNULL_END
