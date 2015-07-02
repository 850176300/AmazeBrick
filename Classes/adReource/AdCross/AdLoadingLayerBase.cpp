//
//  AdLoadingLayerBase.cpp
//
//  Created by tanshoumei on 15/6/10.
//
//

#include "AdLoadingLayerBase.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d::ui;

AdLoadingLayerBase* AdLoadingLayerBase::s_currentInstance = nullptr;

bool AdLoadingLayerBase::init()
{
    Layer::init();
   
    _loadingMinTime = 0;
    _loadingMaxTime = 5;
    
    _eventListenerTouch = EventListenerTouchOneByOne::create();
    _eventListenerTouch->setSwallowTouches(true);
    _eventListenerTouch->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_eventListenerTouch, this);
    return true;
}

void AdLoadingLayerBase::onExit()
{
    Layer::onExit();
    
    _ads.setAdsDelegate(nullptr);
    
    s_currentInstance = nullptr;
    
}

void AdLoadingLayerBase::onEnter()
{
    Layer::onEnter();
    
    s_currentInstance = this;
    
    gettimeofday(&_timeEnter, nullptr);
    
    schedule(schedule_selector(AdLoadingLayerBase::_timeCheckSchedule));
    
    _ads.setAdsDelegate(this);
    
    loadAd();
}

void AdLoadingLayerBase::setSwallowTouch(bool value)
{
    _eventListenerTouch->setSwallowTouches(value);
}

void AdLoadingLayerBase::_timeCheckSchedule(float dt)
{
    struct timeval now;
    gettimeofday(&now, nullptr);
    float lTimePasses = now.tv_sec - _timeEnter.tv_sec;
    if ( ((lTimePasses >= _loadingMinTime) && _adLoadDone))
    {
        _adLoadInTime();
    }
    else if (lTimePasses >=_loadingMaxTime)
    {
        _adLoadTimeOut();
    }

}

void AdLoadingLayerBase::loadAd(bool abIscross)
{
    _adLoadType = abIscross;
    
    _isRequestingLoadAd = false;
    
    if(abIscross)
    {
        bool ret = _ads.showCrosspromo();
        if(!ret)
        {
            _isRequestingLoadAd = true;
        }
    }
    else
    {
        bool ret = _ads.showInterstitial();
        if(!ret)
        {
            _isRequestingLoadAd = true;
        }
    }
}

void AdLoadingLayerBase::onInterstitialAdFailed(int errorCode, int type)
{
    if(_adLoadType == type)
        _adLoadDone = true;
}

void AdLoadingLayerBase::onInterstitialShown(int type)
{
    if(_adLoadType == type)
    {
        _adLoadDone = true;
        _adShowing  = true;
    }
}

void AdLoadingLayerBase::onInterstitialAdLoaded(int type)
{
    if(_adLoadType == type && _isRequestingLoadAd)
        _ads.showInterstitial();
}

void AdLoadingLayerBase::onInterstitialDismissed(int type)
{
    if(_adLoadType == type)
    {
        if(_bLoadingCanRemove)
        {
            _taskDone();
            return;
        }
        _adShowing = false;
    }
}

void AdLoadingLayerBase::_adLoadInTime()
{
    //广告已关闭或加载失败
    if(!_adShowing)
    {
        _taskDone();
    }
    //广告正在显示
    else
    {
        _bLoadingCanRemove = true;
    }
}

void AdLoadingLayerBase::_adLoadTimeOut()
{
    //广告已关闭或加载失败
    if(!_adShowing)
    {
        _taskDone();
    }
    //广告正在显示
    else
    {
        _bLoadingCanRemove = true;
    }
}

void AdLoadingLayerBase::_taskDone()
{
    unschedule(schedule_selector(AdLoadingLayerBase::_timeCheckSchedule));
    removeFromParent();
    if(loadingDoneCallback)
    {
        loadingDoneCallback();
    };
}