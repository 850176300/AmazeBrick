//
//  EllipseAngularAction.cpp
//  ActionTest-x
//
//  Created by renhong on 7/15/14.
//
//

#include "EllipseAngular.h"


EllipseAngular *EllipseAngular::create(float dt, float a, float b, Vec2 center){
    EllipseAngular *pAction = new EllipseAngular(a, b, center);
    pAction->initWithDuration(dt);
    pAction->autorelease();
    
    return pAction;
}

EllipseAngular::EllipseAngular(float a, float b, Vec2 center){
    _a = a;
    _b = b;
    _center = center;
}

EllipseAngular* EllipseAngular::clone() const{
    auto a = new EllipseAngular(_a, _b, _center);
    a->initWithDuration(_duration);
    a->autorelease();
    return a;
}

void EllipseAngular::startWithTarget(cocos2d::Node *target) {
    ActionInterval::startWithTarget(target);
}

EllipseAngular* EllipseAngular::reverse() const{
    return EllipseAngular::create(_duration, _a, _b, _center);
}

void EllipseAngular::update(float t){
    float x = 0, y = 0;
    float angle = M_PI * 2 * t;//椭圆中心与当前运动点连线角度
    float k = tanf(angle);//椭圆中心与当前运动点连线斜率
    //联立直线标准方程（y = kx）与椭圆标准方程（x^2 / a^2 + y^2 / b^2 = 1）求当前坐标点
    if (t <= 0.25) {//第一象限
        x = (_a * _b) / sqrt(pow(k, 2) * pow(_a, 2) + pow(_b, 2));
        y = k * x;
    }
    else if(t <= 0.5){//第二象限
        x = -(_a * _b) / sqrt(pow(k, 2) * pow(_a, 2) + pow(_b, 2));
        y = k * x;
    }
    else if(t <= 0.75){//第三象限
        x = -(_a * _b) / sqrt(pow(k, 2) * pow(_a, 2) + pow(_b, 2));
        y = k * x;
    }
    else{//第四象限
        x = (_a * _b) / sqrt(pow(k, 2) * pow(_a, 2) + pow(_b, 2));
        y = k * x;
    }
    Point position = _center + Vec2(x, y);
    this->getTarget()->setPosition(position);
}