/*
 * STAds.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */
#include "STAds.h"
#include "ST_Ad_Android.h"

bool STAds::willShowAd = true;
bool STAds::isInterstitialShowing = false;
bool STAds::bannerAdVisibility = false;

void STAds::requestAds()
{
	AndroidAdManager::getInstance()->requestAds();
}

void STAds::removeAds()
{
	AndroidAdManager::getInstance()->removeAds();
}

void STAds::setAdsDelegate(STAdsDelegate* delegate)
{
	AndroidAdManager::getInstance()->setAdDelegate(delegate);
}

void STAds::preloadInterstitial()
{
	AndroidAdManager::getInstance()->preloadInterstitial();
}

void STAds::preloadCrosspromo()
{
	AndroidAdManager::getInstance()->preloadCrosspromo();
}
void STAds::preloadAllInterstitial(){
	AndroidAdManager::getInstance()->preloadAllInterstitial();
}

bool STAds::showInterstitial()
{
	return AndroidAdManager::getInstance()->showInterstitial();
}

bool STAds::showCrosspromo()
{
	return AndroidAdManager::getInstance()->showCrosspromo();
}



void STAds::destroy()
{
	AndroidAdManager::getInstance()->destroy();
}

STAds::STAds()
{
}

STAds::~STAds()
{
}
