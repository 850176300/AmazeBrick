//
//  GameLayerBase.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#include "GameLayerBase.h"
#include "CocosHelper.h"
//#include "PurchaseManager.h"
#include "STAds.h"
//#include "GameController.h"

GameLayerBase::GameLayerBase()
{
    homeBtn = nullptr;
    nextBtn = nullptr;
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayerBase::onPauseGame), kPuaseGame, nullptr);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayerBase::onResumeGame), kResumeGame, nullptr);
    
}

GameLayerBase::~GameLayerBase(){
    log("the class %s consturctor========", __FUNCTION__);
    NotificationCenter::getInstance()->removeObserver(this, kPuaseGame);
    NotificationCenter::getInstance()->removeObserver(this, kResumeGame);
}

void GameLayerBase::onPauseGame(cocos2d::Ref *ref) {
    pauseCount++;
    if (pauseCount == 1) {
        onPause();
    }
}

void GameLayerBase::onResumeGame(cocos2d::Ref *ref) {
    pauseCount -= 1;
    if (pauseCount == 0) {
        onResume();
    }
}

bool GameLayerBase::init(){
    if (CCLayer::init()) {
        
        return true;
    }
    return false;
}

bool GameLayerBase::initWithBgFileName(const char *apFileName, bool showAds /*= true*/)
{
    if(CCLayer::init())
    {
        //场景背景
        m_pBg = Sprite::create(apFileName);
        m_pBg->setPosition(STVisibleRect::getCenterOfScene());
        m_pBg->setScale(STVisibleRect::getRealDesignScale());
        this->addChild(m_pBg, 0);
        
        
        isShowAds = showAds;
        if (showAds) {
            log("show the banner %s", __FUNCTION__);
            showHomeButton();
        }else {
            log("donnot need show banner %s", __FUNCTION__);
        }
        
        //        this->setKeypadEnabled(true);
        return true;
    }
    return false;
}

void GameLayerBase::setShowAds(bool isShow) {
    isShowAds = isShow;
}
void GameLayerBase::onEnter(){
    KeypadBaseLayer::onEnter();
    if (isShowAds) {
//        if (PurchaseManager::getInstance()->getRemoveAd() == false) {
//            STAds ads;
//            ads.requestAds();
//            ads.setAdsVisibility(true);
//        }
    }else {
//        if (PurchaseManager::getInstance()->getRemoveAd() == false) {
//            STAds ads;
//            ads.setAdsVisibility(false);
//        }
    }
}


void GameLayerBase::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
    scheduleOnce(schedule_selector(GameLayerBase::removeunuseCache), 0);
}

void GameLayerBase::removeunuseCache(float) {
     Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void GameLayerBase::showHomeButton(){
    if (homeBtn != nullptr) {
        return;
    }
    homeBtn = CocosHelper::getButton("ui/publish/home.png", "ui/publish/home.png");
//    homeBtn->setAnchorPoint(Vec2(1.0, 1.0));
    homeBtn->setPosition(STVisibleRect::getPointOfSceneRightUp() + Vec2(-15-homeBtn->getContentSize().width/2.0, -15-homeBtn->getContentSize().height/2.0));
    homeBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayerBase::onHomeButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    homeBtn->setZoomOnTouchDown(false);
    addChild(homeBtn, kHomeBtn);
    
}

void GameLayerBase::onHomeButtonClicked(cocos2d::Ref *pRef, Control::EventType type) {
    
    if (canbeClicked == false) {
        return;
    }
    canbeClicked = false;
    ControlButton* pBtn = dynamic_cast<ControlButton*>(pRef);
    pBtn->setEnabled(false);
    SoundPlayer::getInstance()->playHomeClickedEffect();
    
    pBtn->runAction(Sequence::create((Sequence*)getJellyAction(),CallFunc::create(std::bind(&GameLayerBase::showConfirmDialog, this)), CallFunc::create([=]{
        pBtn->setEnabled(true);
    }),NULL));
    
}

void GameLayerBase::showConfirmDialog(){
    AlertViewLayer* _layer = AlertViewLayer::createWithDelegateAndTitle(CC_CALLBACK_2(GameLayerBase::alertViewClickedButtonAtIndex, this), "Do you want to start over?");
    _layer->setTag(kHomeDialog);
    this->addChild(_layer, kDialog);
    log("添加提示框");
    this->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create(std::bind(&GameLayerBase::onPauseGame, this, nullptr)), NULL));
    log("暂停所有的东西！");
}

