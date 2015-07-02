//
//  MovableItem.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#include "MovableItem.h"
#include "MathUtil.h"
#include "STVisibleRect.h"
#include "CocosHelper.h"
//#include "NotificationDef.h"
#include "SimpleAudioEngine.h"
#define NotifyGLViewWillLoseFocus "NotifyGLViewWillLoseFocus"
using namespace CocosDenshion;
USING_NS_ST;

MovableItem* MovableItem::create(const char* apName)
{
    MovableItem* pItem = new MovableItem;
    pItem->initWithFile(apName);
    pItem->autorelease();
    return pItem;
}

MovableItem* MovableItem::createWithTexture(cocos2d::Texture2D *texture) {
    MovableItem* pItem = new MovableItem();
    pItem->initWithTexture(texture);
    pItem->autorelease();
    return pItem;
}


MovableItem::MovableItem():
m_iTouchEndType(kMovableItemTouchEndStop),
m_pMove(0),
m_uiMovingEffectId(0),
m_uiSelectEffectId(0),
m_bMovingLoop(true),
m_pMovableItemDelegate(0),
isFirstTimeInEnter(true)
{
}

MovableItem::~MovableItem(){
   
}

bool MovableItem::initWithFile(const char *pszFilename)
{
    if(Sprite::initWithFile(pszFilename))
    {
        m_sInitName.append(pszFilename);
        m_sMovingName.append(pszFilename);
        m_enState = kMovableItemStateStill;
        float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
        float scaleY = Director::getInstance()->getOpenGLView()->getScaleY();
        m_tMoveRect.origin =Director::getInstance()->getOpenGLView()->getVisibleOrigin();
        m_tMoveRect.size = Size(STVisibleRect::getFrameSize().width / scaleX, STVisibleRect::getFrameSize().height / scaleY);
        CCLOG("%f,%f,%f,%f,", m_tMoveRect.origin.x, m_tMoveRect.origin.y, m_tMoveRect.size.width, m_tMoveRect.size.height);
        m_tMoveRect = STVisibleRect::getMovableRect();
        return true;
    }
    return false;
}

bool MovableItem::initWithTexture(cocos2d::Texture2D *pTexture) {
    if (Sprite::initWithTexture(pTexture)) {
        m_sInitName.append("movable");
        m_sMovingName.append("movable");
        m_enState = kMovableItemStateStill;
        float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
        float scaleY = Director::getInstance()->getOpenGLView()->getScaleY();
        m_tMoveRect.origin = Director::getInstance()->getOpenGLView()->getVisibleOrigin();
        m_tMoveRect.size = Size(STVisibleRect::getFrameSize().width / scaleX, STVisibleRect::getFrameSize().height / scaleY);
        CCLOG("%f,%f,%f,%f,", m_tMoveRect.origin.x, m_tMoveRect.origin.y, m_tMoveRect.size.width, m_tMoveRect.size.height);
        m_tMoveRect = STVisibleRect::getMovableRect();
        return true;
    }
    return false;
}

void MovableItem::onEnter()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(MovableItem::TouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MovableItem::TouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MovableItem::TouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MovableItem::TouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    _touchListener = listener;
    Sprite::onEnter();
}

void MovableItem::onExit()
{
    _eventDispatcher->removeEventListener(_touchListener);
    Sprite::onExit();
//    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NotifyGLViewWillLoseFocus);
//    ItemBase::onExit();

//    CCSprite::onExit();
}

bool MovableItem::TouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    if(m_pMove){
        stopAction(m_pMove);
        m_pMove = NULL;
    }
    bool ret = CocosHelper::isPointInNode(this, pTouch->getLocation());
    if(ret)
    {
        CCLOG("MovableItem::ccTouchBegan:%s", m_sSelectSoundEffect.c_str());
        m_uiSelectEffectId = SimpleAudioEngine::getInstance()->playEffect(m_sSelectSoundEffect.c_str());
        changeToMoving();
        if (m_pMovableItemDelegate) {
            m_pMovableItemDelegate->itemDidClicked(this, pEvent, pTouch);
        }
    }
    return ret;
}

void MovableItem::TouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    if(!m_bTouchable)
    {
        _touchEndDoing(pTouch, pEvent);
        return;
    }
    if(m_uiSelectEffectId > 0)
    {
//        SimpleAudioEngine::sharedEngine()->stopEffect(m_uiSelectEffectId);
//        m_uiSelectEffectId = 0;
    }
    if(0 == m_uiMovingEffectId)
    {
        m_uiMovingEffectId = SimpleAudioEngine::getInstance()->playEffect(m_sMovingSoundEffect.c_str(), m_bMovingLoop);
    }
    //限制在屏幕范围内.先将坐标转换为世界坐标，看其是否还在限制范围内，如是，则设置新的坐标，否则，不做处理
    Point newPtWorld = convertToWorldSpace(Vec2(getContentSize().width * .5f, getContentSize().height * .5f)) + pTouch->getDelta();
//    CCLOG("moveRect:(%f,%f,%f,%f)",m_tMoveRect.origin.x, m_tMoveRect.origin.y, m_tMoveRect.size.width,m_tMoveRect.size.height);
//    CCLOG("touchPoint:(%f,%f), newPtWorld:(%f,%f)",pTouch->getLocation().x, pTouch->getLocation().y,newPtWorld.x,newPtWorld.y);
    if (m_pMovableItemDelegate) {
        m_pMovableItemDelegate->itemDidMoved(this, pEvent, pTouch);
    }else {
        if(m_tMoveRect.containsPoint(newPtWorld))
            setPosition(getPosition() + pTouch->getDelta());
        else
            CCLOG("out of movable range");
    }
}

