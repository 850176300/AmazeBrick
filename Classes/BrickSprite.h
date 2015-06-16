//
//  BrickSprite.h
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/14.
//
//

#ifndef __com_kekeapp_amazebrick__BrickSprite__
#define __com_kekeapp_amazebrick__BrickSprite__

#include <iostream>
#include "cocos2d.h"
#include "Box2dPhysicSprite.h"
USING_NS_CC;
using namespace std;
class BrickSprite : public Box2dPhysicSprite{
public:
    enum BrickStatues{
        kDie = 1,
        kTouchL,
        kTouchR,
        kIdle,
    };
public:
    static BrickSprite* createWithSpriteFrame(SpriteFrame* frame);
    
    static BrickSprite* create(const string& file);
    
    virtual bool initWithFilename(const string& file);
    
    virtual bool initWithFrame(SpriteFrame* frame);
    
    CC_SYNTHESIZE(BrickStatues, statue, Statues);
    
    void brickDie();
    
    void tapRSide();
    
    void tapLSide();
    
};

#endif /* defined(__com_kekeapp_amazebrick__BrickSprite__) */
