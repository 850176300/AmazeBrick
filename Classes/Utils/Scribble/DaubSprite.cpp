//
//  DaubSprite.cpp

//
//  Created by chenxi1 on 13-10-23.
//
//

#include "DaubSprite.h"


DaubSprite::DaubSprite():width(0),height(0),resHeight(0),offsetX(0),offsetY(0),_total(1), sprite(NULL){
    
}

DaubSprite::~DaubSprite(){
    sprite->release();
}

DaubSprite* DaubSprite::create( Scribble *scribble, const string& filename){
    DaubSprite *pRet = new DaubSprite();
    Sprite* temp = Sprite::create(filename);
    Size size = temp->getContentSize();
    log("sprite->getContentSize(%f,%f)",size.width, size.height);
    if(pRet && pRet->initWithWidthAndHeight(size.width, size.height, Texture2D::PixelFormat::RGBA8888, 0))
    {
        pRet->scribble=scribble;
        pRet->resWidth =size.width;
        pRet->resHeight =size.height;
        Size size = pRet->getContentSize();
        if (pRet->resWidth<size.width) {
            pRet->offsetX =pRet->resWidth-size.width;
        }
        if(pRet->resHeight<size.height){
            pRet->offsetY =size.height-pRet->resHeight;
        }
        pRet->isDaub=false;
//        pRet->setContentSize(renderTextureSize(w, h));
        scribble->removeTargetObserver(pRet);
        pRet->changeTarget(filename);
        pRet->show();
        pRet->clear(0, 0, 0, 0);
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
DaubSprite* DaubSprite::create(Size size, Scribble *scribble,const string& filename){
    DaubSprite *pRet = new DaubSprite();
//    Size size = sprite->getContentSize();
    if(pRet && pRet->initWithWidthAndHeight(size.width, size.height, Texture2D::PixelFormat::RGBA8888, 0))
    {
        pRet->scribble=scribble;
        pRet->resWidth =size.width;
        pRet->resHeight =size.height;
        Size size = pRet->getContentSize();
        if (pRet->resWidth<size.width) {
            pRet->offsetX =pRet->resWidth-size.width;
        }
        if(pRet->resHeight<size.height){
            pRet->offsetY =size.height-pRet->resHeight;
        }
        pRet->isDaub=false;
        //        pRet->setContentSize(renderTextureSize(w, h));
        scribble->removeTargetObserver(pRet);
        pRet->changeTarget(filename);
        pRet->show();
        
        pRet->clear(0, 0, 0, 0);
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

 bool DaubSprite::initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat eFormat, GLuint uDepthStencilFormat){
    const float lFitSize = 370;//min 353
     eraserFinished = false;
     paintFinished = false;
    if (w < lFitSize) {
        w = lFitSize;
        
    }
  this->width = w;
    
    if (h < lFitSize) {
        h = lFitSize;
    }
   this->height = h;
     
    return RenderTexture::initWithWidthAndHeight(w, h,eFormat,uDepthStencilFormat);
   
    
}

void DaubSprite::onEnter(){
    RenderTexture::onEnter();
    
//    Size size=getContentSize();
//    soundRect=CCRect(blankArea_height+getPositionX()-size.width/2, getPositionY()-size.height/2, size.width, size.height);
}

void DaubSprite::onExit(){
    RenderTexture::onExit();
}

void DaubSprite::paint(Point lTouchPoint,Point lpreTouchPoint){
    scribble->paint(sprite, this, lTouchPoint,lpreTouchPoint);
}
void DaubSprite::changeTarget(const string& filename,bool mClean){
    if (sprite != NULL) {
        sprite->release();
    }
    sprite = Sprite::create(filename);
    sprite->retain();
    Size size =  this->getContentSize();
    sprite->setPosition( Vec2(width/2+offsetX,height/2+offsetY)  );
    scribble->setTarget(sprite);
    Image* tempImage = new Image();
    tempImage->initWithImageFile(filename);
    _total =  calcute(tempImage);
    if(mClean){
        RenderTexture::clear(0,0,0,0);
    }
}
void DaubSprite::show(){
    if(this->sprite==NULL){
        return;
    }
    this->begin();
    this->sprite->visit();
    this->end();
}
long DaubSprite::calcute(Image *pImage){
    long lCounter = 0;
    for (long i = 0; i < pImage->getHeight(); ++i) {
        for (long j = 0; j < pImage->getWidth(); ++j) {
            unsigned char *lData = pImage->getData();
            long lPixcelIndex = i * pImage->getWidth() + j;
            unsigned char lRed = lData[lPixcelIndex * 4];
            unsigned char lGreen = lData[lPixcelIndex * 4 + 1];
            unsigned char lBlue = lData[lPixcelIndex * 4 + 2];
            unsigned char lAlpha = lData[lPixcelIndex * 4 + 3];
            if (lAlpha > 10) {
                if (lRed > 0 || lGreen > 0 || lBlue > 0) {
                    ++lCounter;
                }
            }
        }
    }
//    CCLog("texture img count %ld",lCounter);
//    CCLog("texture total count %ld",_total);
    CC_SAFE_RELEASE(pImage);
    return lCounter;
}
float DaubSprite::paintPercent(){
    return this->calcute(this->newImage()) / (this->_total * 1.0);
}
float DaubSprite::easePercent(){
    return 1-this->calcute(this->newImage()) / (this->_total * 1.0);
}
void DaubSprite::cleanupEverything(){
    RenderTexture::clear(0,0,0,0);
}