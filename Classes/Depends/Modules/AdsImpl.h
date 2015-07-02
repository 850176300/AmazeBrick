#ifndef __ADS_IMPL_H__
#define __ADS_IMPL_H__
#include "cocos2d.h"
#include "STAdsDelegate.h"


USING_NS_CC;

class AdsImpl:public STAdsDelegate
{
public:
	AdsImpl();
	static AdsImpl* getInstance();

	virtual void onBannerLoadSuccessfully();

	virtual void onBannerLoadFailed( int errorCode );

	virtual void onBannerClicked();

	virtual void onBannerDismissed();

	virtual void onInterstitialAdLoaded();

	virtual void onInterstitialAdFailed( int errorCode );

	virtual void onInterstitialShown();

	virtual void onInterstitialDismissed();

	static AdsImpl* instance;
};
#endif