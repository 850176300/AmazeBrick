/*
 *  SeparatingAxisTheorem.h
 *  CollisionDetect
 *
 *  Created by tanshoumei on 13-7-12.
 *
 */
#pragma once

#include <stdio.h>
#include <math.h>
#include "Polygon.h"

//圆形
typedef struct Circle
{
	CCPoint o; // 圆心坐标
	float r; //半径
} Circle;

//矩形
typedef struct Rectangle
{
	float left, right, top, bottom;
} Rectangle;

//矩形构造器
static inline Rectangle rectMake(float left, float right, float top, float bottom)
{
	Rectangle r = {left, right, top, bottom};
	return r;
}

//两点距离的平方
static inline float disSquare(CCPoint p1, CCPoint p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/*
 * 圆形与圆形碰撞检测
 */
static bool circleCollision(Circle c1, Circle c2);


/*
 * 检测两个多边形是否碰撞，碰撞返回true，不碰撞返回false
 * 必须是两个凸多边形，凹多边形必须拆分成多个凸多边形或三角形
 */
bool polygonCollision( Polygon p1, Polygon p2);

/*
 * 凸多边形与圆形碰撞
 */
bool polygonCircleCollision(Polygon &p, Circle &c);

/*
 * 正直矩形与圆形碰撞
 */
bool rectangleCircleCollision(Rectangle rect, Circle circle);

//点与多边形
bool ptInPolygon (CCPoint pt, Polygon pologon);
