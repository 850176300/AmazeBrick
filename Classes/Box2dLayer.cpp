//
//  Box2dLayer.cpp
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/8.
//
//

#include "Box2dLayer.h"
#include "VisibleRect.h"

#include "STVisibleRect.h"
#include "b2BodySprite.h"
#include "GB2ShapeCache-x.h"
#include "Config.h"
#define PTM_RATIO 32.0
USING_NS_ST;

Scene* Box2dLayer::scene(){
    Scene* pscene = Scene::create();
    
    Box2dLayer* pLayer = Box2dLayer::createWithePhysic();
    
    pscene->addChild(pLayer);
    
    return pscene;
}

Box2dLayer*  Box2dLayer::createWithePhysic(){
    Box2dLayer* pRet = new Box2dLayer();
    if (pRet && pRet->init()) {
        pRet->initPhysics();
        pRet->scheduleUpdate();
        pRet->addB2Body();
        pRet->addBrickBody();
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool Box2dLayer::init(){
    if (Layer::init()) {
        Sprite* bg = Sprite::create("bg.png");
        bg->setPosition(STVisibleRect::getCenterOfScene());
        addChild(bg);
        
        obstacleY = STVisibleRect::getPointOfSceneLeftUp().y;
        centerY = STVisibleRect::getCenterOfScene().y + 50;
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common.plist");
        
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(_swallowsTouches);
        
        listener->onTouchBegan = CC_CALLBACK_2(Box2dLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(Box2dLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(Box2dLayer::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(Box2dLayer::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Box2dLayer::onRecieveEvent), kMoveNotifyEvent, nullptr);
        return true;
    }
    return false;
}

void Box2dLayer::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, 40.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    world->SetContactListener(this);
    world->SetContinuousPhysics(true);
    
             _debugDraw = new GLESDebugDraw( PTM_RATIO );
             world->SetDebugDraw(_debugDraw);
    
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
                flags += b2Draw::e_jointBit;
                flags += b2Draw::e_aabbBit;
    //            flags += b2Draw::e_pairBit;
                flags += b2Draw::e_centerOfMassBit;
        _debugDraw->SetFlags(flags);
    //
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.userData = (void*)kEdge;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
}

void Box2dLayer::update(float dt) {
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
   
}

void Box2dLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    Layer::draw(renderer, transform, flags);
    
    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    _modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(Box2dLayer::onDraw, this);
    renderer->addCommand(&_customCommand);

    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}

void Box2dLayer::onDraw()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    Mat4 oldMV;
    oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
    world->DrawDebugData();
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}

void Box2dLayer::onRecieveEvent(cocos2d::Ref *pref) {
    __String* data = dynamic_cast<__String*>(pref);
    float infor = atof(data->getCString());
    float distance = infor - (((int)infor) / 1000)*1000;
    increaseY += distance;
    checkNeedAddBodys();
}

void Box2dLayer::addB2Body(){
    float deltax = arc4random() % 10 ;
    deltax = (deltax - 5) * 30;
    {
        Box2dPhysicSprite* pSprite = Box2dPhysicSprite::create("brick2.png");
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.userData = (void*)kMonster;
        bodyDef.position.Set((STVisibleRect::getCenterOfScene().x + deltax - pSprite->getContentSize().width/2.0)/PTM_RATIO, (obstacleY)/PTM_RATIO);
        b2Body* _body = world->CreateBody(&bodyDef);
        // Define another box shape for our dynamic body.
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(_body, "brick2");
        
        _body->SetGravityScale(0);
        _body->SetBullet(true);
        pSprite->setB2Body(_body);
        pSprite->setPTMRatio(PTM_RATIO);
        pSprite->setColor(Color3B(220, 250, 160));
        pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + deltax - pSprite->getContentSize().width/2.0, obstacleY));
        addChild(pSprite);
        pSprite->addMoveEventNotify();
    }
    {
        Box2dPhysicSprite* pSprite = Box2dPhysicSprite::create("brick2.png");
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.userData = (void*)kMonster;
        bodyDef.position.Set((STVisibleRect::getCenterOfScene().x + deltax + 320 + pSprite->getContentSize().width/2.0)/PTM_RATIO, (obstacleY )/PTM_RATIO);
        b2Body* _body = world->CreateBody(&bodyDef);
        // Define another box shape for our dynamic body.

        
        GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(_body, "brick2");
        _body->SetGravityScale(0);
        _body->SetBullet(true);
        pSprite->setB2Body(_body);
        pSprite->setPTMRatio(PTM_RATIO);
        pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + deltax + 250 + pSprite->getContentSize().width/2.0, obstacleY));
        pSprite->setColor(Color3B(220, 250, 160));
        addChild(pSprite);
        pSprite->addMoveEventNotify();
    }

    {
        
        
    }
}

