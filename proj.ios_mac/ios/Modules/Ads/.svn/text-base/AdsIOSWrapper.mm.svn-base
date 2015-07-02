//
//  AdsIOSWrapper.m
//  MysteryGuardians
//
//  Created by Steven.Tian on 13-7-22.
//
//

#import "AdsIOSWrapper.h"
#import "AppController.h"
//#import "AppController+Shared.h"
#import "DeviceHelper.h"
#import "RootViewController.h"
#include "SimpleAudioEngine.h"
#import "AnalysisManager.h"
#if !KIDS
#import "AdsPopupManager.h"
#endif



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

//banner ad 点击处理





//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_Resume);
//    cocos2d::Director::getInstance()->resume();
//    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
    // resume game


//    cocos2d::Director::getInstance()->pause();
//    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_Clickbanner);
//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_Pause);


//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_Resume);
//    cocos2d::Director::getInstance()->resume();
//    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();


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


    // pause game
//    cocos2d::Director::getInstance()->pause();
//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_Pause);


//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_Resume);
    // pause game
//    cocos2d::Director::getInstance()->resume();
//    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_CLoseFullAds);





    // pause game
//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_Pause);
//    cocos2d::Director::getInstance()->pause();
//     CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();


    // pause game
//    cocos2d::NotificationCenter::getInstance()->postNotification(Notify_Resume);
//    cocos2d::Director::getInstance()->resume();
//    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();


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
- (void)interstitialDidFailToLoad{
    if(stAdsDelegate_)
        stAdsDelegate_->onInterstitialAdFailed(-1);
}
- (void)interstitialDidShow{
    if(stAdsDelegate_)
        stAdsDelegate_->onInterstitialShown();
}
- (void)interstitialDidDismiss{
    if(stAdsDelegate_)
        stAdsDelegate_->onInterstitialDismissed();
}

@end
