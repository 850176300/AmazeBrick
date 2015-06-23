//
//  BrickSprite.cpp
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/14.
//
//

#include "BrickSprite.h"

BrickSprite* BrickSprite::create(const string &file) {
    BrickSprite* pRet = new BrickSprite();
    if (pRet && pRet->initWithFilename(file)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

BrickSprite* BrickSprite::createWithSpriteFrame(cocos2d::SpriteFrame *frame) {
    BrickSprite* pRet = new BrickSprite();
    if (pRet && pRet->initWithFrame(frame)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool BrickSprite::initWithFrame(cocos2d::SpriteFrame *frame) {
    if (Sprite::initWithSpriteFrame(frame)) {
        statue = kIdle;
        return true;
    }
    return false;
}


bool BrickSprite::initWithFilename(const string &file) {
    if (Sprite::initWithFile(file)) {
        statue = kIdle;
        return true;
    }
    return false;
}

void BrickSprite::tapLSide(){
    if (statue == kDie) {
        return;
    }
    statue = kTouchL;
}

void BrickSprite::tapRSide(){
    if (statue == kDie) {
        return;
    }
    statue = kTouchR;
}

void BrickSprite::brickDie(){
    statue = kDie;
    unscheduleUpdate();
    runAction(EaseSineIn::create(MoveBy::create(0.5, Vec2(0, -1000))));
}
