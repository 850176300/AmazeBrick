//
//  CCImageColorSpace.h
//  GIRLS_Framework_part
//
//  Created by renhong on 9/17/13.
//
//

#ifndef __GIRLS_Framework_part__CCImageColorSpace__
#define __GIRLS_Framework_part__CCImageColorSpace__

#include <iostream>
/*
 refrence from
 http://blog.csdn.net/ldz15838245189/article/details/9365499
 */

#include "cocos2d.h"

USING_NS_CC;

class CCImageColorSpace  {
public:
   static CCImage* imageWithHSB(CCImage *pRGBImage, int pHueValue, int pSaturationValue, int pBrightnessValue);
};
#endif /* defined(__GIRLS_Framework_part__CCImageColorSpace__) */
