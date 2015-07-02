//
//  Polygon.h
//  Burgers
//
//  Created by tanshoumei on 13-7-12.
//
//

#ifndef __Burgers__Polygon__
#define __Burgers__Polygon__

#include <iostream>
#include <math.h>
#import <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

//向量
static Vec2 vectMake(int x, int y)
{
	return Vec2(x, y);
}

//向量点乘
static float vectDot(Vec2 v1, Vec2 v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

//向量减法
static Vec2 vectSub(Vec2 v1, Vec2 v2)
{
	return vectMake(v1.x - v2.x, v1.y - v2.y);
}

//向量加法
static inline Vec2 vectAdd(Vec2 v1, Vec2 v2)
{
	return vectMake(v1.x + v2.x, v1.y + v2.y);
}

//向量长度
static inline float vectLength(Vec2 v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}
//向量的垂直向量
static inline Vec2 vectPerp(Vec2 v)
{
	return vectMake(-(v.y), v.x);
}

//多边形定义
class Polygon{
public:
	Polygon();
	Polygon(vector<Vec2> vecs);
    //返回多边形点的数目
	int getVecNum();
    //获取指定位置的顶点坐标
	Vec2 getVectAt(int i);
    //于尾部添加一个顶点
	void addVec(Vec2 vec);
    //打印当前所有的顶点坐标
    void print()
    {
        for(vector<Vec2>::iterator it=vectors.begin(); it!=vectors.end();++it)
        {
//            CCLOG("%d %d",(*it).x,(*it).y);
        }
    }
    void draw();
private:
	vector<Vec2> vectors;
};


#endif /* defined(__Burgers__Polygon__) */