//
//  KeypadDispatchCenter.h
//  HUGS108-IcePrincess Spa
//
//  Created by tanshoumei on 14-7-17.
//
//

#pragma once

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class KeypadDelegate
{
public:
    // The back key clicked
    virtual void onKeyBackClicked() {};
};

class KeypadDispatchCenter: public Ref
{
public:
    static KeypadDispatchCenter* getInstance();
    
    KeypadDispatchCenter();
    ~KeypadDispatchCenter();
    
    void addDelegate(Ref* apDelegate);
    void removeDelegate(Ref* apDelegate);
    
    // The back key clicked
    virtual void keyBackClicked();
    
    // The menu key clicked. only available on wophone & android
    virtual void keyMenuClicked() {};
protected:
    Vector<Ref*> m_pDelegates;
    EventListenerKeyboard* m_pKeyBoardListener;
};

class KeypadBaseLayer: public Layer, public KeypadDelegate
{
public:
    virtual void onEnter();
    virtual void onExit();
};
