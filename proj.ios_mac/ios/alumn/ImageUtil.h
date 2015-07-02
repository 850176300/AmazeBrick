//
//  ImageUtil.h
//  Doctor
//
//  Created by tanshoumei on 13-8-16.
//
//

#ifndef __Doctor__ImageUtil__
#define __Doctor__ImageUtil__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class ImageUtil {
public:
    //将CCImage转换为UIImage对象，实现了cocos2d-x与ios图片的接轨，可用于分享，照片保存等
    static UIImage* CCImageToUIImage(CCImage* apImg);
};


#endif /* defined(__Doctor__ImageUtil__) */
