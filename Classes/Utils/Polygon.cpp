//
//  Polygon.cpp
//  Burgers
//
//  Created by tanshoumei on 13-7-12.
//
//

#include "Polygon.h"


Polygon::Polygon()
{
}

Polygon::Polygon(vector<CCPoint> vecs)
{
	vectors=vecs;
}

void Polygon::addVec(CCPoint vec)
{
	vectors.push_back(vec);
}

CCPoint Polygon::getVectAt(int i)
{
	return vectors.at(i);
}

int Polygon::getVecNum()
{
	return vectors.size();
}

void Polygon::draw()
{
    if( vectors.size() > 1)
    {
        CCPoint pt = vectors[vectors.size() -1];
        for (int i = 0; i < vectors.size(); ++i) {
            ccDrawLine(pt, vectors[i]);
            pt = vectors[i];
        }
    }
}

