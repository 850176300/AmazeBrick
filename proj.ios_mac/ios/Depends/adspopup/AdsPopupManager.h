//
//  AdsPopupManager.h
//
//  Created by tang.wei on 13-11-8.
//  Copyright (c) 2013年 yixing. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NewsBlast.h"

typedef NS_ENUM(NSInteger, BannerAdPosition) {
    BannerAdPositionTop,
    BannerAdPositionBottom
};

typedef NS_ENUM(NSUInteger, InterstitialAdType) {
    InterstitialAdTypeDefault = 0,     // 显示系统广告
    InterstitialAdTypeCrossPromo,  // 显示交叉推广广告
};

@protocol AdsPopupManagerDelegate;

@interface AdsPopupManager : NSObject

@property (nonatomic, assign) id<AdsPopupManagerDelegate> delegate;

// 默认值为屏幕下边
@property (nonatomic, assign) BannerAdPosition bannerAdPosition;

// 如果为nil, 默认为UIWindow的rootViewController,
// 如果rootViewController为UINavigationController,
// 那么默认为UINavigationController的visibleViewController
@property (nonatomic, assign) UIViewController *viewController;

// 设置全屏广告的类型, 默认值为InterstitialAdTypeDefault
@property (nonatomic, assign) InterstitialAdType interstitalAdType;

+ (AdsPopupManager *)sharedManager;

// 预先加载所有广告，请务必在appDidFinishLaunch调用
- (void)preloadAllAds;


#pragma mark - Banner相关

// 显示横幅
- (void)showBannerAd;

// 隐藏横幅
- (void)hideBannerAd;

// 移除横幅
- (void)removeBannerAd;

// 获取banner的高度
- (CGFloat)bannerHeight;

// 检查banner是否正在显示
- (BOOL)bannerIsShowing;

#pragma mark - 方块广告相关

// 预先加载300X250广告
// 注意：这个只在app需要支持改尺寸的广告才使用

// 广告默认大小为300x250, 广告中心点位置为屏幕的中心
- (void)showMediumRectAd;
// 设置广告视图的中心点位置, 大小默认为300x250
- (void)showMediumRectAdAtPoint:(CGPoint)center;
// 设置广告的frame
- (void)showMediumRectAdAtFrame:(CGRect)frame;

- (void)hideMediumRectAd;
- (void)removeMediumRectAd;

#pragma mark - 全屏相关

//重新加载广告
- (void)preloadshowInterstitialForType:(InterstitialAdType)adType;
// 显示全屏
- (BOOL)showInterstitial;

// 显示全屏
- (BOOL)showInterstitialForType:(InterstitialAdType)adType;

// 移除全屏
- (void)dismissInterstitial;

// 检查全屏广告是否正在显示
- (BOOL)interstitialIsShowing;

/**** 显示NewsBlast，和Chartboost全屏广告互斥显示 */
// launch显示
- (void)showNewsBlast;
// resume是显示
- (void)showNewsBlastOnResume;
// 根据模式来显示
- (void)showNewsBlast:(InvokeMode)mode;

@end

@protocol AdsPopupManagerDelegate <NSObject>

#pragma mark - Banner delegate
@optional
- (void)bannerAdDidLoad;
- (void)bannerAdDidFailToLoad;
// 点击了banner时候调用
- (void)willPresentModalViewForBanner;
// 点击了banner后，广告内容页dismiss时调用
- (void)didDismissModalViewForBanner;
// 跳到app store时调用
- (void)willLeaveApplicationFromBanner;

#pragma mark - Medium Rect Ads delegate
@optional
- (void)mediumRectAdDidLoad;
- (void)mediumRectAdDidFailToLoad;
// 点击了banner时候调用
- (void)willPresentModalViewForMediumRectAd;
// 点击了banner后，广告内容页dismiss时调用
- (void)didDismissModalViewForMediumRectAd;
// 跳到app store时调用
- (void)willLeaveApplicationFromMediumRectAd;

#pragma mark - Interstitial delegate
@optional
- (void)interstitialDidFailToLoad:(InterstitialAdType )adType;
- (void)interstitialDidLoad:(InterstitialAdType )adType;
- (void)interstitialDidShow:(InterstitialAdType )adType;
- (void)interstitialDidDismiss:(InterstitialAdType )adType;

#pragma mark - NewsBlast delegate
@optional
- (void)newsblastDidNotShow;
- (void)newsblastDidShow;
- (void)newsblastDidClickOK;
- (void)newsblastDidClickCancel;

@end
