//
//  AdLoadingLayerBase.h
//
//  Created by tanshoumei on 15/6/10.
//
//

#pragma once

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "STAds.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class AdLoadingLayerBase: public Layer, public STAdsDelegate
{
public:
    //用于判断当前是否有AdLoadingLayer(其子类也算)的实例存在.不为空，则可重复使用。
    //注意这不是单例，使用要进行空判断。
    //使用场景: 比如正在AdLoading界面，用户点击了后面，再返回，此时回来界面上是有AdLoadingLayer的实例的，可重复使用，当然你也可以选择重新创建，Depends on U.
    static AdLoadingLayerBase* s_currentInstance;
    
    CREATE_FUNC(AdLoadingLayerBase);
    
    virtual bool init();
    
    void onExit();
    
    void onEnter() override;
        
    void loadAd(bool abIscross = false);
    
    void setSwallowTouch(bool value);
    
#pragma mark --ad delegate--

    virtual void onInterstitialAdFailed(int errorCode, int type);
    
    virtual void onInterstitialShown(int type);
    
    virtual void onInterstitialAdLoaded(int type);
    
    virtual void onInterstitialDismissed(int  type);
#pragma mark --ad delegate end--
    
protected:
    /*
     为什么不直接用schedule update(1. update比较常用，如果子类也用，容易产生混乱。2.此处对时效性要求不高，也不需要每帧检测)
     **/
    virtual void _timeCheckSchedule(float dt);
    
    //广告按时加载出来
    virtual void _adLoadInTime();
    
    //广告超时还未加载出来
    virtual void _adLoadTimeOut();

    //本界面任务完成
    virtual void _taskDone();
public:
    //
    std::function<void()> loadingDoneCallback = nullptr;
    
public:
    //Loading界面最多停留的时间(秒)
    CC_SYNTHESIZE(float, _loadingMaxTime, LoadingMaxTime);
    
    CC_SYNTHESIZE(float, _loadingMinTime, LoadingMinTime);
    
protected:
    EventListenerTouchOneByOne* _eventListenerTouch;
    
    timeval _timeEnter;
    
    STAds _ads;
    
    //0第三方 1交叉
    int _adLoadType = 0;
    
    //广告是否在显示
    bool _adShowing = false;
    
    bool _isRequestingLoadAd = false;
    
    bool _bLoadingCanRemove = false;    
    
    //广告加载完成与否(失败成功回调都算完成)
    bool _adLoadDone = false;
};