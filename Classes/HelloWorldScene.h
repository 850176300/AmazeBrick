#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
using namespace cocos2d;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    static HelloWorld* createWithPhysic();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually

    
private:
    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    void initPhysics();
    void update(float dt);
    void onDraw();
    b2World* world;
    Mat4 _modelViewMV;
    CustomCommand _customCommand;
    GLESDebugDraw* _debugDraw;
};

#endif // __HELLOWORLD_SCENE_H__
