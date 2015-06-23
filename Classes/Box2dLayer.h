//
//  Box2dLayer.h
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/8.
//
//

#ifndef __com_kekeapp_amazebrick__Box2dLayer__
#define __com_kekeapp_amazebrick__Box2dLayer__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "Box2dPhysicSprite.h"
#include "BrickComponent.h"
USING_NS_CC;
using namespace std;

#define kCenterBox "centerBox"
#define kBrick "brick"
#define kEdge "edge"
#define kMonster "monster"
class Box2dLayer : public Layer, public b2ContactListener{
public:
    static Scene* scene();
    
    static Box2dLayer* createWithePhysic();
    
    virtual bool init();
    
    CREATE_FUNC(Box2dLayer);
    
protected:
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event){}
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event){}
    
    void addBrickBody();
    void addB2Body();
    void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    void initPhysics();
    void update(float dt);
    void onDraw();
    void resetGravity(float);
    void checkNeedPostEvent(float);
    void checkNeedAddBodys();
    virtual void BeginContact(b2Contact* contact) ;
    virtual void EndContact(b2Contact* contact) ;
    bool CompareTwo(cocos2d::__String *src1, cocos2d::__String *src2, const string &dst1, const string &dst2);
    void onRecieveEvent(Ref* pref);
private:
    
    b2World* world;
    Mat4 _modelViewMV;
    CustomCommand _customCommand;
        GLESDebugDraw* _debugDraw;
    b2Body* _Brickbody;
    BrickSprite* brickSprite;
    bool canTwiceClick = false;
//    LayerColor* obstacleLayer = nullptr;//障碍物的页面
    float obstacleY = 0;
    float centerY = 0;
    float increaseY = 0;
    bool JumpNow = false;
    float xForce;
};

#endif /* defined(__com_kekeapp_amazebrick__Box2dLayer__) */
