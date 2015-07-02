//
//  AdsIOSWrapper.h
//  MysteryGuardians
//
//  Created by Steven.Tian on 13-7-22.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AdsPopupManager.h"
#include "STAds.h"
#include "cocos2d.h"

@interface AdsIOSManager : NSObject<AdsPopupManagerDelegate>
{
    STAdsDelegate* stAdsDelegate_;
    
    bool _couldShowCross;
}

+(AdsIOSManager*)sharedManager;
+(void)purgeManager;

-(void)setSTAdsDelegate:(STAdsDelegate*)delegate;

-(void)requestAds;
-(void)removeAds;
-(void)requestInterstitialAds:(BOOL)isCrossProm;
-(void)setAdsVisibility:(BOOL)visibility;


/**
 * 加载普通全屏广告
 */
-(void) preloadInterstitial;
/**
 * 加载交叉推广广告
 */
-(void) preloadCrosspromo;
/**
 * 加载全屏和交叉推广广告
 */
-(void) preloadAllInterstitial;
/*
 * 显示全屏广告，false表示没有广告可以显示，需要预加载
 *
 */
-(bool) showInterstitial;
/**
 * 显示交叉推广广告，false表示没有广告可以显示，需要预加载
 */
-(bool) showCrosspromo;

@end
