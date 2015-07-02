//
//  ScribbleNode.cpp
//  ScribbleDemo_3_2
//
//  Created by renhong on 8/4/14.
//
//

#include "ScribbleNode.h"

ScribbleNode *ScribbleNode::create(int pCanvasWidth, int pCanvasHeight){
    ScribbleNode *ret = new ScribbleNode();
    if(ret && ret->init(pCanvasWidth, pCanvasHeight))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

vector<Point> ScribbleNode::interpolate(Point pStartPosition, Point pEndPosition, float pDelta){
    return Scribble::interpolate(pStartPosition, pEndPosition, pDelta);
}

vector<Point> ScribbleNode::waterPositions(Point pFromPoint, float pMaxX, float pDelta, Vec2 pDirection){
    float lVy = pDirection.y;
    float lVx = pDirection.x;
    const float lAccelerationRate = 0.01;
    int lXVar = pMaxX;
    //lXVar = lXVar / 2 + arc4random() % lXVar / 2;
    //int lDelta = _scribble->getBrush()->getContentSize().width / 4.0 * _scribble->getBrush()->getScaleX();
    int a = 0;
    float lX = pFromPoint.x;
    float lY = pFromPoint.y;
    vector<Point> lPositions;
    for (int i = 0; i < lXVar; i += pDelta) {
        Point lPosition;
        a += pDelta;
        lPosition.x = lX + lVx * i;
        lPosition.y = lY + lVy * i - lAccelerationRate * a * a;
        lPositions.push_back(lPosition);
        
        //CCLOG("touchmove2 %f %f %d", lX, lY, a);
    }
    return lPositions;
}

ScribbleNode::ScribbleNode() : _brush(nullptr), _canvas(nullptr){
    _scribble = new Scribble(CCSprite::create());
    _scribble->setBrushShader();
    _scribble->setBrushType(Scribble::eBrush);
    _scribble->setTargetSolid(true);
    //_scribble->setTargetAlphaTestValue(0.1f);
}

ScribbleNode::~ScribbleNode(){
    delete _scribble;
    
    if (nullptr != _brush) {
        _brush->release();
    }
    if (nullptr != _canvas) {
        _canvas->release();
    }
}

bool ScribbleNode::init(int pCanvasWidth, int pCanvasHeight){
    if (!Node::init()) {
        return false;
    }
    
    _canvas = Canvas::create(pCanvasWidth, pCanvasHeight);
    _canvas->retain();
    //_canvas->clear(1, 0, 0, 0.1);
    this->addChild(_canvas);
    return true;
}

bool ScribbleNode::setBrush(string pBrushFile, Scribble::BrushType pBrushType/* = Scribble::eBrush*/){
    CCLOG("Warning: Dot use this function frequently");
    if (0 == pBrushFile.length()) {
        return false;
    }
    
    Texture2D *lBrushTexture = Director::getInstance()->getTextureCache()->addImage(pBrushFile);
    CCASSERT(lBrushTexture != nullptr, "brush is null");
    _scribble->setBrush(lBrushTexture);
    _scribble->setBrushType(pBrushType);
    return true;
}

bool ScribbleNode::setBrush(Scribble::BrushType pBrushType){
    _scribble->setBrushType(pBrushType);
    return true;
}

bool ScribbleNode::useBrush(){
    return true;
}

bool ScribbleNode::addTarget(string pTargetFile, Vec2 pPositionInCanvas){
    Target *lTarget = Target::create(pTargetFile);
    lTarget->setPosition(pPositionInCanvas);
    _targets.insert(pTargetFile, lTarget);
    return true;
}

bool ScribbleNode::useTarget(string pTargetFile, Vec2 pPositionInCanvas){
    Target *lTarget = _targets.find(pTargetFile)->second;
    lTarget->setPosition(pPositionInCanvas);
    _scribble->setTarget(lTarget);
    return true;
}

bool ScribbleNode::useTarget(string pTargetFile){
    Target *lTarget = _targets.find(pTargetFile)->second;
    _scribble->setTarget(lTarget);
    return true;
}

//bool ScribbleNode::useTarget(Vec2 pPositionInCanvas){
//    Target *lTarget = Sprite::createWithSpriteFrame(_canvas->getSprite()->getSpriteFrame());
//    lTarget->setPosition(pPositionInCanvas);
//    lTarget->setFlippedY(true);
//    lTarget->getTexture()->
//    _scribble->setTarget(lTarget);
//    return true;
//}

Scribble *ScribbleNode::getScribble(){
    return _scribble;
}

void ScribbleNode::paint(Point pPosition){
    _scribble->paint(nullptr, _canvas, pPosition);
}

void ScribbleNode::paint(Point pStartPosition, Point pEndPosition){
    _scribble->paint(nullptr, _canvas, pStartPosition, pEndPosition);
}

void ScribbleNode::paint(vector<Point> pWorldPositions){
    _scribble->paint(nullptr, _canvas, pWorldPositions);
}