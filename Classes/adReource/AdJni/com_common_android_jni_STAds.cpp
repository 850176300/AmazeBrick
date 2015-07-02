/*
 * com_common_android_jni_STAds.cpp
 *
 *  Created on: 2013-7-3
 *      Author: Steven.Xc.Tian
 */
#include "com_common_android_jni_STAds.h"
#include "ST_Ad_Android.h"

JNIEXPORT void JNICALL Java_com_common_android_jni_STAds_nativeInit
(JNIEnv * pEnv, jobject thisObj)
{
	AndroidAdManager::getInstance()->init(pEnv, thisObj);
}

JNIEXPORT void JNICALL Java_com_common_android_jni_STAds_nativeDestroy
(JNIEnv * pEnv, jobject thisObj)
{
	AndroidAdManager::getInstance()->destroy();
}

JNIEXPORT void Java_com_common_android_jni_STAds_nativeAdLoadSuccessfully
(JNIEnv * pEnv, jobject thisObj)
{
	AndroidAdManager::getInstance()->onBannerLoadSuccessfully();
}

JNIEXPORT void JNICALL Java_com_common_android_jni_STAds_nativeAdLoadFailed
(JNIEnv * pEnv, jobject thisObj, jint errorCode)
{
	AndroidAdManager::getInstance()->onBannerLoadFailed(errorCode);
}
JNIEXPORT void JNICALL Java_com_common_android_jni_STAds_nativeClickedBannerAd
  (JNIEnv *, jobject){
	AndroidAdManager::getInstance()->onBannerClicked();

}
JNIEXPORT void JNICALL Java_com_common_android_jni_STAds_nativeInterstitialAdLoaded
(JNIEnv * pEnv, jobject thisObj, jint type)
{
	AndroidAdManager::getInstance()->onInterstitialAdLoaded(type);
}

JNIEXPORT void JNICALL Java_com_common_android_jni_STAds_nativeInterstitialAdFailed
(JNIEnv * pEnv, jobject thisObj, jint errorCode, jint type)
{
	AndroidAdManager::getInstance()->onInterstitialAdFailed(errorCode,type);
}

JNIEXPORT void JNICALL Java_com_common_android_jni_STAds_nativeInterstitialAdShown
(JNIEnv * pEnv, jobject thisObj, jint type)
{
	AndroidAdManager::getInstance()->onInterstitialShown(type);
}

JNIEXPORT void JNICALL Java_com_common_android_jni_STAds_nativeInterstitialAdDismissed
(JNIEnv * pEnv, jobject thisObj, jint type)
{
	AndroidAdManager::getInstance()->onInterstitialDismissed(type);
}

