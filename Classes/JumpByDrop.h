//
//  JumpByDrop.h
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/14.
//
//

#ifndef com_kekeapp_amazebrick_JumpByDrop_h
#define com_kekeapp_amazebrick_JumpByDrop_h

#include <iostream>
#include <vector>
#include "cocos2d.h"
USING_NS_CC;

class JumpByDrop : public FiniteTimeAction{
    
public:
    JumpByDrop();
    
    virtual ~JumpByDrop(){};
    static JumpByDrop* create(float duration, const Vec2& position, float height, int jumps);
    
    bool initWithDuration(float duration, const Vec2& position, float height, int jumps);
    

    virtual void update(float) override;
    virtual bool isDone(void) const override;
    virtual void step(float dt) override;
    virtual void startWithTarget(Node *target) override;
    virtual JumpByDrop* reverse() const override;
    virtual JumpByDrop *clone() const override;
    /** how many seconds had elapsed since the actions started to run. */
    inline float getElapsed(void) { return _elapsed; }
    
    //extension in GridAction
    void setAmplitudeRate(float amp);
    float getAmplitudeRate(void);
    
protected:
    Vec2           _startPosition;
    Vec2           _delta;
    float           _height;
    int             _jumps;
    Vec2           _previousPos;
    float _elapsed;
    bool   _firstTick;
private:
    CC_DISALLOW_COPY_AND_ASSIGN(JumpByDrop);
};

#endif
