//
// AlertViewLayer.cpp
// PetPlay
//
// Created by jianghai on 14-9-9.
//
//

#include "AlertViewLayer.h"
#include "CocosHelper.h"
#define kButtonYes 101
#define kButtonNo  102


AlertViewLayer::AlertViewLayer()
{
    _callBack = nullptr;
    _Yes= nullptr;
    _No =nullptr;
    justOneButton = false;
}

AlertViewLayer::~AlertViewLayer()
{
    
}

AlertViewLayer* AlertViewLayer::createWithDelegateAndTitle(ccAlertViewCallBack callback,const char* title)
{
    auto pRet = new AlertViewLayer();
    if(pRet->initWithDelegateAndTitle(callback,title))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool AlertViewLayer::init()
{
    return initWithDelegateAndTitle(nullptr,NULL);
}
bool AlertViewLayer::initWithDelegateAndTitle(ccAlertViewCallBack callback,const char* title)
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255/2)))
    {
        return false;
    }
    _callBack = callback;
    //注册touch监听，防止在alertView出现的时候不能屏蔽下层事件
    __touchListener = EventListenerTouchOneByOne::create();
    __touchListener->setSwallowTouches(true);
    
    __touchListener->onTouchBegan = CC_CALLBACK_2(AlertViewLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(__touchListener, this);
    
    
    _title = title;
    
    _banner = Sprite::create("ui/tanchuang_1.png");
    _Yes =  CocosHelper::getButton("ui/yes.png", "ui/yes.png");
    _No = CocosHelper::getButton("ui/no.png", "ui/no.png");
    _Yes->addTargetWithActionForControlEvents(this, cccontrol_selector(AlertViewLayer::buttonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    _No->addTargetWithActionForControlEvents(this, cccontrol_selector(AlertViewLayer::buttonClicked), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE);
    _Yes->setTag(kButtonYes);
    _No->setTag(kButtonNo);
    
    _banner->setPosition(STVisibleRect::getCenterOfScene());
    _Yes->setPosition(155, 80);
    _No->setPosition(415, 80);
    
    _banner->addChild(_Yes);
    _banner->addChild(_No);
    
    
    //添加标题
//    Label *label = Label::createWithBMFont("TextFile.fnt",title);// GetWrapStr(title, 15));
    TTFConfig config2 = TTFConfig("fonts/Comic Sans MS Bold.ttf", 40, GlyphCollection::DYNAMIC);
    
    Label *label = Label::createWithTTF(config2, title);
    
    // label->setContentSize(Size(300,100));
    label->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    label->setDimensions(500, 240);
    label->setPosition(280,200);
    _banner->addChild(label);
    
    this->addChild(_banner);
    
    _banner->setScale(0);
    
    _Yes->setEnabled(false);
    _No->setEnabled(false);
    _banner->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(.3f, 1)),CallFunc::create([&](){
        if (_No) {
            _No->setEnabled(true);
        }
        if (_Yes) {
            _Yes->setEnabled(true);
        }
    }), nullptr));
    
    return true;
}

void AlertViewLayer::setAlertViewCallBack(ccAlertViewCallBack _call) {
    _callBack = _call;
}

void AlertViewLayer::buttonClicked(cocos2d::Ref *psender, Control::EventType type)
{
    _banner->runAction(Sequence::create(EaseBackIn::create(ScaleTo::create(.3f, 0)),CallFunc::create([&,psender](){
        if(dynamic_cast<ControlButton*>(psender)->getTag() == kButtonYes)
        {
            if (_callBack) {
                _callBack(this, 0);
            }
        }
        else
        {
            if (_callBack) {
                _callBack(this, 1);
            }
        }
        this->removeFromParentAndCleanup(true);
    }), nullptr));
}
#pragma mark --touch event--
bool AlertViewLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
    return true;
}

void AlertViewLayer::onEnter(){
    KeypadDispatchCenter::getInstance()->addDelegate(this);
    
    LayerColor::onEnter();
    if (justOneButton == true) {
        _No->removeFromParent();
        _No = nullptr;
        _Yes->setPositionX(_banner->getContentSize().width/2.0);
    }
}
void AlertViewLayer::onExit()
{
    KeypadDispatchCenter::getInstance()->removeDelegate(this);
    LayerColor::onExit();
}

void AlertViewLayer::onKeyBackClicked(){
    _banner->runAction(Sequence::create(EaseBackIn::create(ScaleTo::create(.3f, 0)),CallFunc::create([this](){
        if (_callBack) {
            _callBack(this, 1);
        }
        this->removeFromParentAndCleanup(true);
    }), nullptr));
}