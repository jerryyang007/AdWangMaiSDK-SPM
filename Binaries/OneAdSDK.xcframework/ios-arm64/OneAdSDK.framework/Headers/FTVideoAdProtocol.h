//
//  FTVideoAdProtocol.h
//  OneAdSDK
//
//  Created by huankuai on 2025/3/18.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol FTVideoAdProtocol <NSObject>

@required

/// 视频将要开始时上报此事件
- (void)willStartVideo;

/// 视频开始播放时上报此事件
- (void)didStartVideoWithVideo;

/// 视频播放完成时上报此事件，duration为视频播放完成时视频已播放的时长，单位毫秒
- (void)didFinishVideoWithCurrentDuration:(NSTimeInterval)duration;

/// 视频播放异常时上报此事件，duration为出现异常时视频已播放的时长，单位毫秒
- (void)didFailVideoWithCurrentDuration:(NSTimeInterval)duration error:(nullable NSError *)error;

/// 视频暂停时上报此事件，duration为视频暂停时视频已播放的时长，单位毫秒
- (void)didPauseVideoWithCurrentDuration:(NSTimeInterval)duration;

/// 视频续播时上报此事件，duration为视频复播时视频已播放的时长，单位毫秒
- (void)didResumeVideoWithCurrentDuration:(NSTimeInterval)duration;
@end

NS_ASSUME_NONNULL_END
