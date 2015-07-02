//
//  ImageUtil.cpp
//  Doctor
//
//  Created by tanshoumei on 13-8-16.
//
//

#include "ImageUtil.h"
UIImage* ImageUtil::CCImageToUIImage(CCImage* apImg)
{    
    int bitsPerComponent = 8;
    int bitsPerPixel = 32;
    int bytesPerRow    = (bitsPerPixel/8) * apImg->getWidth();
    int myDataLength = bytesPerRow * apImg->getHeight();    
    unsigned char *pixels    = apImg->getData();    
    // make data provider with data.
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGDataProviderRef provider        = CGDataProviderCreateWithData(NULL, pixels, myDataLength, NULL);
    CGColorSpaceRef colorSpaceRef    = CGColorSpaceCreateDeviceRGB();
    CGImageRef iref                    = CGImageCreate(apImg->getWidth(), apImg->getHeight(),
                                                       bitsPerComponent, bitsPerPixel, bytesPerRow,
                                                       colorSpaceRef, bitmapInfo, provider,
                                                       NULL, false,
                                                       kCGRenderingIntentDefault);
    UIImage* image                    = [[[UIImage alloc] initWithCGImage:iref] autorelease];
    CGImageRelease(iref);    
    return image;
}
