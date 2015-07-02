//
//  AlumnAdapter.cpp
//  Doctor2
//
//  Created by tanshoumei on 13-9-18.
//
//

#include "AlumnAdapter.h"
#include "ImageUtil.h"
#import "AlumnImpIos.h"
void AlumnAdapter::saveToAlumn(cocos2d::Image *apCCImg)
{
    [[AlumnImpIos shared] saveToAlumn:ImageUtil::CCImageToUIImage(apCCImg)];
}