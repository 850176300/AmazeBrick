//
//  STAds.h
//
//  Created by Steven.Tian on 13-7-3.
//
//

#pragma once

#include "cocos2d.h"
#include "STAdsDelegate.h"

class STAds
{
public:
	STAds();
	virtual ~STAds();
    
    void setAdsDelegate(STAdsDelegate* delegate);
    
public:
	/**
	 * @brief request and show banner ads
	 */
	void requestAds();
    
    
	/**
	 * @brief remove shown ads or cancel suspending ads
	 */
	void removeAds();
    
	/**
	 * 加载普通全屏广告
	 */
	void preloadInterstitial();
	/**
	 * 加载交叉推广广告
	 */
	void preloadCrosspromo();
	/**
	 * 加载全屏和交叉推广广告
	 */
	void preloadAllInterstitial();
	/*
	 * 显示全屏广告，false表示没有广告可以显示，需要预加载
	 *
	 */
	bool showInterstitial();
	/**
	 * 显示交叉推广广告，false表示没有广告可以显示，需要预加载
	 */
	bool showCrosspromo();
    
public:
    /**
     * @brief destroy environment about ads
     */
    static void destroy();
    
    // when interstitial ads shown, set it true
    static bool isInterstitialShowing;
    
    // when user not purchased anything can remove ads, set it true;
    static bool willShowAd;
    
    // indicate current banner ad status
    static bool bannerAdVisibility;
};

