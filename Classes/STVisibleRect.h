#ifndef _STVISIBLE_H_
#define _STVISIBLE_H_

#include "cocos2d.h"
#include "STMacro.h"

NS_ST_BEGIN
USING_NS_CC;

class STVisibleRect {
public:
	// initialization for STVisibleRect
	static void setupVisibleRect(Size frameSize, Size designSize);

	// initialization offset for STVisibleRect
	static void initRetainOffset(int left, int top, int right, int bottom);
    
    static int getRetainOffsetTop();

	// real design size(bigger than the designed size of game)
	static Size& getRealDesignSize();
	
	// the designed size of game
	static Size& getDesignSize();
    
    //the center of design frame.
    static Point getDesignCeneter();
	
	// get frame size(can consider as screen size)
	static Size& getFrameSize();

	// the margin of top and left according to frame size
	static Point& getTopLeftOffset();

	// the offset between game designed size and real design size
	static Point getDesignOffset();

	// the ratio = RealDesignSize / DesignSize
	static float getRealDesignScale();
    
    //将给定的坐标转化成屏幕适配后的坐标
    static Point getPosition(float x, float y, bool bTop = false, bool bBottom = false, bool bLeft = false);
    //the center coordindate of the screen
    static Point getCenterOfScene();
    static Point getPointOfSceneRightBottom();
    static Point getPointOfSceneRightUp();
    static Point getPointOfSceneLeftUp();

	// adjust Node's position(attention:top & bottom feature)
    //居右还未测
	static void setPosition(Node* node, float x, float y, bool bTop = false, bool bBottom = false, bool bLeft = false, bool bRight = false);

	// adjust Node's position
	static void setPositionWithRetainOffset(Node* node, float x, float y, bool bTop = false, bool bBottom = false);
    
    //get cocos2dx visible size
    static Size getGlvisibleSize();
    
    //get movable Rect
    static Rect getMovableRect();
    
    //get oringinal Point
    static Point getOriginalPoint();
    //judge rect Contain other one
    static bool JudgeContain(Rect dstrect1, Rect resrect2);
    
    //caculate point by anchor point
    static Point conformByAnchorPoint(Node *pNode ,Point p1, Point anchorP1, Point p2 = Vec2(0.5f, 0.5f));
    
    
};

NS_ST_END
#endif