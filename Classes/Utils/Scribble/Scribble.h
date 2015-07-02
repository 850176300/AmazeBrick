//
//  Scribble.h
//  GIRLS_Framework_part
//
//  Created by renhong on 9/12/13.
//
//

#ifndef __GIRLS_Framework_part__Scribble__
#define __GIRLS_Framework_part__Scribble__
#include <cocos2d.h>
#include <iostream>
#include <string>
using namespace cocos2d;
using namespace std;

extern CC_DLL const GLchar * ScribbleShader_frag;
#define kScribbleShaderName "kScribbleShaderName"

class Scribble {//Support cocos2d-x 3.2  and later
public:
    typedef enum{
        eBrush,
        eEaser
    }BrushType;
private:
    Sprite *_brush;
    BrushType _brushType;
    Sprite *_target;
protected:
    GLProgram *loadShader(const GLchar *pShaderString, string pShaderCacheKey);
    
public:
    static vector<Point> interpolate(Point pStartPosition, Point pEndPosition, float pDelta);
    
public:
    Scribble(Sprite *pBrush);
    ~Scribble();
    void antiAliasing(RenderTexture *pRenderTexture);
    void disAntiAliasing(RenderTexture *pRenderTexture);
    
    void paint(Sprite *pTarget, RenderTexture *pCanvas, Point pPosition);
    void paint(Sprite *pTarget, RenderTexture *pCanvas, Point pStartPosition, Point pEndPosition);
    void paint(Sprite *pTarget, RenderTexture *pCanvas, vector<Point> pWorldPositions);
    
    void setBrush(Texture2D *pBrushTexture);
    
    virtual void setBrushShader();
    virtual void setBrushType(BrushType pType = eBrush);
    void setBrushAlphaTestValue(float pAlphaValue);
    
    virtual void setTarget(Sprite *pTarget);
    void setTargetSolid(bool pIsSolid);
    void setTargetAlphaTestValue(float pAlphaValue);
    
    void removeTargetObserver(RenderTexture *pTarget);
    
protected:
    inline void setPaintPosition(Sprite *pTarget, Sprite *pBrush, Point pWorldPosition);
    inline void setTargetTexture(Sprite *pTexture);
    inline void setBrushTexture();
    
    inline Sprite *getBrush(){return _brush;}
    inline  virtual Sprite *getTarget(){return _target;}
};
inline void setShaderPrograms(Node *n, GLProgram *p);
#endif /* defined(__GIRLS_Framework_part__Scribble__) */
