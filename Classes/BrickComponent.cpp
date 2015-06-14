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

void BrickComponent::update(float){
    if (parent == nullptr) {
        return;
    }
    if (parent->getStatues() == BrickSprite::kDie) {
        return;
    }
    
    if (parent->getStatues() == BrickSprite::kTouchL) {
        parent->setStatues(BrickSprite::kIdle);
        stopAction();
        touchLAction();
    }else if (parent->getStatues() == BrickSprite::kTouchR){
        parent->setStatues(BrickSprite::kIdle);
        stopAction();
        touchRAction();
    }
    
    
}

void BrickComponent::touchLAction(){
    Vec2 startPos = parent->getPosition();
    float y = MoveY;
    float x = -1*MoveX;
    float deltay = STVisibleRect::getOriginalPoint().y + STVisibleRect::getGlvisibleSize().height*0.6 - startPos.y;
    float deltaX = STVisibleRect::getOriginalPoint().x - startPos.x;
    if (deltay < MoveY) {
        y = deltay;
    }

    if (deltaX > -1 * MoveX) {
        x = deltaX;
    }
    
    JumpByDrop* move1 = JumpByDrop::create(MoveDuration, Vec2(x, 0), y, 1);
    EaseSineIn* move2 = EaseSineIn::create(MoveBy::create(DropDuration, Vec2(0, -1*STVisibleRect::getGlvisibleSize().height*0.75)));
    curAction = Sequence::create(move1, move2, NULL);
    parent->runAction(curAction);
    
}

void BrickComponent::touchRAction(){
    Vec2 startPos = parent->getPosition();
    float y = MoveY;
    float x = MoveX;
    float deltay = STVisibleRect::getOriginalPoint().y + STVisibleRect::getGlvisibleSize().height*0.6 - startPos.y;
    float deltaX = STVisibleRect::getPointOfSceneRightBottom().x - startPos.x;
    if (deltay < MoveY) {
        y = deltay;
    }
    
    if (deltaX < MoveX) {
        x = deltaX;
    }
    
    JumpByDrop* move1 = JumpByDrop::create(MoveDuration, Vec2(x, 0), y, 1);
    EaseSineIn* move2 = EaseSineIn::create(MoveBy::create(DropDuration, Vec2(0, -1*STVisibleRect::getGlvisibleSize().height*0.75)));
    curAction = Sequence::create(move1, move2, NULL);
    parent->runAction(curAction);
}

void BrickComponent::stopAction(){
    if (parent != nullptr) {
        if (curAction != nullptr) {
            parent->stopAction(curAction);
            curAction = nullptr;
        }
    }
}



