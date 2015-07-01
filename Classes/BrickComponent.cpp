//
//  BrickComponent.cpp
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/14.
//
//

#include "BrickComponent.h"
#include "STVisibleRect.h"
#include "Config.h"
#include "JumpByDrop.h"
USING_NS_ST;

BrickComponent::BrickComponent(){
    setName("BrickComponent");
}

void BrickComponent::onEnter(){
    parent = (BrickSprite*)getOwner();
}

void BrickComponent::update(float t){
    if (parent == nullptr) {
        return;
    }
    if (parent->getStatues() == BrickSprite::kDie) {
        if (startMove == true) {
            _elapsed += t;
            this->step(MAX (0,                                  // needed for rewind. elapsed could be negative
                            MIN(4.0, _elapsed /
                                MAX(MoveDuration, FLT_EPSILON)   // division by 0
                                )
                            )
                       );
        }
        return;
    }
    
    if (parent->getStatues() == BrickSprite::kTouchL) {
        parent->setStatues(BrickSprite::kIdle);
        stopAction();
        touchLAction();
        startMove = true;
    }else if (parent->getStatues() == BrickSprite::kTouchR){
        parent->setStatues(BrickSprite::kIdle);
        stopAction();
        touchRAction();
        startMove = true;
    }
    if (startMove == true) {
        _elapsed += t;
        this->step(MAX (0,                                  // needed for rewind. elapsed could be negative
                          MIN(4.0, _elapsed /
                              MAX(_durantion, FLT_EPSILON)   // division by 0
                              )
                          )
                     );
    }

    
    
}

void BrickComponent::step(float t) {
    if (startMove == true)
    {
        float y = 0;
        if (changeSpeed == true) {
      
            y += _delta.y * t;
            y += speedY * 0.2;
            speedY -= 20*0.2f;

        }else {
            float frac = fmodf( t , 1.0f );
            y = _height * 4 *  frac * (1 - frac);
            y += _delta.y * t;
            _moveHeight += y;
            speedY = 0;
//            log("the y speed is %.2f", y);
        }

        float x = _delta.x * t;
        
        Vec2 currentPos = parent->getPosition();

        Vec2 diff = currentPos - _previousPos;
        
        _startPosition = diff + _startPosition;

        Vec2 newPos = _startPosition + Vec2(x,y);
        
        if (changeSpeed == true) {
            newPos.y = currentPos.y + y;
        }
        if (fabs(fabs(y) - fabs(_height)) < 0.1) {
//            log("the position is Heightest!!");
            changeSpeed = true;
        }
        
        if (newPos.x <= Director::getInstance()->getVisibleOrigin().x + parent->getContentSize().width / 2.0) {
            newPos.x = Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleOrigin().x + parent->getContentSize().width / 2.0;
        }
        if (newPos.x >= Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width - parent->getContentSize().width / 2.0) {
            newPos.x = Director::getInstance()->getVisibleOrigin().x + Director::getInstance()->getVisibleSize().width - parent->getContentSize().width / 2.0;
        }
        
        parent->setPosition(newPos);
        
        _previousPos = newPos;
        if (parent->boundingBox().getMinY() < Director::getInstance()->getVisibleOrigin().y) {
            parent->brickDie();
            
        }
    }
}

void BrickComponent::touchLAction(){
    float dt;
    float movedis;
    Vec2 startPos = parent->getPosition();
    float y = MoveY;
    float x = -1*MoveX;
    float deltay = STVisibleRect::getOriginalPoint().y + STVisibleRect::getGlvisibleSize().height*0.6 - startPos.y;
    float deltaX = STVisibleRect::getOriginalPoint().x - startPos.x;
    _durantion = MoveDuration;
    if (deltay < MoveY) {
        y = deltay;
        movedis = MoveY - y;
        _durantion = MoveDuration*(y / MoveY);
        x = x*(y / MoveY);
        dt = MoveDuration - _durantion;
        if (_durantion < SecondTime) {
            _durantion = SecondTime;
            dt = _durantion;
            x = x*0.5f;
        }
        if (fabs(x) < XChange) {
            x = -XChange;
        }
        int tempT = (int)(dt*10);
        __String* data = __String::createWithFormat("%.2f", tempT*1000+movedis);
        NotificationCenter::getInstance()->postNotification(kMoveNotifyEvent, data);
    }

    if (deltaX > -1 * MoveX) {
        x = deltaX;
    }
    _delta = Vec2(x, 0);
    _height = y;
    _moveHeight = 0;
    speedY = 0;
    _elapsed = 0;
    _previousPos = _startPosition = startPos;
    changeSpeed = false;
//    log("move x Position is %.2f", x);
    
}

void BrickComponent::touchRAction(){
    float dt;
    float movedis;
    Vec2 startPos = parent->getPosition();
    float y = MoveY;
    float x = MoveX;
    float deltay = STVisibleRect::getOriginalPoint().y + STVisibleRect::getGlvisibleSize().height*0.6 - startPos.y;
    float deltaX = STVisibleRect::getPointOfSceneRightBottom().x - startPos.x;
    _durantion = MoveDuration;
    if (deltay < MoveY) {
        y = deltay;
        movedis = MoveY - y;
        _durantion = MoveDuration*(y / MoveY);
        dt = MoveDuration - _durantion;
         x = x*(y / MoveY);
        if (_durantion < SecondTime) {
            _durantion = SecondTime;
            dt = _durantion;
            x=x*0.5f;
        }
        if (fabs(x) < XChange) {
            x = XChange;
        }
        int tempT = (int)(dt*10);
        __String* data = __String::createWithFormat("%.2f", tempT*1000+movedis);
        NotificationCenter::getInstance()->postNotification(kMoveNotifyEvent, data);
    }
    
    if (deltaX < MoveX) {
        x = deltaX;
    }
    _delta = Vec2(x, 0);
    _height = y;
    _moveHeight = 0;
    speedY = 0;
    _elapsed = 0;
    _previousPos = _startPosition = startPos;
    changeSpeed = false;
//    log("move x Position is %.2f", x);

}

void BrickComponent::stopAction(){
    if (parent != nullptr) {
        if (curAction != nullptr) {
            parent->stopAction(curAction);
            curAction = nullptr;
        }
    }
}



