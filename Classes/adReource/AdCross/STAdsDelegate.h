//
//  STAdsDelegate.h
//
//  Created by Steven.Xc.Tian on 13-7-22.
//
//

#pragma once

class STAdsDelegate
{
public:
    /**
	 * @brief This event is called once an ad loads successfully.
	 */
    virtual void onBannerLoadSuccessfully() {};
    
	/**
	 * @brief This event is called if an ad fails to load.
	 */
	virtual void onBannerLoadFailed(int errorCode) {};
    
    /**
     * @brief Sent when the banner has just taken over the screen.
     */
    virtual void onBannerClicked() {};
    
    /**
     * @brief Sent when an expanded banner has collapsed back to its original size.
     */
	virtual void onBannerDismissed() {};
    
    /**
	 * @brief This event is called once an interstitial ad loads successfully.
	 */
    virtual void onInterstitialAdLoaded(int type) {};
    
    /**
	 * @brief This event is called if an interstitial ad fails to load.
	 */
    virtual void onInterstitialAdFailed(int errorCode,int type) {};
    
    /**
	 * @brief This event is called if an interstitial ad shown.
	 */
    virtual void onInterstitialShown(int type) {};
    
    /**
	 * @brief This event is called if an interstitial ad closed.
	 */
    virtual void onInterstitialDismissed(int  type) {};
};
