//
//  SpriteInScrollview.cpp
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 15-1-19.
//
//

#include "SpriteInScrollview.h"
SpriteInScrollview* SpriteInScrollview::create(const char* apName)
{
    SpriteInScrollview* pItem = new SpriteInScrollview;
    pItem->initWithFile(apName);
    pItem->autorelease();
    return pItem;
}

SpriteInScrollview* SpriteInScrollview::createWithTexture(cocos2d::Texture2D *texture) {
    SpriteInScrollview* pItem = new SpriteInScrollview();
    pItem->initWithTexture(texture);
    pItem->autorelease();
    return pItem;
}

bool SpriteInScrollview::initWithFile(const char *pszFilename) {
    if (Sprite::initWithFile(pszFilename)) {
        return true;
    }
    return false;
}

bool SpriteInScrollview::initWithTexture(cocos2d::Texture2D *pTexture){
    if (Sprite::initWithTexture(pTexture)) {
        
        return true;
    }
    return false;
}