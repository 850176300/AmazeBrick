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
//    
//    //广告视图
//    MPAdView *adView_;
//    MPInterstitialAdController *adController_;
}

+(AdsIOSManager*)sharedManager;
+(void)purgeManager;

-(void)setSTAdsDelegate:(STAdsDelegate*)delegate;

-(void)requestAds;
-(void)removeAds;
-(void)requestInterstitialAds:(BOOL)isCrossProm;
-(void)setAdsVisibility:(BOOL)visibility;

@end