Rect MovableItem::getmovableRect(){
    return m_tMoveRect;
}

void MovableItem::TouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    if(!m_bTouchable)
    {
        _touchEndDoing(pTouch, pEvent);
        return;
    }
    _touchEndDoing(pTouch, pEvent);
}

void MovableItem::TouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    _touchEndDoing(pTouch, pEvent);
}

void MovableItem::setMovableItemDelegate(MovableItemDelegate *apDelegate)
{
    m_pMovableItemDelegate = apDelegate;
}

void MovableItem::setMovingName(std::string asName)
{
    if(asName.compare(m_sMovingName) != 0)
    {
        m_sMovingName = asName;
        if(kMovableItemStateHandMoving == m_enState)
        {
            setDisplayFrame(CCSprite::create(m_sMovingName.c_str())->displayFrame());
        }
    }
}

void MovableItem::setStillName(std::string asName)
{
    if(asName.compare(m_sInitName) != 0)
    {
        m_sInitName = asName;
        if(kMovableItemStateHandMoving != m_enState)
        {
            setDisplayFrame(CCSprite::create(m_sInitName.c_str())->displayFrame());
        }
    }
}

void MovableItem::setSelectSoundEffect(std::string asName)
{
    m_sSelectSoundEffect = asName;
}

void MovableItem::setMovingSoundEffect(std::string asName)
{
    m_sMovingSoundEffect = asName;
}

void MovableItem::setStartLocation(const cocos2d::Point aPt)
{
    m_tStartLocation = aPt;
}

Point MovableItem::getStartLocation()
{
    return m_tStartLocation;
}

void MovableItem::setMoveRect(const cocos2d::Rect aRect)
{
    m_tMoveRect = aRect;
}

void MovableItem::setTouchEndHandleType(const int aType)
{
    m_iTouchEndType = aType;
}

void MovableItem::setTouchable(bool abValue) {
    m_bTouchable = abValue;
    _touchListener->setEnabled(false);

}



void MovableItem::backToStartLocation()
{
    CCLOG("MovableItem::backToStartLocation in. state:%d", m_enState);
    if(m_enState != kMovableItemStateBackMoving)
    {
        _changeToBacking();
        CCLOG("MovableItem::backToStartLocation start");
        m_pMove = CCMoveTo::create(.2, m_tStartLocation);
        CallFunc *pCall = CallFunc::create(std::bind(&MovableItem::_itemBackEnd, this));
        Action* pAction = NULL;
        if (m_tStartLocation.x < 0) {
            pAction = Sequence::create(pCall, NULL);
        }else {
            pAction = Sequence::create(m_pMove, pCall, NULL);
        }
        runAction(pAction);        
    }
}

void MovableItem::_itemBackEnd()
{
    _changeToInit();
    if(m_pMovableItemDelegate)
        m_pMovableItemDelegate->ItemDidBackToStartLocation(this, nullptr, nullptr);
}

void MovableItem::_inertiaFront()
{
}

void MovableItem::changeToMoving()
{
    if(m_enState != kMovableItemStateHandMoving)
    {
        m_enState = kMovableItemStateHandMoving;
        if(m_sMovingName.compare(m_sInitName) != 0)
        {
            Sprite* spr = Sprite::create(m_sMovingName.c_str());
            if(spr)
                setDisplayFrame(spr->displayFrame());
        }
    }
}

//这里假设外貌和初始是一样的
void MovableItem::_changeToBacking()
{
    m_enState = kMovableItemStateBackMoving;
}

void MovableItem::_changeToInit()
{
    if(m_enState == kMovableItemStateStill)
        return;
    m_enState = kMovableItemStateStill;
    Sprite* spr = Sprite::create(m_sInitName.c_str());
    if(spr)
        setDisplayFrame(spr->displayFrame());
}

void MovableItem::setMovingSoundEffectLoop(bool aLoop)
{
    m_bMovingLoop = aLoop;
}

void MovableItem::_onApplicationWillEnterForeground(cocos2d::Ref *apObj)
{
    if(kMovableItemTouchEndBackStart == m_iTouchEndType)
    {
        backToStartLocation();
    }
    if(m_pMovableItemDelegate)
        m_pMovableItemDelegate->itemDidBecomActive(this, nullptr, nullptr);
    _stopSoundEffect();
}

void MovableItem::_touchEndDoing(Touch *pTouch, Event *pEvent)
{
    switch (m_iTouchEndType) {
        case kMovableItemTouchEndStop:
            //do nothing
            if (m_pMovableItemDelegate) {
                m_pMovableItemDelegate->ItemDidBackToStartLocation(this, pEvent, pTouch);
            }
            break;
        case kMovableItemTouchEndBackStart:
            backToStartLocation();
            break;
        case kMovableItemTouchEndInertia:
            _inertiaFront();
            break;
        default:
            break;
    }
    //停止音效
    _stopSoundEffect();
}

void MovableItem::_stopSoundEffect()
{
    CCLOG("MovableItem::_stopSoundEffect");
    if(m_uiMovingEffectId > 0)
    {
        SimpleAudioEngine::getInstance()->stopEffect(m_uiMovingEffectId);
        m_uiMovingEffectId = 0;
    }
    if(m_uiSelectEffectId > 0)
    {
        SimpleAudioEngine::getInstance()->stopEffect(m_uiSelectEffectId);
        m_uiSelectEffectId = 0;
    }
}