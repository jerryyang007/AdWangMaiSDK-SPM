//
//  QYNativeAdDelegate.h
//  QySdk
//
//  Created by Peiran Zhang on 2022/2/9.
//  Copyright © 2022 iqiyi. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "QYExpressBase.h"

NS_ASSUME_NONNULL_BEGIN

@protocol QYNativeAd;

@protocol QYNativeAdDelegate <NSObject>

-(void) onNativeAdDidLoad:(id<QYNativeAd>) nativeAd;
-(void) onNativeAd:(id<QYNativeAd>) nativeAd failWithError:(QyAdErrorCode)errorCode;
-(void) onNativeAdBecomeVisiable:(id<QYNativeAd>) nativeAd;
-(void) onNativeAdClick:(id<QYNativeAd>) nativeAd;
-(void) onNativeAdVideoStart:(id<QYNativeAd>) nativeAd;
-(void) onNativeAdVideoEnd:(id<QYNativeAd>) nativeAd;

@end

NS_ASSUME_NONNULL_END
