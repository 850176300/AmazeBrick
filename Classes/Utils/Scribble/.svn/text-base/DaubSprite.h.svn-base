//
//  DaubSprite.h

//
//  Created by chenxi1 on 13-10-23.
//
//

#ifndef ____DaubSprite__
#define ____DaubSprite__

#include "cocos2d.h"
#include "Scribble.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DaubSprite: public RenderTexture {
    
    Scribble *scribble;
    Sprite *sprite;
    bool isDaub;
    
    long _total;
    float _alphaTestValue;
protected:
    long calcute(Image *pImage);
    
public:
    DaubSprite();
    virtual ~DaubSprite();

    //标志类变量
    bool eraserFinished;
    bool paintFinished;
    static DaubSprite* create( Scribble *scribble,const string& filename);
    static DaubSprite* create(Size size, Scribble *scribble,const string& filename);
    bool initWithWidthAndHeight(int w, int h, Texture2D::PixelFormat eFormat, GLuint uDepthStencilFormat);

    virtual void onEnter();
    virtual void onExit();
    virtual void paint(Point lTouchPoint,Point lpreTouchPoint);
    
    void setEnableDaub(bool isDaub);
    virtual void changeTarget(const string& filename,bool mClean = true);
    void show();
    int width,height,resWidth,resHeight,offsetX,offsetY;
    
    float paintPercent();
    float easePercent();
    
    void cleanupEverything();
};

#endif 
