//
//  QYNativeAd.h
//  QySdk
//
//  Created by Peiran Zhang on 2022/1/28.
//  Copyright © 2022 iqiyi. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "QYNativeAdDelegate.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 模板类型
   NORMAL = 0; //图片(2:1, 16:9, 6:5) 开机屏
   VIDEO = 1; //视频(16:9, 6:5) 开机屏
   VERTICAL_IMG = 2;//竖版图片(9:16)
   VERTICAL_VIDEO = 3;//竖版视频(9:16)
   SMALL_IMG = 4;//小图片 （视频关联位模板，小图文模板）（1：1， 5：3）
   LARGE_IMG = 5；//大图片（banner_pic 16:3）
 */

typedef NS_ENUM(NSInteger, QYNativeTemplateType) {
    QYNativeTemplateType_Normal = 0,
    QYNativeTemplateType_Video = 1,
    QYNativeTemplateType_VerticalImg = 2,
    QYNativeTemplateType_VerticalVideo = 3,
    QYNativeTemplateType_SmallImg = 4,
    QYNativeTemplateType_LargeImg = 5
};

typedef NS_ENUM(NSInteger, QYNativeMuteStatus) {
    QYNativeMuteStatus_Sound = 0,               // 有声播放
    QYNativeMuteStatus_Mute = 1,                // 静音播放，调整音量物理键时，如果监测到声音>0，会变为有声播放
    QYNativeTemplateType_AlwaysMute = 2         // 始终静音播放，不受物理键控制，始终静音
};

@protocol QYNativeAd <NSObject>

@required

/**
 * 获取价格，单位 分/千次曝光
 */
- (NSInteger) getPrice;

/**
 * 获取广告文案
 */
- (NSString *) getTitle;

/**
 * 获取广告时长，图片素材返回0
 */
- (NSInteger) getAdDuration;

/**
 * 获取广告图片的素材地址
 */
- (NSString *) getAppIcon;

/**
 * 主素材的宽，像素值
 */
- (NSInteger) getWidth;

/**
 * 主素材的高，像素值
 */
- (NSInteger) getHeight;

/**
 * 获取广告产品名称
 */
- (NSString *) getAppName;

/**
 * 获取广告来源名称
 */
- (NSString *) getDspName;

/**
 * 获取按钮文案
 */
- (NSString *) getButtonText;

/**
 * 获取点击交互类型
 */
- (NSInteger) getClickThroughType;
 
/**
 * 模板类型
 */
- (QYNativeTemplateType) getTemplateType;

/**
 * 获取图片素材地址
 */
- (NSArray<NSString *> *) getImgUrlList;

/**
 * 获取渲染好的视频View
 */
- (NSArray<UIView *> *) getViewList;


/**
 * 注册视图容器和可点击的view
 */
- (void) registerContainer:(UIView *)container withClickableViews:(NSArray<UIView *> *)clickableViews;

/**
 * 取消view上注册的点击
 */
- (void) unRegisterClickableViews;

/**
 * 设置广告加载回调
 */
- (void) setDelegate:(id<QYNativeAdDelegate>)delegate;

/**
 * 开始加载广告数据
 */
- (void) loadData;

/**
 * 判断当前广告是不是在播放，对于图片类广告，将始终返回YES
 */
- (BOOL) isPlaying;

/**
 * 判断当前广告是不是静音状态，对于图片类广告，将始终返回YES
 */
- (BOOL) isMute;

/**
 * 获取额外信息
 */
- (NSDictionary *) getExtra;

/**
 * 获取广告的互动类型
 * @return 4：AD_ACTION_TYPE_SHARK
 */
- (NSInteger) getActionType;

/**
 * 开始监听互动
 */
- (void) setActionStart;

/**
 * 停止互动
 */
- (void) setActionStop;


//视频播控，对于图片类广告无效
- (void) play;
- (void) pause;
- (void) resume;
- (void) replay;
- (void) setMuteStatus:(QYNativeMuteStatus)status;

@end

NS_ASSUME_NONNULL_END
