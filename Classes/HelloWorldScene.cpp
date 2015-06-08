#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "b2BodySprite.h"
#include "Box2dPhysicSprite.h"
#include "STVisibleRect.h"
USING_NS_CC;
USING_NS_ST;
#define PTM_RATIO 32.0
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::createWithPhysic();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld* HelloWorld::createWithPhysic(){
    HelloWorld* pRet = new HelloWorld();
    if (pRet && pRet->init()) {
        pRet->initPhysics();
        pRet->scheduleUpdate();
        pRet->addB2Body();
        pRet->addBrickBody();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

void HelloWorld::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, 40.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    
    world->SetContinuousPhysics(true);
    
//         _debugDraw = new GLESDebugDraw( PTM_RATIO );
//         world->SetDebugDraw(_debugDraw);
//    
//    uint32 flags = 0;
//    flags += b2Draw::e_shapeBit;
//            flags += b2Draw::e_jointBit;
//            flags += b2Draw::e_aabbBit;
////            flags += b2Draw::e_pairBit;
//            flags += b2Draw::e_centerOfMassBit;
//    _debugDraw->SetFlags(flags);
//    
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
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

void HelloWorld::update(float dt) {
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
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
    _customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this);
    renderer->addCommand(&_customCommand);
    
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}

void HelloWorld::onDraw()
{
    Director* director = Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    
    Mat4 oldMV;
    oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
    world->DrawDebugData();
    director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
    {
        return false;
    }
    obstacleLayer = LayerColor::create(Color4B(00, 0, 0, 150));
    obstacleLayer->setPosition(Vec2(STVisibleRect::getOriginalPoint().x, STVisibleRect::getPointOfSceneLeftUp().y));
    addChild(obstacleLayer);
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("common.plist");
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HelloWorld::addB2Body(){
    
    {
        Box2dPhysicSprite* pSprite = Box2dPhysicSprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-long.png"));
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pSprite->getContentSize().width/2.0/PTM_RATIO, pSprite->getContentSize().height/2.0/PTM_RATIO);
        b2Body* _body = world->CreateBody(&bodyDef);
        // Define another box shape for our dynamic body.
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(7.6,1.05);
        
        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.0f;
        fixtureDef.restitution = 0.0f;
        
        _body->CreateFixture(&fixtureDef);
        _body->SetGravityScale(-1.0);
        _body->SetBullet(true);
        pSprite->setB2Body(_body);
        pSprite->setPTMRatio(PTM_RATIO);
        pSprite->setPosition(Vec2(300, 800));
        addChild(pSprite);
    }
    {
        Box2dPhysicSprite* pSprite = Box2dPhysicSprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-long.png"));
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(pSprite->getContentSize().width/2.0/PTM_RATIO, pSprite->getContentSize().height/2.0/PTM_RATIO);
        b2Body* _body = world->CreateBody(&bodyDef);
        // Define another box shape for our dynamic body.
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(7.6,1.05);
        
        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.0f;
        fixtureDef.restitution = 0.0f;
        
        _body->CreateFixture(&fixtureDef);
        _body->SetGravityScale(-1.0);
        _body->SetBullet(true);
        pSprite->setB2Body(_body);
        pSprite->setPTMRatio(PTM_RATIO);
        pSprite->setPosition(Vec2(300, 800));
        addChild(pSprite);
    }
}

void HelloWorld::addBrickBody(){
    Box2dPhysicSprite* pSprite = Box2dPhysicSprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-block.png"));
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pSprite->getContentSize().width/2.0/PTM_RATIO, pSprite->getContentSize().height/2.0/PTM_RATIO);
    _Brickbody = world->CreateBody(&bodyDef);
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.7,0.7);
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.05f;
    fixtureDef.friction = 2.0f;
    fixtureDef.restitution = 0.0f;
    
    _Brickbody->CreateFixture(&fixtureDef);
    _Brickbody->SetGravityScale(-1.0);
    _Brickbody->SetBullet(true);
//    b2MassData* pData = nullptr;
//    _Brickbody->GetMassData(pData);
    pSprite->setB2Body(_Brickbody);
    
    pSprite->setPTMRatio(PTM_RATIO);
    pSprite->setPosition(Vec2(250, 300));
    pSprite->setColor(Color3B::BLACK);
    pSprite->setIgnoreBodyRotation(true);
    addChild(pSprite);
    

}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    float xForce = -25;
    float yFroce = 120;
    if (touch->getLocation().x > Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2.0) {
        xForce = 25;
    }
    if (canTwiceClick == false) {
        canTwiceClick = true;
        _Brickbody->SetLinearVelocity(b2Vec2(0, 0));
        yFroce = 80;
        xForce = (xForce > 0 ? 1 : -1)*35;
        this->scheduleOnce(schedule_selector(HelloWorld::resetGravity), 0.5f);
    }else {
        _Brickbody->SetAngularVelocity(0);
        
    }
    //    log("the speed is %.2f, %.2f", vel.x, vel.y);
    //    world->SetGravity(b2Vec2(0, 10));
    _Brickbody->ApplyForce(b2Vec2(xForce, 120), _Brickbody->GetWorldCenter(), false);
    
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
//    b2Vec2 vel = _Brickbody->GetLinearVelocity();

}

void HelloWorld::resetGravity(float dt){
    canTwiceClick = false;
//    world->SetGravity(b2Vec2(0, 20));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
