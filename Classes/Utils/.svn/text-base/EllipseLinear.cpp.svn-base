//
//  EllipseLinearAction.cpp
//  ActionTest-x
//
//  Created by renhong on 7/15/14.
//
//

#include "EllipseLinear.h"

EllipseLinear *EllipseLinear::create(float dt, float a, float b, Vec2 center){
    EllipseLinear *pAction = new EllipseLinear(a, b, center);
    pAction->initWithDuration(dt);
    pAction->autorelease();
    
    return pAction;
}



EllipseLinear::EllipseLinear(float a, float b, Vec2 center){
    _a = a;
    _b = b;
    _center = center;
}

EllipseLinear* EllipseLinear::clone() const{
    auto a = new EllipseLinear(_a, _b, _center);
    a->initWithDuration(_duration);
    a->autorelease();
    return a;
}

void EllipseLinear::startWithTarget(cocos2d::Node *target) {
    ActionInterval::startWithTarget(target);
}

EllipseLinear* EllipseLinear::reverse() const{
    return EllipseLinear::create(_duration, _a, _b, _center);
}

void EllipseLinear::update(float t){
    float x = 0, y = 0;
    float angle = M_PI * 2 * t;//椭圆中心与当前运动点连线角度
    float k = tanf(angle);//椭圆中心与当前运动点连线斜率
    //联立直线标准方程（y = kx）与椭圆标轨迹定义求当前坐标点
    if (t <= 0.25) {//第一象限
        x = _a / sqrt(1 + k * k);
        y = k * _b / sqrt(1 + k * k);
        this->getTarget()->setRotation(60.0f-t*240);
    }
    else if(t <= 0.5){//第二象限
        x = -_a / sqrt(1 + k * k);
        y = -k * _b / sqrt(1 + k * k);
        this->getTarget()->setRotation(60.0f-t*240);
//        CCLog("get the rotation is %.2f", this->getTarget()->getRotation());
    }
    else if(t <= 0.75){//第三象限
        x = -_a / sqrt(1 + k * k);
        y = -k * _b / sqrt(1 + k * k);
        this->getTarget()->setRotation(-120-(t-0.5)*240);
    }
    else{//第四象限
        x = _a / sqrt(1 + k * k);
        y = k * _b / sqrt(1 + k * k);
        this->getTarget()->setRotation(-120-(t-0.5)*240);
    }
    Vec2 position = _center + Vec2(x, y);
//    CCLog("the ttt is %.2f", t);
    
    this->getTarget()->setPosition(position);
}