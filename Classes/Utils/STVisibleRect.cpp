#include "STVisibleRect.h"
#include "STSystemFunction.h"
USING_NS_CC;
USING_NS_ST;

static Size s_FrameSize;
static Size s_DesignSize;
static Size s_RealDesignSize;
static Point s_TopLeftOffset;
static Point s_DesignOffset;
static float s_RealDesignScale = 1.0f;

static int s_RetainOffsetLeft = 0;
static int s_RetainOffsetTop = 0;
static int s_RetainOffsetRight = 0;
static int s_RetainOffsetBottom = 0;

void STVisibleRect::setupVisibleRect(Size frameSize, Size designSize)
{
	s_DesignSize = designSize;
	s_FrameSize = frameSize;

	float scaleX = (float) frameSize.width / s_DesignSize.width;
	float scaleY = (float) frameSize.height / s_DesignSize.height;

	// MAX(scaleX, scaleY);
	float scale = 0.0f;
	if (scaleX > scaleY)
	{
		scale = scaleX / scaleY;
		s_TopLeftOffset = Vec2(s_DesignSize.width * (scale - 1.0f) / 2.0f, 0);
	}
	else
	{
		scale = scaleY / scaleX;
		s_TopLeftOffset = Vec2(0, s_DesignSize.height * (scale - 1.0f) / 2.0f);
	}

	s_RealDesignScale = scale;
	s_RealDesignSize = Size(s_DesignSize.width * scale, s_DesignSize.height * scale);

	s_DesignOffset = Vec2((s_RealDesignSize.width - s_DesignSize.width) / 2.0f,
		(s_RealDesignSize.height - s_DesignSize.height) / 2.0f);
}

void STVisibleRect::initRetainOffset(int left, int top, int right, int bottom)
{
	s_RetainOffsetLeft = left * s_RealDesignSize.width / s_FrameSize.width;
	s_RetainOffsetTop = top * s_RealDesignSize.height / s_FrameSize.height;
	s_RetainOffsetRight = right * s_RealDesignSize.width / s_FrameSize.width;
	s_RetainOffsetBottom = bottom * s_RealDesignSize.height / s_FrameSize.height;
    NotificationCenter::getInstance()->postNotification("NotifyRetainOffset");
}

int STVisibleRect::getRetainOffsetTop()
{
    return s_RetainOffsetTop;
}
Point STVisibleRect::getPosition(float x, float y, bool bTop, bool bBottom, bool bLeft) {
//    CCLog("the design offset x:%.2f, y:%.2f", s_DesignOffset.x, s_DesignOffset.y);
    float posX = x + s_DesignOffset.x;
	float posY = y + s_DesignOffset.y;
    
	if(bTop)
		posY += s_DesignOffset.y;
	else if(bBottom)
		posY -= s_DesignOffset.y;
    
    if(bLeft)
        posX -= s_DesignOffset.x;

    return Vec2(posX, posY);
}
void STVisibleRect::setPosition(Node* node, float x, float y, bool bTop, bool bBottom, bool bLeft, bool bRight)
{
	float posX = x + s_DesignOffset.x;
	float posY = y + s_DesignOffset.y;

	if(bTop)
		posY += s_DesignOffset.y;
	else if(bBottom)
		posY -= s_DesignOffset.y;
    
    if(bLeft)
        posX -= s_DesignOffset.x;
    if (bRight) {
        posX += s_DesignOffset.x;
    }
    
	node->setPosition(Vec2(posX, posY));
}

void STVisibleRect::setPositionWithRetainOffset(Node* node, float x, float y, bool bTop, bool bBottom)
{
	float posX = x + s_DesignOffset.x;
	float posY = y + s_DesignOffset.y;

	if(bTop)
	{
		posY += (s_TopLeftOffset.y - s_RetainOffsetTop);
	}

	if(bBottom)
	{
		posY -= (s_TopLeftOffset.y - s_RetainOffsetBottom);
	}

	node->setPosition(Vec2(posX, posY));
}

Size& STVisibleRect::getRealDesignSize()
{
	return s_RealDesignSize;
}

Size& STVisibleRect::getDesignSize()
{
	return s_DesignSize;
}

Point STVisibleRect::getDesignCeneter()
{
    return Vec2(s_DesignSize.width * .5f, s_DesignSize.height * .5f);
}

Size& STVisibleRect::getFrameSize()
{
	return s_FrameSize;
}

float STVisibleRect::getRealDesignScale()
{
	return s_RealDesignScale;
}

Point& STVisibleRect::getTopLeftOffset()
{
	return s_TopLeftOffset;
}

Point STVisibleRect::getDesignOffset()
{
	return s_DesignOffset;
}

Point STVisibleRect::getCenterOfScene()
{
//    float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
//    float scaleY = Director::getInstance()->getOpenGLView()->getScaleY();
//    return Vec2(getDesignOffset().x + s_FrameSize.width * .5f / scaleX, getDesignOffset().y + s_FrameSize.height* .5f / scaleY);
    Point oringnalP = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Vec2(oringnalP.x + visibleSize.width/2.0, oringnalP.y+visibleSize.height/2.0);
}

Point STVisibleRect::getPointOfSceneRightBottom()
{
    return getOriginalPoint()+Vec2(getGlvisibleSize().width, 0);
}

Point STVisibleRect::getPointOfSceneRightUp(){
    return getOriginalPoint()+Vec2(getGlvisibleSize().width, getGlvisibleSize().height);
}

Point STVisibleRect::getPointOfSceneLeftUp()
{
//    float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
//    float scaleY = Director::getInstance()->getOpenGLView()->getScaleY();
//    return Vec2(getDesignOffset().x + s_FrameSize.width / scaleX, getDesignOffset().y + s_FrameSize.height / scaleY);
    return getOriginalPoint()+ Vec2(0, getGlvisibleSize().height);
}

Size STVisibleRect::getGlvisibleSize(){
    return Director::getInstance()->getVisibleSize();
}

Rect STVisibleRect::getMovableRect(){
    float bannerSize = 0;
    STSystemFunction st;
    bool istablet = st.isTabletAvailable();
    if (istablet == true) {
        bannerSize = 50;
    }else {
        bannerSize = 90;
    }
    return Rect(Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleOrigin().y+bannerSize, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height-bannerSize);
//    }
    
}


bool STVisibleRect::JudgeContain(cocos2d::Rect rect1/*大矩阵*/, cocos2d::Rect rect2/*小矩阵*/) {
    return !((rect1.origin.x >= rect2.origin.x) || (rect1.origin.y >= rect2.origin.y) ||
                      ( rect1.origin.x + rect1.size.width <= rect2.origin.x + rect2.size.width) ||
                    ( rect1.origin.y + rect1.size.height <= rect2.origin.y + rect2.size.height));
}

Point STVisibleRect::getOriginalPoint(){
    return Director::getInstance()->getVisibleOrigin();
}

//p2 表示转换之前的锚点，p1 应该对应的锚点
Point STVisibleRect::conformByAnchorPoint(cocos2d::Node *pNode,cocos2d::Point p1, cocos2d::Point anchorP1,Point p2/* = Vec2(0.5f, 0.5f)*/) {
    Point delta = Vec2((anchorP1.x - p2.x)*pNode->getContentSize().width, (anchorP1.y-p2.y)*pNode->getContentSize().height);
    return p1+delta;
}




