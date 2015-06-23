//
//  Box2dPhysicSprite.h
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 15-1-22.
//
//

#ifndef __DND2052_Baby_Play_Town__Box2dPhysicSprite__
#define __DND2052_Baby_Play_Town__Box2dPhysicSprite__

#include <iostream>
#include "cocos2d.h"
#include <Box2d/Box2d.h>
using namespace std;
USING_NS_CC;



class Box2dPhysicSprite : public Sprite{
public:
    
    static Box2dPhysicSprite* create();
    
    static Box2dPhysicSprite* createWithTexture(Texture2D *pTexture);
    
    static Box2dPhysicSprite* createWithTexture(Texture2D *pTexture, const Rect& rect);
    
    static Box2dPhysicSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
    
    static Box2dPhysicSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    
    static Box2dPhysicSprite* create(const string &pszFileName);
    static Box2dPhysicSprite* create(const string &pszFileName, const Rect& rect);
    
    Box2dPhysicSprite();
    
    ~Box2dPhysicSprite();
    
    virtual bool isDirty() const;
    
    bool isIgnoreBodyRotation() const;
    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);
    
    
    b2Body* getB2Body() const;
    void setB2Body(b2Body *pBody);
    
    float getPTMRatio() const;
    void setPTMRatio(float fPTMRatio);
    
    // overrides
    virtual const Vec2& getPosition() const override;
    virtual void getPosition(float* x, float* y) const override;
    virtual float getPositionX() const override;
    virtual float getPositionY() const override;
    virtual void setPosition(const Vec2 &position) override;
    virtual float getRotation() const override;
    virtual void setRotation(float fRotation) override;
    virtual void syncPhysicsTransform() const;
    virtual const Mat4& getNodeToParentTransform() const override;
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
    void addMoveEventNotify();
protected:
    void onRecieveEvent(Ref* pRef);
    void checkNeedRemove();
    const Vec2& getPosFromPhysics() const;
    
protected:
    bool hadAddNotify = false;
    bool    _ignoreBodyRotation;
    
    // box2d specific
    b2Body  *_pB2Body;
    float   fPTMRatio;
    
};
#endif /* defined(__DND2052_Baby_Play_Town__Box2dPhysicSprite__) */
