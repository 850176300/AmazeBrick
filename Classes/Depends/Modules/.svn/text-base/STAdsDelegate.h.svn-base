//
//  STAdsDelegate.h
//  MysteryGuardians
//
//  Created by Steven.Xc.Tian on 13-7-22.
//
//

#ifndef MysteryGuardians_STAdsDelegate_h
#define MysteryGuardians_STAdsDelegate_h

class STAdsDelegate
{
public:
    /**
	 * @brief This event is called once an ad loads successfully.
	 */
	virtual void onBannerLoadSuccessfully() = 0;
    
	/**
	 * @brief This event is called if an ad fails to load.
	 */
	virtual void onBannerLoadFailed(int errorCode) = 0;
    
    /**
     * @brief Sent when the banner has just taken over the screen.
     */
    virtual void onBannerClicked() = 0;
    
    /**
     * @brief Sent when an expanded banner has collapsed back to its original size.
     */
	virtual void onBannerDismissed() = 0;
    
    /**
	 * @brief This event is called once an interstitial ad loads successfully.
	 */
    virtual void onInterstitialAdLoaded() = 0;
    
    /**
	 * @brief This event is called if an interstitial ad fails to load.
	 */
    virtual void onInterstitialAdFailed(int errorCode) = 0;
    
    /**
	 * @brief This event is called if an interstitial ad shown.
	 */
    virtual void onInterstitialShown() = 0;
    
    /**
	 * @brief This event is called if an interstitial ad closed.
	 */
    virtual void onInterstitialDismissed() = 0;
};


#endif
