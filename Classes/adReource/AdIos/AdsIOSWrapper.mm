//
//  AdsIOSWrapper.m
//  MysteryGuardians
//
//  Created by Steven.Tian on 13-7-22.
//
//

#import "AdsIOSWrapper.h"
#import "AppController.h"
#import "RootViewController.h"
#include "SimpleAudioEngine.h"
#import "AnalysisManager.h"
#import "AdsPopupManager.h"



static AdsIOSManager *s_instance = nil;

@implementation AdsIOSManager

+(AdsIOSManager*)sharedManager
{
    if(s_instance==nil)
    {
        s_instance=[[AdsIOSManager alloc] init];
        

    }
    return s_instance;
}

+(void)purgeManager
{
    if (s_instance)
    {
        [s_instance release],s_instance = nil;
    }
}

-(void)dealloc
{
    stAdsDelegate_=0;
    s_instance=0;
    [super dealloc];
}

-(id)init{
    self = [super init];
    if (self) {
        RootViewController *vc=[AppController sharedAppController].viewController;
        
        [[AdsPopupManager sharedManager] setViewController:vc];
        [[AdsPopupManager sharedManager] preloadAllAds];
        [[AdsPopupManager sharedManager] setDelegate:self];
        [[AdsPopupManager sharedManager] setBannerAdPosition:BannerAdPositionBottom];
        [[AnalysisManager sharedManager] startSession];
        
        _couldShowCross = false;
    }
    
    return self;
}

-(void)setSTAdsDelegate:(STAdsDelegate*)delegate
{
    stAdsDelegate_ = delegate;
}

-(void)requestAds
{
    [[AdsPopupManager sharedManager] showBannerAd];
}

-(void)removeAds
{
    [[AdsPopupManager sharedManager] hideBannerAd];
}

-(void)setAdsVisibility:(BOOL)visibility
{
    visibility ?
    [[AdsPopupManager sharedManager] showBannerAd] :
    [[AdsPopupManager sharedManager] hideBannerAd];
}


//全屏广告
-(void)requestInterstitialAds:(BOOL)isCrossProm
{

    if (STAds::willShowAd)
    {
        [[AdsPopupManager sharedManager] setDelegate:self];
        if (isCrossProm) {
            [[AdsPopupManager sharedManager] showInterstitialForType:InterstitialAdTypeCrossPromo];
        }else{
            [[AdsPopupManager sharedManager] showInterstitial];
        }
    }

}

-(void) preloadInterstitial
{
    [[AdsPopupManager sharedManager] preloadshowInterstitialForType:InterstitialAdTypeDefault];
}

-(void) preloadCrosspromo
{
    [[AdsPopupManager sharedManager] preloadshowInterstitialForType:InterstitialAdTypeCrossPromo];
}

-(void) preloadAllInterstitial
{
    [self preloadInterstitial];
    [self preloadCrosspromo];
}

-(bool) showInterstitial
{
    return [[AdsPopupManager sharedManager] showInterstitialForType:InterstitialAdTypeDefault];
}

-(bool) showCrosspromo
{
    _couldShowCross = true;
    
    bool ret = [[AdsPopupManager sharedManager] showInterstitialForType:InterstitialAdTypeCrossPromo];
    return ret;
}

#pragma banner delegate 
- (void)bannerAdDidLoad{
    if(stAdsDelegate_)
        stAdsDelegate_->onBannerLoadSuccessfully();
}
- (void)bannerAdDidFailToLoad{
    if(stAdsDelegate_)
        stAdsDelegate_->onBannerLoadFailed(-1);
}
// 点击了banner时候调用
- (void)willPresentModalViewForBanner{
    if(stAdsDelegate_)
        stAdsDelegate_->onBannerClicked();
}
// 点击了banner后，广告内容页dismiss时调用
- (void)didDismissModalViewForBanner{
    if(stAdsDelegate_)
        stAdsDelegate_->onBannerDismissed();
}
// 跳到app store时调用
- (void)willLeaveApplicationFromBanner{
    
}

#pragma interstial delegate
- (void)interstitialDidFailToLoad: (InterstitialAdType )adType
{
    if(stAdsDelegate_)
        stAdsDelegate_->onInterstitialAdFailed(-1, adType);
}
- (void)interstitialDidShow: (InterstitialAdType )adType
{
    STAds::isInterstitialShowing = true;

    if(stAdsDelegate_)
        stAdsDelegate_->onInterstitialShown(adType);
}
- (void)interstitialDidDismiss:(InterstitialAdType )adType
{
    STAds::isInterstitialShowing = false;

    if(stAdsDelegate_)
        stAdsDelegate_->onInterstitialDismissed(adType);
}
- (void)interstitialDidLoad:(InterstitialAdType )adType
{
    if(stAdsDelegate_)
        stAdsDelegate_->onInterstitialAdLoaded(adType);
}

@end
