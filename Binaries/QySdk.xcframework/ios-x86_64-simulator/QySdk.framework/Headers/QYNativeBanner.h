//
//  QYNativeBanner.h
//  QySdk
//
//  Created by Peiran Zhang on 2021/6/11.
//  Copyright © 2021 iqiyi. All rights reserved.
//
#import <QySdk/IAdSdk.h>
#import "QYCupidNative.h"

NS_ASSUME_NONNULL_BEGIN

@protocol QYNativeDelegate <NSObject>

- (void) onExpressNativeLoadSuccess:(NSArray<QYCupidNative *>*)ads;
- (void) onExpressNativeLoadFailed;
- (void) onExpressNativeReward:(QYCupidNative *)ad extraInfo:(NSDictionary *)extra;
- (void) onExpressNativeSubPageOpen:(QY_PULLING_PAGETYPE)type;
- (void) onExpressNativeSubPageClosed:(QY_PULLING_PAGETYPE)type;

@end

@interface QYNativeBanner : QYExpressBase

@property (nonatomic, weak) id<QYNativeDelegate> nativeDelegate;

- (instancetype) initWithSlotId:(NSString *)slotId rootViewController:(UIViewController *)controller;

- (void) onCupidImpressed:(QYCupidNative *)cupid
                  impArea:(CGRect)area
                  extInfo:(NSDictionary *)extInfo;

- (void) onCupidClick:(QYCupidNative *)cupid
              impArea:(CGRect)ia //曝光区域，相对于屏幕左上角
             clickPos:(CGPoint)ca //点击坐标，相对于屏幕左上角
           buttonArea:(CGRect)ba //捕获点击视图坐标，相对于屏幕左上角
              extInfo:(NSDictionary *)extInfo;

@end

NS_ASSUME_NONNULL_END

