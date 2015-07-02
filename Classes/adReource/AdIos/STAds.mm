//
//  STAds.cpp
//  MysteryGuardians
//
//  Created by Steven.Xc.Tian on 13-7-3.
//
//

#include "STAds.h"
#include "AdsIOSWrapper.h"
#include "cocos2d.h"
#include "AdsPopupManager.h"

bool STAds::willShowAd = true;
bool STAds::isInterstitialShowing = false;

void STAds::requestAds()
{
    [[AdsIOSManager sharedManager] requestAds];
}

void STAds::removeAds()
{
    [[AdsIOSManager sharedManager] removeAds];
}

void STAds::preloadAllInterstitial()
{
    [[AdsIOSManager sharedManager] preloadAllInterstitial];
}

void STAds::preloadCrosspromo()
{
    [[AdsIOSManager sharedManager] preloadCrosspromo];
}

void STAds::preloadInterstitial()
{
    [[AdsIOSManager sharedManager] preloadInterstitial];
}

bool STAds::showCrosspromo()
{
    return [[AdsIOSManager sharedManager] showCrosspromo];
}

bool STAds::showInterstitial()
{
    return [[AdsIOSManager sharedManager] showInterstitial];
}


void STAds::setAdsDelegate(STAdsDelegate* delegate)
{
    [[AdsIOSManager sharedManager] setSTAdsDelegate:delegate];
}


void STAds::destroy()
{
    [AdsIOSManager purgeManager];
}

//void STAds::getBannerSize(float  size[])
//{
//    size[0]=  0;
//    size[1]=  [[AdsPopupManager sharedManager] bannerHeight];
////    NSLog(@"ios--------->%f",[[AdsPopupManager sharedManager] bannerHeight]);
//}

STAds::STAds()
{
}

STAds::~STAds()
{
}
