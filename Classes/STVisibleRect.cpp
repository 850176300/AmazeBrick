#include "STVisibleRect.h"
//#include "KKAds.h"
#include "GameController.h"
USING_NS_CC;
USING_NS_ST;

static Size s_FrameSize;
static Size s_DesignSize;
static Size s_RealDesignSize;
static Vec2 s_TopLeftOffset;
static Vec2 s_DesignOffset;
static float s_RealDesignScale = 1.0f;

static float s_RealContentFactor;

static int s_RetainOffsetLeft = 0;
static int s_RetainOffsetTop = 0;
static int s_RetainOffsetRight = 0;
static int s_RetainOffsetBottom = 0;

void STVisibleRect::setupVisibleRect(Size frameSize, Size designSize)
{
    s_DesignSize = designSize;
    s_FrameSize = frameSize;
    
    float scaleX = frameSize.width / designSize.width;
    float scaleY = frameSize.height / designSize.height;
    float scale = MIN(scaleX, scaleY);
    
    s_RealDesignSize = Size(frameSize.width / scale, frameSize.height / scale);
    s_RealContentFactor = MAX(scaleX, scaleY);
    
    s_DesignOffset = Point( abs(s_RealDesignSize.width - designSize.width)/2.0 ,
                             abs(s_RealDesignSize.height - designSize.height)/2.0 );
    s_RealDesignScale = s_RealContentFactor;
    
}

void STVisibleRect::initRetainOffset(int left, int top, int right, int bottom)
{
	s_RetainOffsetLeft = left * s_RealDesignSize.width / s_FrameSize.width;
	s_RetainOffsetTop = top * s_RealDesignSize.height / s_FrameSize.height;
	s_RetainOffsetRight = right * s_RealDesignSize.width / s_FrameSize.width;
	s_RetainOffsetBottom = bottom * s_RealDesignSize.height / s_FrameSize.height;
    __NotificationCenter::getInstance()->postNotification("NotifyRetainOffset");
}

int STVisibleRect::getRetainOffsetTop()
{
    return s_RetainOffsetTop;
}
Vec2 STVisibleRect::getPosition(float x, float y, bool bTop, bool bBottom, bool bLeft) {
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

Vec2 STVisibleRect::getDesignCeneter()
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

Vec2& STVisibleRect::getTopLeftOffset()
{
	return s_TopLeftOffset;
}

Vec2 STVisibleRect::getDesignOffset()
{
	return s_DesignOffset;
}

Vec2 STVisibleRect::getCenterOfScene()
{
//    float scaleX = Director::getInstance()->getOpenGLView()->getScaleX();
//    float scaleY = Director::getInstance()->getOpenGLView()->getScaleY();
//    return Vec2(getDesignOffset().x + s_FrameSize.width * .5f / scaleX, getDesignOffset().y + s_FrameSize.height* .5f / scaleY);
    Vec2 oringnalP = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    return Vec2(oringnalP.x + visibleSize.width/2.0, oringnalP.y+visibleSize.height/2.0);
}

Vec2 STVisibleRect::getPointOfSceneRightBottom()
{
    Vec2 p = Vec2(0,0);
    p.add(getOriginalPoint());
    p.add(Vec2(getGlvisibleSize().width, 0));
    return p;
}

Vec2 STVisibleRect::getPointOfSceneRightUp(){
    Vec2 p = Vec2(0,0);
    p.add(getOriginalPoint());
    p.add(Vec2(getGlvisibleSize().width, getGlvisibleSize().height));
    return p;
}

Vec2 STVisibleRect::getPointOfSceneLeftUp()
{
    Vec2 p = Vec2(0,0);
    p.add(getOriginalPoint());
    p.add(Vec2(0, getGlvisibleSize().height));
    return p;
}

Size STVisibleRect::getGlvisibleSize(){
    return Director::getInstance()->getVisibleSize();
}

Rect STVisibleRect::getMovableRect(){
    float bannerSize = GameController::getInstance()->getBannerHeight();
    
        return Rect(Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleOrigin().y+bannerSize, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height-bannerSize);
//    }
    
}
//judge dstrect1 is in resrect2

bool STVisibleRect::JudgeContain(Rect dstrect1, Rect resrect2) {
    return !((dstrect1.origin.x >= resrect2.origin.x) || (dstrect1.origin.y >= resrect2.origin.y) ||
                      ( dstrect1.origin.x + dstrect1.size.width <= resrect2.origin.x + resrect2.size.width) ||
                    ( dstrect1.origin.y + dstrect1.size.height <= resrect2.origin.y + resrect2.size.height));
}

Vec2 STVisibleRect::getOriginalPoint(){
    return Director::getInstance()->getVisibleOrigin();
}

//p2 表示转换之前的锚点，p1 应该对应的锚点
Vec2 STVisibleRect::conformByAnchorPoint(Node *pNode,cocos2d::Vec2 p1, cocos2d::Vec2 anchorP1,Vec2 p2/* = Vec2(0.5f, 0.5f)*/) {
    Vec2 delta = Vec2((anchorP1.x - p2.x)*pNode->getContentSize().width, (anchorP1.y-p2.y)*pNode->getContentSize().height);
    p1.add(delta);
    return p1;
}