void GameLayerBase::alertViewClickedButtonAtIndex(AlertViewLayer *alert, int index) {
    if (alert->getTag() == kHomeDialog) {
        if (index == 1) {
            canbeClicked = true;
            onResumeGame(nullptr);
        }else {
//            Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
            homeClickEvent();
        }
    }else if (alert->getTag() == kBackDialog){
        if (index == 1) {
            canbeClicked = true;
        }else {
//            Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
            homeClickEvent();
        }
    }
}

void GameLayerBase::homeClickEvent(){
//    if (PurchaseManager::getInstance()->getRemoveAd() == false) {
//        STAds ads;
//        ads.requestInterstitialAds(true);
//    }
//    SceneManager::getInstance()->gotoMainScene();
}


void GameLayerBase::showNextButton(){
    if (nextBtn != nullptr) {
        return;
    }
    nextBtn = CocosHelper::getButton("ui/publish/next.png", "ui/publish/next.png");
    //    homeBtn->setAnchorPoint(Vec2(1.0, 1.0));
    nextBtn->setPosition(STVisibleRect::getPointOfSceneRightBottom() + Vec2(-15-nextBtn->getContentSize().width/2.0, 15+nextBtn->getContentSize().height/2.0));
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    nextBtn->setPositionY(nextBtn->getPositionY()+GameController::getInstance()->getBannerSize());
#endif
    nextBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayerBase::onNextButtonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    nextBtn->setZoomOnTouchDown(false);
    addChild(nextBtn, kHomeBtn);
}

void GameLayerBase::onNextButtonClicked(cocos2d::Ref *pRef, Control::EventType type) {
    if (canbeClicked == false) {
        return;
    }
    canbeClicked = true;
//    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    ControlButton* pNode = dynamic_cast<ControlButton*>(pRef);
    if (pNode->getNumberOfRunningActions() != 0) {
        return;
    }
    pNode->setEnabled(false);
    pNode->runAction(Sequence::create((Sequence*)getJellyAction(),CallFunc::create(std::bind(&GameLayerBase::nextClickEvent, this)), NULL));
}

void GameLayerBase::nextClickEvent(){
    SoundPlayer::getInstance()->playNextClickedEffect();
//    SceneManager::getInstance()->gotoChooseMap();
}

void GameLayerBase::setADVisible(bool visible) {

}

void GameLayerBase::onKeyBackClicked(){
    showConfirmDialog();
    log("点击返回键按钮！！");

}

void GameLayerBase::onExit(){
    SoundPlayer::getInstance()->stopAlleffect();
//    if (PurchaseManager::getInstance()->getRemoveAd() == false) {
//        STAds ads;
//        ads.setAdsVisibility(false);
//    }
    KeypadBaseLayer::onExit();
    
}


void GameLayerBase::onPause()
{

    NotificationCenter::getInstance()->postNotification(kPuaseTip);
    this->pause();

}

void GameLayerBase::onResume()
{
    
    NotificationCenter::getInstance()->postNotification(kResumeTip);
    this->resume();
    
}


Action *GameLayerBase::getJellyAction()
{
    Action *ret = NULL;
    
    ScaleTo *lScale1 = ScaleTo::create(0.13, 1.0, 0.90);
    ScaleTo *lScale2 = ScaleTo::create(0.11, 0.92, 1.0);
    ScaleTo *lScale3 = ScaleTo::create(0.10, 1.0, 0.96);
    ScaleTo *lScale4 = ScaleTo::create(0.09, 0.98, 1.0);
    ScaleTo *lScale5 = ScaleTo::create(0.08, 1.0, 0.99);
    ScaleTo *lScale6 = ScaleTo::create(0.07, 0.99, 1.0);
    ret = Sequence::create(lScale1, lScale2, lScale3, lScale4, lScale5, lScale6, NULL);
    return ret;
}

void GameLayerBase::setNextHidden(bool hidden) {
    if (nextBtn != nullptr) {
        nextBtn->setVisible(hidden);
    }
}

void GameLayerBase::setHomeHidden(bool hidden) {
    if (homeBtn != nullptr) {
        homeBtn->setVisible(hidden);
    }
}


void GameLayerBase::setNextButtonZorder(int zorder) {
    if (nextBtn != nullptr) {
        nextBtn->setLocalZOrder(zorder);
    }
}