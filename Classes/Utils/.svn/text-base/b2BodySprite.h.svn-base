//
//  b2BodySprite.h
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 15-1-13.
//
//

#ifndef __DND2052_Baby_Play_Town__b2BodySprite__
#define __DND2052_Baby_Play_Town__b2BodySprite__

#include <iostream>
#include "cocos2d.h"
#include <Box2D/Box2D.h>
using namespace std;
USING_NS_CC;

class b2BodySprite : public Sprite{
public:
    
    static b2BodySprite* create(const string& filename);
    static b2BodySprite* createWithTexture(Texture2D* texture);
    
    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);
    
    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);
    void setPosition(const cocos2d::Vec2 &pos);
    void setPositionWithBool(const cocos2d::Vec2 &pos, bool ignorgAnchorPoint);
protected:
    float   PTMRatio;
private:
    
    b2Body  *_pB2Body;
    
//    float   _PTMRatio;
//    float   _PTMRatio;
};

#endif /* defined(__DND2052_Baby_Play_Town__b2BodySprite__) */
