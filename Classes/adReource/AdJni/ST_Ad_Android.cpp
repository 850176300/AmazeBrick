/*
 * ST_Ad_Android.cpp
 *
 *  Created on: 2013-9-2
 *      Author: Steven.Xc.Tian
 */

#include "ST_Ad_Android.h"
#include "STAds.h"

static AndroidAdManager* sp_AndroidAdManager = 0;

AndroidAdManager* AndroidAdManager::getInstance()
{
	if (!sp_AndroidAdManager)
	{
		sp_AndroidAdManager = new AndroidAdManager();
	}

	return sp_AndroidAdManager;
}

void AndroidAdManager::destroy()
{
	if (sp_AndroidAdManager)
	{
		delete sp_AndroidAdManager;

		sp_AndroidAdManager = 0;
	}
}

bool AndroidAdManager::init(JNIEnv * pEnv, jobject pAdJava)
{
	// get class
	ClassAds = pEnv->GetObjectClass(pAdJava);
	if (!ClassAds)
	{
		LOGE("get STAds class Failed!");
		return false;
	}
	ClassAds = (jclass) ST_JNI_Helper::makeGlobalRef(pEnv, ClassAds);

	// get method id --- purchaseManaged(String)
	MethodRequestAds = pEnv->GetMethodID(ClassAds, "requestAds", "()V");
	if (!MethodRequestAds)
	{
		LOGE("get Method requestAds id Failed!");
		return false;
	}


	// get method id --- purchaseUnmanaged(String)
	MethodRemoveAds = pEnv->GetMethodID(ClassAds, "removeAds", "()V");
	if (!MethodRemoveAds)
	{
		LOGE("get Method removeAds id Failed!");
		return false;
	}


	MethodPreloadCrosspromo = pEnv->GetMethodID(ClassAds, "preloadCrosspromo", "()V");
	if (!MethodPreloadCrosspromo)
	{
		LOGE("get Method preloadCrosspromo id Failed!");
		return false;
	}

	MethodPreloadInterstitial = pEnv->GetMethodID(ClassAds, "preloadInterstitial", "()V");
	if (!MethodPreloadInterstitial)
	{
		LOGE("get Method preloadInterstitial id Failed!");
		return false;
	}

	MethodPreloadAllInterstitiall = pEnv->GetMethodID(ClassAds, "preloadAllInterstitial", "()V");
	if (!MethodPreloadAllInterstitiall)
		{
			LOGE("get Method preloadAllInterstitial id Failed!");
			return false;
		}

	//
	MethodShowInterstitial = pEnv->GetMethodID(ClassAds, "showInterstitial", "()Z");
	if (!MethodShowInterstitial)
	{
		LOGE("get Method showInterstitial id Failed!");
		return false;
	}

	MethodShowCrosspromo = pEnv->GetMethodID(ClassAds, "showCrosspromo", "()Z");
	if (!MethodShowCrosspromo)
	{
		LOGE("get Method showCrosspromo id Failed!");
		return false;
	}

	// Caches objects.
	stAdsJava = ST_JNI_Helper::makeGlobalRef(pEnv, pAdJava);
	if (!stAdsJava)
	{
		LOGE("Cache stIABJava Failed!");
		return false;
	}

    _couldShowCross = false;
	return true;
}

void AndroidAdManager::setAdDelegate(STAdsDelegate* pAdDelegate)
{
	st_m_AdsDelegate = pAdDelegate;
}

void AndroidAdManager::requestAds()
{
	if (!stAdsJava)
	{
		LOGE("STAds::requestAds() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stAdsJava, MethodRequestAds);
}



void AndroidAdManager::removeAds()
{
	if (!stAdsJava)
	{
		LOGE("STAds::removeAds() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	lEnv->CallVoidMethod(stAdsJava, MethodRemoveAds);
}

void AndroidAdManager::preloadInterstitial(){
	if (!stAdsJava)
	{
		LOGE("STAds::preloadInterstitial() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	lEnv->CallVoidMethod(stAdsJava, MethodPreloadInterstitial);

}
void AndroidAdManager::preloadCrosspromo(){
	if (!stAdsJava)
	{
		LOGE("STAds::preloadCrosspromo() failed!");
		return;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	lEnv->CallVoidMethod(stAdsJava, MethodPreloadCrosspromo);
}

void AndroidAdManager::preloadAllInterstitial(){
	if (!stAdsJava)
	{
		LOGE("STAds::preloadAllInterstitial() failed!");
		return ;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();
	lEnv->CallVoidMethod(stAdsJava, MethodPreloadAllInterstitiall);
}
bool AndroidAdManager::showInterstitial(){
	if (!stAdsJava)
	{
		LOGE("STAds::showInterstitial() failed!");
		return false;
	}

	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	jboolean ret = lEnv->CallBooleanMethod(stAdsJava, MethodShowInterstitial);
		return (ret == JNI_TRUE ? true : false);
}
bool AndroidAdManager::showCrosspromo(){
	if (!stAdsJava)
	{
		LOGE("STAds::showInterstitial() failed!");
		return false;
	}

    _couldShowCross = true;
    
	JNIEnv* lEnv = ST_JNI_Helper::getJNIEnv();

	jboolean ret = lEnv->CallBooleanMethod(stAdsJava, MethodShowCrosspromo);
	return (ret == JNI_TRUE ? true : false);
}



/*============================================*/
void AndroidAdManager::onBannerLoadSuccessfully()
{
	if (st_m_AdsDelegate)
	{
		st_m_AdsDelegate->onBannerLoadSuccessfully();
	}
}

void AndroidAdManager::onBannerLoadFailed(int errorCode)
{
	if (st_m_AdsDelegate)
	{
		st_m_AdsDelegate->onBannerLoadFailed(errorCode);
	}
}

void AndroidAdManager::onBannerClicked()
{
	if (st_m_AdsDelegate)
	{
		st_m_AdsDelegate->onBannerClicked();
	}
}

void AndroidAdManager::onBannerDismissed()
{
	if (st_m_AdsDelegate)
	{
		st_m_AdsDelegate->onBannerDismissed();
	}
}

void AndroidAdManager::onInterstitialAdLoaded(int type)
{
	if (st_m_AdsDelegate)
	{
		st_m_AdsDelegate->onInterstitialAdLoaded(type);
	}
}

void AndroidAdManager::onInterstitialAdFailed(int errorCode,int type)
{
	if (st_m_AdsDelegate)
	{
		st_m_AdsDelegate->onInterstitialAdFailed(errorCode,type);
	}
}

void AndroidAdManager::onInterstitialShown(int type)
{
    STAds::isInterstitialShowing = true;

	if (st_m_AdsDelegate)
	{
		st_m_AdsDelegate->onInterstitialShown(type);
	}
}

void AndroidAdManager::onInterstitialDismissed(int type)
{
    STAds::isInterstitialShowing = false;

	if (st_m_AdsDelegate)
	{
		st_m_AdsDelegate->onInterstitialDismissed(type);
	}
}

AndroidAdManager::~AndroidAdManager()
{
	ST_JNI_Helper::deleteGlobalRef(ClassAds);
	ST_JNI_Helper::deleteGlobalRef(stAdsJava);
}

