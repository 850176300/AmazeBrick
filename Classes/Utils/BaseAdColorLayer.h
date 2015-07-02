//
//  BaseAdColorLayer.h
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 15-1-28.
//
//

#ifndef __DND2052_Baby_Play_Town__BaseAdColorLayer__
#define __DND2052_Baby_Play_Town__BaseAdColorLayer__

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

class BaseAdColorLayer : public LayerColor{
public:
    BaseAdColorLayer();
    ~BaseAdColorLayer();
    virtual void onEnter();
    virtual void onExit();
    virtual void onPauseGame(Ref* _ref);
    virtual void onResumeGame(Ref* _ref);
};

#endif /* defined(__DND2052_Baby_Play_Town__BaseAdColorLayer__) */
