//
//  QYExpressBanner.h
//  Cupid
//
//  Created by Peiran Zhang on 2020/5/7.
//  Copyright © 2020 iqiyi. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "QYExpressBase.h"
#import "QYBannerView.h"

NS_ASSUME_NONNULL_BEGIN

// 自动播放类型
typedef NS_ENUM(NSUInteger, QY_VIDEOAD_AUTOPLAY_TYPE) {
    QY_VIDEOAD_AUTOPLAY_TYPE_ALWAYS     = 0,        //随时自动播放(WIFI/移动网络)
    QY_VIDEOAD_AUTOPLAY_TYPE_WIFI       = 1,        //WIFI下自动播放
    QY_VIDEOAD_AUTOPLAY_TYPE_NEVER      = 2         //不自动播放
};

@protocol QYExpressBannerDelegate <NSObject>
- (void) onExpressBannerReady:(QYBannerView *)banner;
- (void) onExpressBannerShow:(QYBannerView *)banner;
- (void) onExpressBannerFailed:(QYBannerView * __nullable)banner;
- (void) onExpressBannerClicked:(QYBannerView *)banner;
- (void) onExpressBannerNagtived:(QYBannerView *)banner extraInfo:(NSDictionary *)extra;
//banner子页面关闭回调：仅支持QY_PULLING_TYPE_WEBVIEW和QY_PULLING_TYPE_STORE两种类型
- (void) onExpressBannerSubPageClosed:(QYBannerView *)banner
                                 type:(QY_PULLING_PAGETYPE)type ;
- (void) onExpressBannerSubPageSuccess:(QYBannerView *)banner type: (QY_PULLING_PAGETYPE)type;

@end

@interface QYExpressBanner : QYExpressBase
@property(nonatomic, assign) QYBannerStyle style; 
@property(nonatomic, weak) id<QYExpressBannerDelegate> bannerDelegate;
- (instancetype) initWithSlotId:(NSString *)slotId rootViewController:(UIViewController *)controller;
- (void) setFrame:(CGRect)frame;
//设置静音播放，默认静音播放
- (void) setMute:(BOOL)mute;
//设置自动播放类型，默认QY_VIDEOAD_AUTOPLAY_TYPE_ALWAYS
- (void) setAutoPlayType:(QY_VIDEOAD_AUTOPLAY_TYPE)autoPlayType;
@end

NS_ASSUME_NONNULL_END
