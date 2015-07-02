//
//  AlertViewDelegate.h
//  BBQParty
//
//  Created by liuwei on 14-8-27.
//
//

#ifndef BBQParty_AlertViewDelegate_h
#define BBQParty_AlertViewDelegate_h
#include <iostream>
class AlertViewDelegate{
public:
    virtual void onAlertViewClickatIndex(int viewTag,int index) = 0;
};

#endif
