//
//  Box2dPhysicSprite.cpp
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 15-1-22.
//
//

#include "Box2dPhysicSprite.h"
#include "Config.h"
Box2dPhysicSprite::Box2dPhysicSprite()
: _ignoreBodyRotation(false)
, _pB2Body(nullptr)
, fPTMRatio(0.0f)
{}

Box2dPhysicSprite::~Box2dPhysicSprite(){
    if (hadAddNotify) {
        NotificationCenter::getInstance()->removeObserver(this, kMoveNotifyEvent);
    }
}

Box2dPhysicSprite* Box2dPhysicSprite::create()
{
    Box2dPhysicSprite* pRet = new Box2dPhysicSprite();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

Box2dPhysicSprite* Box2dPhysicSprite::createWithTexture(Texture2D *pTexture)
{
    Box2dPhysicSprite* pRet = new Box2dPhysicSprite();
    if (pRet && pRet->initWithTexture(pTexture))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

Box2dPhysicSprite* Box2dPhysicSprite::createWithTexture(Texture2D *pTexture, const Rect& rect)
{
    Box2dPhysicSprite* pRet = new Box2dPhysicSprite();
    if (pRet && pRet->initWithTexture(pTexture, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

Box2dPhysicSprite* Box2dPhysicSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
    Box2dPhysicSprite* pRet = new Box2dPhysicSprite();
    if (pRet && pRet->initWithSpriteFrame(pSpriteFrame))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

Box2dPhysicSprite* Box2dPhysicSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    Box2dPhysicSprite* pRet = new Box2dPhysicSprite();
    if (pRet && pRet->initWithSpriteFrameName(pszSpriteFrameName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

Box2dPhysicSprite* Box2dPhysicSprite::create(const string &pszFileName)
{
    Box2dPhysicSprite* pRet = new Box2dPhysicSprite();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

Box2dPhysicSprite* Box2dPhysicSprite::create(const string &pszFileName, const Rect& rect)
{
    Box2dPhysicSprite* pRet = new Box2dPhysicSprite();
    if (pRet && pRet->initWithFile(pszFileName, rect))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

// this method will only get called if the sprite is batched.
// return YES if the physic's values (angles, position ) changed.
// If you return NO, then getNodeToParentTransform won't be called.
bool Box2dPhysicSprite::isDirty() const
{
    return true;
}

bool Box2dPhysicSprite::isIgnoreBodyRotation() const
{
    return _ignoreBodyRotation;
}

void Box2dPhysicSprite::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
    _ignoreBodyRotation = bIgnoreBodyRotation;
}

// Override the setters and getters to always reflect the body's properties.
const Vec2& Box2dPhysicSprite::getPosition() const
{
    return getPosFromPhysics();
}

void Box2dPhysicSprite::getPosition(float* x, float* y) const
{
    if (x == nullptr || y == nullptr) {
        return;
    }
    const Vec2& pos = getPosFromPhysics();
    *x = pos.x;
    *y = pos.y;
}

float Box2dPhysicSprite::getPositionX() const
{
    return getPosFromPhysics().x;
}

float Box2dPhysicSprite::getPositionY() const
{
    return getPosFromPhysics().y;
}

//
// Chipmunk only
//






b2Body* Box2dPhysicSprite::getB2Body() const
{
    
    return _pB2Body;
}

void Box2dPhysicSprite::setB2Body(b2Body *pBody)
{
    _pB2Body = pBody;
}

float Box2dPhysicSprite::getPTMRatio() const
{
    return fPTMRatio;
}

void Box2dPhysicSprite::setPTMRatio(float fRatio)
{
    fPTMRatio = fRatio;
}

//
// Common to Box2d and Chipmunk
//

const Vec2& Box2dPhysicSprite::getPosFromPhysics() const
{
    static Vec2 s_physicPosion;
    
    
    
    b2Vec2 pos = _pB2Body->GetPosition();
    float x = pos.x * fPTMRatio;
    float y = pos.y * fPTMRatio;
    s_physicPosion = Vec2(x,y);
    return s_physicPosion;
}

void Box2dPhysicSprite::setPosition(const Vec2 &pos)
{
    
    
    float angle = _pB2Body->GetAngle();
    _pB2Body->SetTransform(b2Vec2(pos.x / fPTMRatio, pos.y / fPTMRatio), angle);
    
}

float Box2dPhysicSprite::getRotation() const
{
    
    
    return (_ignoreBodyRotation ? Sprite::getRotation() :
            CC_RADIANS_TO_DEGREES(_pB2Body->GetAngle()));
    
}

void Box2dPhysicSprite::setRotation(float fRotation)
{
    if (_ignoreBodyRotation)
    {
        Sprite::setRotation(fRotation);
    }
    
    
    
    
    else
    {
        b2Vec2 p = _pB2Body->GetPosition();
        float radians = CC_DEGREES_TO_RADIANS(fRotation);
        _pB2Body->SetTransform(p, radians);
        Sprite::setRotation(_pB2Body->GetTransform().q.GetAngle());
    }
    
    
}

void Box2dPhysicSprite::syncPhysicsTransform() const
{
    // Although scale is not used by physics engines, it is calculated just in case
    // the sprite is animated (scaled up/down) using actions.
    // For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
    
    
    
    
    
    b2Vec2 pos  = _pB2Body->GetPosition();
    
    float x = pos.x * fPTMRatio;
    float y = pos.y * fPTMRatio;
    
    if (_ignoreAnchorPointForPosition)
    {
        x += _anchorPointInPoints.x;
        y += _anchorPointInPoints.y;
    }
    
    // Make matrix
    float radians = getRotation();//_pB2Body->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);
    
    if (!_anchorPointInPoints.equals(Vec2::ZERO))
    {
        x += ((c * -_anchorPointInPoints.x * _scaleX) + (-s * -_anchorPointInPoints.y * _scaleY));
        y += ((s * -_anchorPointInPoints.x * _scaleX) + (c * -_anchorPointInPoints.y * _scaleY));
    }
    
    // Rot, Translate Matrix
    
    float mat[] = {  (float)c * _scaleX, (float)s * _scaleX, 0,  0,
        (float)-s * _scaleY, (float)c * _scaleY,  0,  0,
        0,  0,  1,  0,
        x,	y,  0,  1};
    
    _transform.set(mat);
    
}

// returns the transform matrix according the Chipmunk Body values
const Mat4& Box2dPhysicSprite::getNodeToParentTransform() const
{
    syncPhysicsTransform();
    
    return _transform;
}

void Box2dPhysicSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if (isDirty())
    {
        syncPhysicsTransform();
    }
    
    Sprite::draw(renderer, _transform, flags);
}

void Box2dPhysicSprite::addMoveEventNotify(){
    if (hadAddNotify == true){
        return;
    }
    hadAddNotify = true;
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Box2dPhysicSprite::onRecieveEvent), kMoveNotifyEvent, nullptr);
}

void Box2dPhysicSprite::onRecieveEvent(cocos2d::Ref *pRef) {
    __String* data = dynamic_cast<__String*>(pRef);
    float infor = atof(data->getCString());
    float distance = infor - (((int)infor) / 1000)*1000;
    float dt = (((int)infor) / 1000) * 0.1;

    this->runAction(Sequence::create(EaseSineInOut::create(MoveBy::create(dt, Vec2(0, -distance))), CallFunc::create(std::bind(&Box2dPhysicSprite::checkNeedRemove, this)),NULL));
}

void Box2dPhysicSprite::checkNeedRemove(){
    if (getBoundingBox().getMaxY() < Director::getInstance()->getVisibleOrigin().y) {
        _pB2Body->GetWorld()->DestroyBody(_pB2Body);
        removeFromParent();
    }
}

