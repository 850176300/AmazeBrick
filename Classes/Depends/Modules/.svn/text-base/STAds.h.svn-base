//
//  STAds.h
//  MysteryGuardians
//
//  Created by Steven.Xc.Tian on 13-7-3.
//
//

#ifndef __MysteryGuardians__STAds__
#define __MysteryGuardians__STAds__

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
	 * @brief request a interstitial ads
	 */
    void requestInterstitialAds(bool isCrossProm = false);
    
	/**
	 * @brief remove shown ads or cancel suspending ads
	 */
	void removeAds();
    
    /**
	 * @brief set visibility of ad view, not remove ad from parent node
	 */
	void setAdsVisibility(bool visibility);
	/**
	*    get banner ad size                                                                  
	*/
	void getBannerSize(float[]);
    
public:
    /**
     * @brief destroy environment about ads
     */
    static void destroy();
    
    // when interstitial ads shown, set it true
    static bool interstitialShown;
    
    // when user not purchased anything can remove ads, set it true;
    static bool willShowAd;

	// indicate current banner ad status
	static bool bannerAdVisibility;
};

#endif /* defined(__MysteryGuardians__STAds__) */
