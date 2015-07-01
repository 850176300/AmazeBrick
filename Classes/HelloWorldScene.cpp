#include "HelloWorldScene.h"
#include "VisibleRect.h"
#include "b2BodySprite.h"
#include "Box2dPhysicSprite.h"
#include "STVisibleRect.h"
#include "Config.h"
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

HelloWorld::~HelloWorld(){
    NotificationCenter::getInstance()->removeObserver(this, kMoveNotifyEvent);
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
    obstacleY = STVisibleRect::getPointOfSceneLeftUp().y;
//    obstacleLayer = LayerColor::create();
//    obstacleLayer->setPosition(Vec2(STVisibleRect::getOriginalPoint().x, STVisibleRect::getPointOfSceneLeftUp().y));
//    addChild(obstacleLayer);
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
    brickSprite = BrickSprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-block.png"));
    brickSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x, startCenterY - 50));
    brickSprite->setColor(Color3B::BLACK);
    brickSprite->addComponent(new BrickComponent());
    brickSprite->scheduleUpdate();
    addChild(brickSprite, 1);
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::onRecieveEvent), kMoveNotifyEvent, nullptr);
    this->schedule(schedule_selector(HelloWorld::checkRect));
    return true;
}

void HelloWorld::checkRect(float dt) {
    
}


void HelloWorld::onRecieveEvent(cocos2d::Ref *pRef){
    __String* data = dynamic_cast<__String*>(pRef);
    float infor = atof(data->getCString());
    float distance = infor - (((int)infor) / 1000)*1000;
    increaseY += distance;
    checkNeedAddBodys();
}

void HelloWorld::checkNeedAddBodys(){
    if (increaseY > 800) {
        increaseY = 0;
        runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create(std::bind(&HelloWorld::addlongBrick, this)), NULL));
    }
}

void HelloWorld::addlongBrick(){
    float deltax = arc4random() % 10 ;
    deltax = (deltax - 5) * 30;
    {
        b2BodySprite* pSprite = b2BodySprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-long.png"));
        pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + deltax - pSprite->getContentSize().width/2.0, obstacleY + pSprite->getContentSize().height / 2.0));
        pSprite->setColor(Color3B(200, 240, 240));
        addChild(pSprite);
        pSprite->addMoveEventNotify();
    }
    {
        b2BodySprite* pSprite = b2BodySprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ingame-brick-long.png"));
        pSprite->setPosition(Vec2(STVisibleRect::getCenterOfScene().x + deltax + 220 + pSprite->getContentSize().width/2.0, obstacleY + pSprite->getContentSize().height / 2.0));
        
        pSprite->setColor(Color3B(200, 240, 240));
        addChild(pSprite);
        pSprite->addMoveEventNotify();
        
    }
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    if (touch->getLocation().x > Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width / 2.0) {
        brickSprite->tapRSide();
    }else {
        brickSprite->tapLSide();
    }

    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
//    b2Vec2 vel = _Brickbody->GetLinearVelocity();

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
