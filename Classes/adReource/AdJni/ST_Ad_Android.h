/*
 * ST_Ad_Android.h
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */

#ifndef ST_AD_ANDROID_H_
#define ST_AD_ANDROID_H_

#include "ST_JNI_Helper.h"
#include "STAdsDelegate.h"

class AndroidAdManager: public STAdsDelegate
{
	STAdsDelegate* st_m_AdsDelegate;
public:
	AndroidAdManager() :
			st_m_AdsDelegate(0), stAdsJava(0), ClassAds(0), MethodRequestAds(0), MethodRemoveAds(0),MethodPreloadInterstitial(0),
			MethodPreloadCrosspromo(0),MethodPreloadAllInterstitiall(0),MethodShowInterstitial(0),MethodShowCrosspromo(0)
	{
	}
	~AndroidAdManager();

	static AndroidAdManager* getInstance();

	static void destroy();

	bool init(JNIEnv * pEnv, jobject pAdJava);

	void setAdDelegate(STAdsDelegate* pAdDelegate);

public:
	void requestAds();


	void removeAds();

	void preloadInterstitial();
	void preloadCrosspromo();
	void preloadAllInterstitial();
	bool showInterstitial();
	bool showCrosspromo();


public:
	/* the below methods derived from STAdsDelegate */

	void onBannerLoadSuccessfully();

	void onBannerLoadFailed(int errorCode);

	void onBannerClicked();

	void onBannerDismissed();

	void onInterstitialAdLoaded(int type);

	void onInterstitialAdFailed(int errorCode,int type);

	void onInterstitialShown(int type);

	void onInterstitialDismissed(int type);

private:
	/*>>>>>>>> below declaration is used by jni <<<<<<<<*/
	// Cached Classes.
	jclass ClassAds;
	// Cached java object
	jobject stAdsJava;
	// Cached active Methods.
	jmethodID MethodRequestAds;
	jmethodID MethodRemoveAds;
	jmethodID MethodPreloadInterstitial;
	jmethodID MethodPreloadCrosspromo;
	jmethodID MethodPreloadAllInterstitiall;
	jmethodID MethodShowInterstitial;
	jmethodID MethodShowCrosspromo;
    
    bool _couldShowCross;    
};

#endif /* ST_AD_ANDROID_H_ */
