//
//  FTNativeAdObject.h
//  OneAdSDK
//
//  Created by huankuai on 2024/12/5.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FTAdInfoObject : NSObject

@property (nonatomic, copy) NSString *requestId;
@property (nonatomic, copy) NSString *creativeId;
@property (nonatomic, copy) NSString *price;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *subTitle;

@property (nonatomic, copy) NSString *videoUrl;//视频素材地址
@property (nonatomic, copy) NSString *videoCoverImageUrl;//视频封面图地址
@property (nonatomic, assign) NSInteger videoDuration;//视频时⻓，秒
@property (nonatomic, assign) NSInteger videoSize;//视频⼤⼩
@property (nonatomic, assign) NSInteger videoWidth;
@property (nonatomic, assign) NSInteger videoHeight;

@property (nonatomic, copy) NSString *imageUrl;//图片素材地址
@property (nonatomic, assign) NSInteger imageWidth;
@property (nonatomic, assign) NSInteger imageHeight;

@property (nonatomic, copy)  NSString *iconUrl;//广告icon

@property (nonatomic, copy)  NSString *dspName;//渠道名字
@property (nonatomic, copy)  NSString *dspLogoUrl;//渠道logo

@property (nonatomic, copy)  NSString *app_download_url;//应⽤下载链接，iOS为appstore地址，Android为apk包下载地址。
@property (nonatomic, copy)  NSString *app_name;//app名称//战斗法则
@property (nonatomic, copy)  NSString *app_version;//版本
@property (nonatomic, copy)  NSString *app_developer_name;//应⽤开发者名称
@property (nonatomic, copy)  NSString *app_permission_info;//权限信息
@property (nonatomic, copy)  NSString *app_update_time;//更新时间
@property (nonatomic, copy)  NSString *app_privacy_url;//隐私政策url
@property (nonatomic, copy)  NSString *app_icon_url;//图标url
@property (nonatomic, copy)  NSString *app_introduction;//app信息介绍

@property (nonatomic, assign) BOOL isShake;
@end

NS_ASSUME_NONNULL_END
