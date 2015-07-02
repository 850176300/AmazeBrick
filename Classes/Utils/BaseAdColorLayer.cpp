//
//  BaseAdColorLayer.cpp
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 15-1-28.
//
//

#include "BaseAdColorLayer.h"
#include "STAds.h"
//#include "PurchaseManager.h"
#include "GameLayerBase.h"
#include "SuperGlobal.h"

BaseAdColorLayer::BaseAdColorLayer(){
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BaseAdColorLayer::onPauseGame), kPuaseTip, nullptr);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BaseAdColorLayer::onResumeGame), kResumeTip, nullptr);
}
BaseAdColorLayer::~BaseAdColorLayer(){
    NotificationCenter::getInstance()->removeObserver(this, kPuaseTip);
    NotificationCenter::getInstance()->removeObserver(this, kResumeTip);
}

void BaseAdColorLayer::onEnter(){
    LayerColor::onEnter();
    if (getParent()) {
        GameLayerBase* _layer = (GameLayerBase*)getParent();
        if (_layer->isNeedShowAD()) {
//            if (PurchaseManager::getInstance()->getRemoveAd() == false) {
//                STAds ads;
//                ads.setAdsVisibility(false);
//            }
        }
    }
}

void BaseAdColorLayer::onExit(){
    LayerColor::onExit();
    if (getParent()) {
        GameLayerBase* _layer = (GameLayerBase*)getParent();
        if (_layer->isNeedShowAD()) {
//            if (PurchaseManager::getInstance()->getRemoveAd() == false) {
//                STAds ads;
//                ads.requestAds();
//                ads.setAdsVisibility(true);
//            }
        }
    }
}


void BaseAdColorLayer::onPauseGame(cocos2d::Ref *_ref) {
    pause();
}

void BaseAdColorLayer::onResumeGame(cocos2d::Ref *_ref) {
    resume();
}