//
//  CocosHelper.h
//  Burgers
//
//  Created by tanshoumei on 13-6-26.
//
//

#ifndef Burgers_CocosHelper_h
#define Burgers_CocosHelper_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "STVisibleRect.h"
#include "editor-support/cocosbuilder/Cocosbuilder.h"
#include "ui/CocosGUI.h"
using namespace std;

USING_NS_CC;
USING_NS_ST;
using namespace cocos2d::extension;
using namespace cocosbuilder;
using namespace ui;

#define CH_RETURN_IF(cond) if(cond) return;

class CocosHelper {
public:
    /*
     根据ccbi文件，生成Node.
     pCCBFileName: ccbi文件名
     pNodeName: 此Node注册的名字，
     **/
    static Node* openCcbNode(const char * pCCBFileName, const char * pNodeName, NodeLoader * pNodeLoader);
    /*
     从CCAniamte中获取Sprite
     aFrameInx: 帧索引，返回相应的帧生成Sprite。
     **/
    static Sprite* getSpriteFromAnimate( const Animate* apAni, const int aFrameInx = 0);
    
    //实例化Sprite对象，不添加纹理缓存
    static Sprite* spriteCreateWithNoCache(const char* pName);
    
    //添加node到指定坐标, 提供的坐标会根据屏幕适配变化。
    static void AddNodeAutoAdapte(Node* apNode, Node* apParent, const Point& aPt, const int aZorder, const int aTag);
    
    //根据sprite file name添加精灵到指定位置
    static Sprite* AddSprite( const char* apFileName, Node* apParent, const int aZorder, const int aTag);
    
    //根据sprite file name添加精灵到指定位置.（不会将texture缓存）
    static Sprite* AddSpriteNoCache( const char* apFileName, Node* apParent, const int aZorder, const int aTag);

    //根据sprite frame name添加精灵到指定位置
    static Sprite* AddSpriteByFrame( const char* apFileName, Node* apParent, const int aZorder, const int aTag);
    
    //将字符串转换成Rect，可设置数字间分隔符，默认为","
    static Rect stringToRect(std::string aStr, const char* sp = ",");
    
    //将字符串转换成Point，可设置数字间分隔符，默认为","
    static Point stringToPoint(std::string aStr, const char* sp = ",");
    
    //判断点是否在node之内，可用于touch判断
    static bool isPointInNode(Node* apNode, const Point& aPtWorld);
    
    static Rect getNodeRectInWorld(Node* apNode);
    
    //node content rect center
    static Point getNodeCenterLocal(Node* apNode);
    
    //根据一张图，生成一个按钮item,其选中效果为变暗，和UIButton差不多
    static MenuItemSprite* menuItemSprite(const char* aName);
    
    //设置节点的触摸优秀级
//    static void setTouchPriority(Touch* apTouchNode, const int aValue);

    //当前系统时间(毫秒)
    static long milliSecondNow();
    
    static ControlButton* getButton(const string& normalName, const string& selectedName);
    
    static ControlButton* getButtonWithLabel(const char *normalName, const char *selectedName, Label* theLabel);
};

#endif
