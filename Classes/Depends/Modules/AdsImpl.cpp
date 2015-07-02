#include "AdsImpl.h"
#include "STAds.h"
#include "SuperGlobal.h"
void AdsImpl::onBannerLoadSuccessfully()
{
}

void AdsImpl::onBannerLoadFailed( int errorCode )
{
}

void AdsImpl::onBannerClicked()
{
    NotificationCenter::getInstance()->postNotification(kPuaseGame);
}

void AdsImpl::onBannerDismissed()
{
    NotificationCenter::getInstance()->postNotification(kResumeGame);
}

void AdsImpl::onInterstitialAdLoaded()
{
}

void AdsImpl::onInterstitialAdFailed( int errorCode )
{
}

void AdsImpl::onInterstitialShown()
{
    
    STAds::isInterstitialShowing=true;
    NotificationCenter::getInstance()->postNotification(kPuaseGame);
 
    
}

void AdsImpl::onInterstitialDismissed()
{
    STAds::isInterstitialShowing=false;
    NotificationCenter::getInstance()->postNotification(kResumeGame);

}

AdsImpl* AdsImpl::getInstance()
{
    if (!instance)
    {
        instance = new AdsImpl();
    }
    return instance;
}

AdsImpl::AdsImpl()
{
    
}

AdsImpl* AdsImpl::instance = NULL;

