#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "BrickComponent.h"
using namespace cocos2d;
class HelloWorld : public cocos2d::LayerColor
{
public:
    ~HelloWorld();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    static HelloWorld* createWithPhysic();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually

    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event){}
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event){}
protected:
    void onRecieveEvent(Ref* pRef);
    void checkNeedAddBodys();
    void checkRect(float dt);
private:
    void addlongBrick();
    BrickSprite* brickSprite = nullptr;
    float obstacleY = 0;
    float startCenterY ;
    float increaseY = 0;
};

#endif // __HELLOWORLD_SCENE_H__
