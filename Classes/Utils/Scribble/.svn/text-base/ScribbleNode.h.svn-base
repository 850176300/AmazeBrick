//
//  ScribbleNode.h
//  ScribbleDemo_3_2
//
//  Created by renhong on 8/4/14.
//
//

#ifndef __ScribbleDemo_3_2__ScribbleNode__
#define __ScribbleDemo_3_2__ScribbleNode__

#include <iostream>
#include <string>
#include <cocos2d.h>
#include "Scribble.h"
using namespace std;
using namespace cocos2d;

typedef Sprite Brush;
typedef Sprite Target;
typedef RenderTexture Canvas;

class ScribbleNode : public Node {//Support cocos2d-x 3.2 and later
public:
    static ScribbleNode *create(int pCanvasWidth, int pCanvasHeight);
    inline static vector<Point> interpolate(Point pStartPosition, Point pEndPosition, float pDelta);
    inline static vector<Point> waterPositions(Point pFromPoint, float pMaxX, float pDelta, Vec2 pDirection);
    ScribbleNode();
    ~ScribbleNode();
    
    virtual bool init(int pCanvasWidth, int pCanvasHeight);
    
    bool setBrush(Scribble::BrushType pBrushType);
    bool setBrush(string pBrushFile, Scribble::BrushType pBrushType = Scribble::eBrush);
    bool useBrush();
    
    bool addTarget(string pTargetFile, Vec2 pPositionInCanvas);
    bool useTarget(string pTargetFile, Vec2 pPositionInCanvas);
    bool useTarget(string pTargetFile);
//    bool useTarget(Vec2 pPositionInCanvas);
    Scribble *getScribble();
    
    inline RenderTexture* getRender(){ return _canvas;};
    void paint(Point pPosition);
    void paint(Point pStartPosition, Point pEndPosition);
    void paint(vector<Point> pWorldPositions);
private:
    Brush *_brush;
    Map<string, Target *> _targets;
    Canvas *_canvas;
    
    Scribble *_scribble;
};

#endif /* defined(__ScribbleDemo_3_2__ScribbleNode__) */
