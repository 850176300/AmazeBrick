//
//  GameLayerBase.h
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#ifndef __LibDoctor__GameLayerBase__
#define __LibDoctor__GameLayerBase__

#include <iostream>
#include "STVisibleRect.h"
#include "SuperGlobal.h"
#include "cocos2d.h"
#include "SoundPlayer.h"
//#include "SceneManager.h"
#include "AlertViewLayer.h"
#include "extensions/cocos-ext.h"
#include "KeypadDispatchCenter.h"
USING_NS_CC;
USING_NS_ST;
USING_NS_CC_EXT;
enum
{
    //背景z order
    kGameLayerZBg = 0,
    //游戏元素z order,分上下两层(目前分两层就够用了)
    kGameLayerZEleBottom,
    kGameLayerZEleUp,
    //按钮类z order
    kGameLayerZUI
};

/*
 游戏baseLayer, 其特点:
 1. 有可折叠的公共按钮(reset, home, music)；
 2. 有一居中放置的背景图片
 */
class GameLayerBase: public KeypadBaseLayer
{
public:
    GameLayerBase();
    ~GameLayerBase();
    
    virtual bool init();
    virtual bool initWithBgFileName(const char* apFileName, bool showAds = true);
    virtual void onEnter();
    virtual void onExit();

//    virtual void keyBackClicked();
    void setShowAds(bool isShow);
    void setADVisible(bool visible);
    Action* getJellyAction();
    void showHomeButton();
    void showNextButton();
    
    virtual void homeClickEvent();
    virtual void nextClickEvent();
    
    virtual void onPause();
    virtual void onResume();
    virtual void onEnterTransitionDidFinish();
    virtual void alertViewClickedButtonAtIndex(AlertViewLayer* alert,int index);
    virtual void onKeyBackClicked();
    bool isNeedShowAD(){return isShowAds;};
    void setNextHidden(bool hidden);
    void setHomeHidden(bool hidden);
    void setNextButtonZorder(int zorder);
protected:
    int pauseCount = 0;
    void showConfirmDialog();
    
    void removeunuseCache(float);
    void onHomeButtonClicked(cocos2d::Ref *pRef, Control::EventType type);
    void onNextButtonClicked(cocos2d::Ref *pRef, Control::EventType type);
    void onPauseGame(Ref *ref);
    void onResumeGame(Ref* ref);
public:
    ControlButton* homeBtn;
    ControlButton* nextBtn;
    Sprite* m_pBg;
    bool canbeClicked = true;
    bool isShowAds;

};
#endif /* defined(__LibDoctor__GameLayerBase__) */
