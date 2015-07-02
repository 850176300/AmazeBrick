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

bool STAds::willShowAd = true;
bool STAds::interstitialShown = false;

void STAds::requestAds()
{
    [[AdsIOSManager sharedManager] requestAds];
}

void STAds::removeAds()
{
    [[AdsIOSManager sharedManager] removeAds];
}

void STAds::requestInterstitialAds(bool isCrossProm)
{
    [[AdsIOSManager sharedManager] requestInterstitialAds:isCrossProm];
}

void STAds::setAdsDelegate(STAdsDelegate* delegate)
{
    [[AdsIOSManager sharedManager] setSTAdsDelegate:delegate];
}

void STAds::setAdsVisibility(bool visibility)
{
    visibility ?
    [[AdsIOSManager sharedManager] setAdsVisibility:YES] :
    [[AdsIOSManager sharedManager] setAdsVisibility:NO];
}

void STAds::destroy()
{
    [AdsIOSManager purgeManager];
}
void STAds::getBannerSize(float  size[])
{
    size[0]=  0;
    size[1]=  [[AdsPopupManager sharedManager] bannerHeight];
//    NSLog(@"ios--------->%f",[[AdsPopupManager sharedManager] bannerHeight]);
}

STAds::STAds()
{
}

STAds::~STAds()
{
}