void Box2dLayer::addBrickBody(){
    brickSprite = BrickSprite::create("brick1.png");
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = (void*)kBrick;
    bodyDef.position.Set(STVisibleRect::getCenterOfScene().x / PTM_RATIO, (STVisibleRect::getCenterOfScene().y - 50) / PTM_RATIO);
    _Brickbody = world->CreateBody(&bodyDef);
    // Define another box shape for our dynamic body.
    
    GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(_Brickbody, "brick1");
    
    _Brickbody->SetGravityScale(0);
    _Brickbody->SetBullet(true);
    //    b2MassData* pData = nullptr;
    //    _Brickbody->GetMassData(pData);
    brickSprite->setB2Body(_Brickbody);
    brickSprite->setPTMRatio(PTM_RATIO);
    brickSprite->setColor(Color3B::BLACK);
    brickSprite->setIgnoreBodyRotation(true);
    _Brickbody->SetFixedRotation(false);
    brickSprite->addComponent(new BrickComponent());
    addChild(brickSprite);
    brickSprite->scheduleUpdate();
}

bool Box2dLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (touch->getLocation().x > Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2.0) {
        brickSprite->tapRSide();
    }else {
        brickSprite->tapLSide();
    }
    return true;
}

void Box2dLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    //    b2Vec2 vel = _Brickbody->GetLinearVelocity();
    
}

void Box2dLayer::resetGravity(float dt){
    canTwiceClick = false;
    //    world->SetGravity(b2Vec2(0, 20));
    _Brickbody->SetGravityScale(-1.0);
}

void Box2dLayer::checkNeedPostEvent(float dt){
    if (brickSprite->getBoundingBox().getMaxY() > centerY) {
        NotificationCenter::getInstance()->postNotification(kMoveNotifyEvent);
        unschedule(schedule_selector(Box2dLayer::checkNeedPostEvent));
        increaseY += 60;
        checkNeedAddBodys();
    }
}

void Box2dLayer::checkNeedAddBodys(){
    if (increaseY > 800) {
        increaseY = 0;
        runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create(std::bind(&Box2dLayer::addB2Body, this)), NULL));
    }
}

void Box2dLayer::BeginContact(b2Contact *contact) {
    
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    char* Astring = (char*)bodyA->GetUserData();
    char* Bstring = (char*)bodyB->GetUserData();
    //    log("A string is %s", Astring);
    //    log("B string is %s", Bstring);
    if (CompareTwo(__String::create(Astring), __String::create(Bstring), kBrick, kMonster) == true) {
//        world->SetContactListener(nullptr);
//        brickSprite->brickDie();
        
//        b2Vec2 speedVec = _Brickbody->GetLinearVelocity();
//        _Brickbody->SetLinearVelocity(b2Vec2(0, 0));
//        _Brickbody->SetAngularVelocity(0);
//        JumpNow = false;
//        float distance = 0.5*(fabs(speedVec.y)*0.5 - 300/PTM_RATIO*0.5*0.5)*PTM_RATIO;//fabs(speedVec.y * 0.5 * PTM_RATIO);
//        float disx = xForce * 0.25 * 5;
//        NotificationCenter::getInstance()->postNotification(kMoveNotifyEvent, __String::createWithFormat("%.2f", distance));
//        brickSprite->runAction(MoveBy::create(0.5, Vec2(disx, 0)));
//        increaseY += distance;
//        checkNeedAddBodys();
    }
}

void Box2dLayer::EndContact(b2Contact *contact) {
    
}


bool Box2dLayer::CompareTwo(cocos2d::__String *src1, cocos2d::__String *src2, const string &dst1, const string &dst2) {
    if (string(src1->getCString()).find(dst1.c_str()) != string::npos && string(src2->getCString()).find(dst2.c_str()) != string::npos) {
        return true;
    }
    if (string(src1->getCString()).find(dst2.c_str()) != string::npos && string(src2->getCString()).find(dst1.c_str())  != string::npos) {
        return true;
    }
    return false;
}