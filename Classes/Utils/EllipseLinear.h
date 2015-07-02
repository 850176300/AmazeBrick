//
//  EllipseLinearAction.h
//  ActionTest-x
//
//  Created by renhong on 7/15/14.
//
//

#ifndef __ActionTest_x__EllipseLinearAction__
#define __ActionTest_x__EllipseLinearAction__
#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
/**
 *  沿着椭圆轨迹绕椭圆中心做匀速（线速度）运动
 */
class EllipseLinear : public ActionInterval {
public:
    
    /**
     *  a: 椭圆长轴 b: 椭圆短轴 center: 椭圆中心点
     */
    static EllipseLinear *create(float dt, float a, float b, Vec2 center);
    virtual EllipseLinear* clone() const override;
    virtual EllipseLinear* reverse(void) const  override;
    virtual void startWithTarget(Node *target) override;
    virtual void update(float time) override;
protected:
    EllipseLinear(float a, float b, Vec2 center);
    virtual ~EllipseLinear(){};
private:
    float _a;
    float _b;
    Vec2 _center;
};

#endif /* defined(__ActionTest_x__EllipseLinearAction__) */
