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
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
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
    obstacleLayer = LayerColor::create();
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
    
    addlongBrick();
    
    startCenterY = STVisibleRect::getCenterOfScene().y;
    brickSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-block.png"));
    brickSprite->setPosition(STVisibleRect::getCenterOfScene().x, startCenterY - 50);
    brickSprite->setColor(Color3B::BLACK);
    addChild(brickSprite, 1);
    
    return true;
}

void HelloWorld::addlongBrick(){
    float deltax = arc4random() % 10 ;
    deltax = (deltax - 5) * 30;
    {
        Sprite* pSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-long.png"));
        pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + deltax - pSprite->getContentSize().width/2.0, obstacleY + pSprite->getContentSize().height / 2.0));
        pSprite->setColor(Color3B(200, 240, 240));
        obstacleLayer->addChild(pSprite);
    }
    {
        Sprite* pSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-long.png"));
        pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + deltax + 180 + pSprite->getContentSize().width/2.0, obstacleY + pSprite->getContentSize().height / 2.0));
        pSprite->setColor(Color3B(200, 240, 240));
        obstacleLayer->addChild(pSprite);
    }
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (isFirst == true){
        scheduleUpdate();
    }
    float xEnerge = -100;
    float yEnerge = 300;
//    if (touch->getLocation().x > Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2.0) {
//        xEnerge = 100;
//    }
//    speedx = xEnerge;
    speedx = 0;
    speedy = yEnerge;
    if (brickSprite->getPositionY() >= startCenterY) {
        
    }
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
//    b2Vec2 vel = _Brickbody->GetLinearVelocity();

}


void HelloWorld::update(float dt) {
    speedx += xgrabity*dt;
    if (fabs(speedx) <= 1) {
        speedx = 0;
    }
    speedy += graverty*dt;
    brickSprite->setPosition(brickSprite->getPosition() + Vec2(speedx*dt, speedy*dt));
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
