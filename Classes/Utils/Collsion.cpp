//
//  Collision.c
//  Burgers
//
//  Created by tanshoumei on 13-7-12.
//
//

#include <stdio.h>
/*
 *  SeparatingAxisTheorem.c
 *  CollisionDetect
 *
 *  Created by George on 12/24/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */


/*
 * 计算多边形polygon在坐标轴axis上得投影，得到最小值min和最大值max
 */
#include "Collsion.h"

static inline void projectPolygon( Vec2 &axis,  Polygon &polygon, float* min, float* max)
{
	float d = vectDot(axis, polygon.getVectAt(0));
	*min = d;
	*max = d;
    int vecNum=polygon.getVecNum();
	for (int i = 0; i < vecNum; i++)
	{
		d = vectDot(axis, polygon.getVectAt(i));
		if (d < *min)
		{
			*min = d;
		}
		else
		{
			if (d > *max)
			{
				*max = d;
			}
		}
	}
}

/*
 * 计算圆形circle在坐标轴axis上得投影，得到最小值min和最大值max
 */
static inline void projectCircle(Vec2 axis, Circle circle, float* min, float* max)
{
	float d = vectDot(axis, circle.o);
	float axisLength = vectLength(axis);
	*min = d - (circle.r * axisLength);
	*max = d + (circle.r * axisLength);
}

/*
 * 计算两个投影得距离
 */
static inline float intervalDistance(const float minA, const float maxA,const float minB,const float maxB)
{
	return (minA < minB) ? (minB - maxA) : (minA - maxB);
}

bool polygonCollision( Polygon a, Polygon b)
{
	Vec2 edge, axis;
	float minA = 0, maxA = 0, minB = 0, maxB = 0;
	int totalVectNum=a.getVecNum()+b.getVecNum();
	for (int i = 0, j=a.getVecNum()-1; i <totalVectNum; j=i, i++)
	{
		//通过顶点取得每个边
		if (i < a.getVecNum())
		{
			edge = vectSub(a.getVectAt(i), a.getVectAt(j));
		}
		else
		{
			int one=i-a.getVecNum(),two=(j-a.getVecNum()+b.getVecNum())%b.getVecNum();
			edge = vectSub(b.getVectAt(one), b.getVectAt(two));
		}
        
		axis = vectPerp(edge); //向量的垂直向量
        
		//以边的垂线为坐标轴进行投影，取得投影线段[min, max]
		projectPolygon(axis, a, &minA, &maxA);
		projectPolygon(axis, b, &minB, &maxB);
        
		//检查两个投影的距离，如果两投影没有重合部分，那么可以判定这两个多边形没有碰撞
		if (intervalDistance(minA, maxA, minB, maxB) > 0)
		{
			return false;
		}
	}
    
    
	return true;
}

bool polygonCircleCollision(Polygon p, Circle c)
{
	Vec2 edge, axis;
	float minP = 0, maxP = 0, minC = 0, maxC = 0;
    
	for(int i = 0, j=p.getVecNum()-1; i < p.getVecNum(); j=i, i++)
	{
		edge = vectSub(p.getVectAt(i), p.getVectAt(j));
		axis = vectPerp(edge); // perpendicular to edge
        
		//以边的垂线为坐标轴进行投影，取得投影线段[min, max]
		projectPolygon(axis, p, &minP, &maxP);
		projectCircle(axis, c, &minC, &maxC);
        
		//printf("%.2f\n", intervalDistance(minP, maxP, minC, maxC));
        
		//检查两个投影的距离，如果两投影没有重合部分，那么可以判定这两个图形没有碰撞
		if (intervalDistance(minP, maxP, minC, maxC) > 0)
		{
			return false;
		}
	}
    
	for(int i = 0; i < p.getVecNum(); i++)
	{
		axis = vectSub(c.o, p.getVectAt(i));
        
		projectPolygon(axis, p, &minP, &maxP);
		projectCircle(axis, c, &minC, &maxC);
        
		//printf("%.2f\n", intervalDistance(minP, maxP, minC, maxC));
        
		if (intervalDistance(minP, maxP, minC, maxC) > 0)
		{
			return false;
		}
	}
    
	return true;
}

bool circleCollision(Circle c1, Circle c2)
{
	float dis = (c1.o.x - c2.o.x) * (c1.o.x - c2.o.x) +  (c1.o.y - c2.o.y) * (c1.o.y - c2.o.y);
	if (dis > (c1.r + c2.r) * (c1.r + c2.r))
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*
 * straight rectangular直矩形，正矩形
 *
 */
bool rectangleCircleCollision(Rectangle rect, Circle circle)
{
	if (circle.o.x > rect.left - circle.r
		&& circle.o.x < rect.right + circle.r
		&& circle.o.y > rect.bottom - circle.r
		&& circle.o.y < rect.top + circle.r)
	{
		//左上角
		if(circle.o.x < rect.left && circle.o.y > rect.top)
		{
			float dis = disSquare(vectMake(rect.left, rect.top), circle.o);
			if( dis > circle.r * circle.r )
			{
				return false;
			}
		}
        
		if(circle.o.x > rect.right && circle.o.y > rect.top)
		{
			float dis = disSquare(vectMake(rect.right, rect.top), circle.o);
			if( dis > circle.r * circle.r )
			{
				return false;
			}
		}
        
		if(circle.o.x < rect.left && circle.o.y < rect.bottom)
		{
			float dis = disSquare(vectMake(rect.left, rect.bottom), circle.o);
			if( dis > circle.r * circle.r )
			{
				return false;
			}
		}
        
		if(circle.o.x > rect.right && circle.o.y < rect.bottom)
		{
			float dis = disSquare(vectMake(rect.right, rect.bottom), circle.o);
			if( dis > circle.r * circle.r )
			{
				return false;
			}
		}
        
		return true;
	}
    
	return false;
}

bool ptInPolygon (Vec2 pt, Polygon pologon)
{
    int nCross = 0;
    for (int i = 0; i < pologon.getVecNum(); i++)
    {
        Vec2 p1 = pologon.getVectAt(i);
        Vec2 p2 = pologon.getVectAt((i + 1) % pologon.getVecNum());
        // 求解 y=p.y 与 p1p2 的交点
        if ( p1.y == p2.y ) // p1p2 与 y=p0.y平行
            continue;
        if ( pt.y < min(p1.y, p2.y) ) // 交点在p1p2延长线上
            continue;
        if ( pt.y >= max(p1.y, p2.y) ) // 交点在p1p2延长线上
            continue;
        // 求交点的 X 坐标 --------------------------------------------------------------
        double x = (double)(pt.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
        if ( x > pt.x )
            nCross++; // 只统计单边交点
    }
    // 单边交点为偶数，点在多边形之外 ---
    return (nCross % 2 == 1);
}
