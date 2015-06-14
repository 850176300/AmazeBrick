//
//  BrickComponent.h
//  com.kekeapp.amazebrick
//
//  Created by liuwei on 15/6/14.
//
//

#ifndef __com_kekeapp_amazebrick__BrickComponent__
#define __com_kekeapp_amazebrick__BrickComponent__

#include <iostream>
#include "cocos2d.h"
#include "BrickSprite.h"
USING_NS_CC;
class BrickComponent : public Component{

public:
    BrickComponent();
    
protected:
    virtual void update(float);
    void stopAction();
    virtual void onEnter();
    void touchLAction();
    void touchRAction();
private:
    Action* curAction = nullptr;
    BrickSprite* parent;
    
};

#endif /* defined(__com_kekeapp_amazebrick__BrickComponent__) */
