//
//  CocosHelper.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-10-16.
//
//

#include "CocosHelper.h"

Node* CocosHelper::openCcbNode(const char * pCCBFileName, const char * pNodeName, NodeLoader * pNodeLoader)
{
    NodeLoaderLibrary * NodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();
    if(pNodeName != NULL && pNodeLoader != NULL) {
        NodeLoaderLibrary->registerNodeLoader(pNodeName, pNodeLoader);
    }
    
    CCBReader * ccbReader = new CCBReader(NodeLoaderLibrary);
    ccbReader->autorelease();
    Node * node = ccbReader->readNodeGraphFromFile(pCCBFileName);
    return node;
}

Sprite* CocosHelper::getSpriteFromAnimate( const Animate* apAni, const int aFrameInx /*= 0*/)
{
    Sprite* pRet = NULL;
    if( apAni )
    {
        Vector<AnimationFrame*> pFrames = apAni->getAnimation()->getFrames();
        if(pFrames.size() > aFrameInx )
        {
            SpriteFrame* pFrame = pFrames.at(0)->getSpriteFrame();
            pRet = Sprite::createWithSpriteFrame(pFrame);
        }
    }
    return pRet;
}

Sprite* CocosHelper::spriteCreateWithNoCache(const char* pName)
{
    Image* pimg = new Image;
    pimg->initWithImageFile(pName);
    Texture2D* pTex = new Texture2D;
    pTex->initWithImage(pimg);
    Sprite* pSpr = Sprite::createWithTexture(pTex);
    pimg->release();
    pTex->release();
    return pSpr;
}

//void CocosHelper::AddNode(Node* apNode, Node* apParent, const Point& aPt, const int aZorder, const int aTag)
//{
//    if(apNode && apParent)
//    {
//        apParent->addChild(apNode, aZorder, aTag);
//        apNode->setPosition(aPt);
//    }
//}

void CocosHelper::AddNodeAutoAdapte(Node* apNode, Node* apParent, const Point& aPt, const int aZorder, const int aTag)
{
    if(apNode && apParent)
    {
        apParent->addChild(apNode, aZorder, aTag);
        STVisibleRect::setPosition(apNode, aPt.x, aPt.y);
    }
}

//根据sprite file name添加精灵到指定位置
Sprite* CocosHelper::AddSprite( const char* apFileName, Node* apParent, const int aZorder, const int aTag)
{
    Sprite *spr = Sprite::create(apFileName);
    apParent->addChild(spr, aZorder, aTag);
    return spr;
}

//根据sprite file name添加精灵到指定位置.（不会将texture缓存）
Sprite* CocosHelper::AddSpriteNoCache( const char* apFileName, Node* apParent, const int aZorder, const int aTag)
{
    Sprite *spr = spriteCreateWithNoCache(apFileName);
    apParent->addChild(spr, aZorder, aTag);
    return spr;
}

//根据sprite frame name添加精灵到指定位置
Sprite* CocosHelper::AddSpriteByFrame( const char* apFileName, Node* apParent, const int aZorder, const int aTag)
{
    SpriteFrame* pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(apFileName);
    if(pFrame)
    {
        Sprite* spr = Sprite::createWithSpriteFrame(pFrame);
        apParent->addChild(spr, aZorder, aTag);
        return spr;
    }
    return NULL;
}

//将字符串转换成Rect，可设置数字间分隔符，默认为","
Rect CocosHelper::stringToRect(std::string aStr, const char* sp /*= ","*/)
{
    int nums[4] = {0};
    const char *tokenPtr = strtok((char*)aStr.c_str(), sp);
    int inx = 0;
    while (NULL != tokenPtr && inx < 4) {
        nums[inx++] = atoi(tokenPtr);
        tokenPtr = strtok(NULL, sp);
    }
    return Rect(nums[0], nums[1], nums[2], nums[3]);
}

//将字符串转换成Point，可设置数字间分隔符，默认为","
Point CocosHelper::stringToPoint(std::string aStr, const char* sp /*= ","*/)
{
    int nums[2] = {0};
    const char *tokenPtr = strtok((char*)aStr.c_str(), sp);
    int inx = 0;
    while (NULL != tokenPtr && inx < 2) {
        nums[inx++] = atoi(tokenPtr);
        tokenPtr = strtok(NULL, sp);
    }
    return Vec2(nums[0], nums[1]);
}

//判断点是否在node之内，可用于touch判断
bool CocosHelper::isPointInNode(Node* apNode, const Point& aPtWorld)
{
    if(apNode)
    {
        Rect rect;
        rect.origin = apNode->convertToWorldSpace(Vec2(0, 0));
        rect.size = apNode->getContentSize();
        if(rect.containsPoint(aPtWorld))
            return true;
    }
    return false;
}

Rect CocosHelper::getNodeRectInWorld(Node* apNode)
{
    Rect rect;
    rect.origin = apNode->convertToWorldSpace(Vec2(0, 0));
    rect.size = apNode->getContentSize();
    return rect;
}

//node content rect center
Point CocosHelper::getNodeCenterLocal(Node* apNode)
{
    Point pt;
    if(apNode){
        pt.x = apNode->getContentSize().width * .5;
        pt.y = apNode->getContentSize().height * .5;
    }
    return pt;
}

//根据一张图，生成一个按钮item,其选中效果为变暗，和UIButton差不多
MenuItemSprite* CocosHelper::menuItemSprite(const char* aName)
{
    Sprite* normalSpr = Sprite::create(aName);
    Sprite* selectSpr = Sprite::create(aName);
    selectSpr->setColor(Color3B::GRAY);
    MenuItemSprite* item = MenuItemSprite::create(normalSpr, selectSpr);
    return item;
}

//当前系统时间(毫秒)
long CocosHelper::milliSecondNow()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}


ControlButton* CocosHelper::getButton(const string& normalName, const string& selectedName) {
    Sprite* sprite = Sprite::create(normalName);

    Scale9Sprite* btnNormal = Scale9Sprite::create(normalName);
    
    /* 点击状态下的按钮图片 */
    Scale9Sprite* btnDown = Scale9Sprite::create(selectedName);
    Scale9Sprite* btnDisable = Scale9Sprite::create(selectedName);
    /* 按钮的大小会根据标题自动调整 */
    ControlButton* controlBtn = ControlButton::create(btnNormal);
    
    /* 设置按钮按下时的图片 */
    controlBtn->setBackgroundSpriteForState(btnDown, Control::State::HIGH_LIGHTED);
    controlBtn->setBackgroundSpriteForState(btnDisable, cocos2d::extension::Control::State::DISABLED);
    //    controlBtn->setZoomOnTouchDown(false);
    controlBtn->setPreferredSize(sprite->getContentSize());
    
    return controlBtn;
}


ControlButton* CocosHelper::getButtonWithLabel(const char *normalName, const char *selectedName, cocos2d::Label *theLabel) {
    Sprite* sprite = Sprite::create(normalName);
    
    Scale9Sprite* btnNormal = Scale9Sprite::create(normalName);
    
    /* 点击状态下的按钮图片 */
    Scale9Sprite* btnDown = Scale9Sprite::create(selectedName);
    
    /* 按钮的大小会根据标题自动调整 */
    ControlButton* controlBtn = ControlButton::create(theLabel, btnNormal);
    
    /* 设置按钮按下时的图片 */
    controlBtn->setBackgroundSpriteForState(btnDown, Control::State::HIGH_LIGHTED);
    //    controlBtn->setZoomOnTouchDown(false);
    controlBtn->setPreferredSize(sprite->getContentSize());
    
    return controlBtn;
}