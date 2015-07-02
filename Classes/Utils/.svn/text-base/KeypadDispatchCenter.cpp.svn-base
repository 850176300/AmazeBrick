//
//  KeypadDispatchCenter.cpp
//  HUGS108-IcePrincess Spa
//
//  Created by tanshoumei on 14-7-17.
//
//

#include "KeypadDispatchCenter.h"
static KeypadDispatchCenter* s_KeypadDispatchCenter = NULL;

KeypadDispatchCenter* KeypadDispatchCenter::getInstance()
{
    if(!s_KeypadDispatchCenter)
        s_KeypadDispatchCenter = new KeypadDispatchCenter;
    return s_KeypadDispatchCenter;
}

KeypadDispatchCenter::KeypadDispatchCenter()
{
    log("%s", __FUNCTION__);
    m_pKeyBoardListener = EventListenerKeyboard::create();
    m_pKeyBoardListener->onKeyPressed = [this](EventKeyboard::KeyCode code, Event*){
        log("%s %d onKeyPressed", __FUNCTION__, code);
        switch (code) {
            case EventKeyboard::KeyCode::KEY_BACK:
                keyBackClicked();
                break;
                
            default:
                break;
        }
    };
    m_pKeyBoardListener->onKeyReleased = [this](EventKeyboard::KeyCode code, Event*){
        log("%s %d onKeyReleased", __FUNCTION__, code);
        switch (code) {
            case EventKeyboard::KeyCode::KEY_BACK:
                keyBackClicked();
                break;
                
            default:
                break;
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(m_pKeyBoardListener, 1);
}

KeypadDispatchCenter::~KeypadDispatchCenter()
{
    Director::getInstance()->getEventDispatcher()->removeEventListener(m_pKeyBoardListener);
}

void KeypadDispatchCenter::addDelegate(Ref *apDelegate)
{
    log("添加返回键监听事件");
    m_pDelegates.pushBack(apDelegate);
}

void KeypadDispatchCenter::removeDelegate(cocos2d::Ref *apDelegate)
{
    log("释放监听");
    m_pDelegates.eraseObject(apDelegate);
}

void KeypadDispatchCenter::keyBackClicked()
{
    CCLOG("%s size:%d", __FUNCTION__, m_pDelegates.size());
    for (int i = (int)m_pDelegates.size() - 1; i >= 0; --i) {
        KeypadDelegate* lpDelegate = dynamic_cast<KeypadDelegate*>(m_pDelegates.at(i));
        if(lpDelegate)
        {
            lpDelegate->onKeyBackClicked();
            break;
        }
    }
}

void KeypadBaseLayer::onEnter()
{
    Layer::onEnter();
    KeypadDispatchCenter::getInstance()->addDelegate(this);
}

void KeypadBaseLayer::onExit()
{
    Layer::onExit();
    KeypadDispatchCenter::getInstance()->removeDelegate(this);
}