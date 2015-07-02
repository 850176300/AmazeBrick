//
//  MathUtil.h
//  Burgers
//
//  Created by hujie on 13-6-21.
//
//

#ifndef Burgers_MathUtil_h
#define Burgers_MathUtil_h

#include  <vector>
using namespace std;

namespace MathUtils {
    //限定值范围[min, max]
    template<class T>
    static void clamp( T& value, const T min, const T max )
    {
        if ( value < min ) { value = min; }
        if ( value > max ) { value = max; }
    }
    //线性插值
    static float lerp( const float a, const float b, float t )
    {
        clamp( t, 0.0f, 1.0f );
        return ( a + t * ( b - a ) );
    }
    //范围随机数[min, max]
    static int randomBetween( const int min, const int max )
    {
        int rd = rand();
        return min + (rd % (max - min + 1) );
    }
    
    //从指定范围[min, max]，随机生成n个不重复的数
    static void random(const int count, const int min, const int max, vector<int>& aOut)
    {
        aOut.clear();
        for (int i = min; i <= max; ++i) {
            aOut.push_back(i);
        }
        int earseCount = aOut.size() - count;
        for (int i = 0; i < earseCount; ++i) {
            if(aOut.size() == 0)
                break;
            int rd = randomBetween(0, aOut.size() - 1);
            aOut.erase(aOut.begin() + rd);
        }
    }

    
    /*
     sum: add random num sum at the value.
     count: count of random numbers. be sure that count is no more than sum.
     aOut: generated numbers.
     **/
    static void randomForSum( const int sum, const unsigned int count, vector<int>& aOut )
    {
        aOut.clear();
        unsigned int ix = 1;
        unsigned int left = sum;// - count;
        while ( ix < count ) {
            int rd = randomBetween( 0, left );
            int value = rd; //+1 means every value has init value 1.
            aOut.push_back(value);
            left -= rd;
            ++ix;
        }
        aOut.push_back( left );
    }
    /*
     detect if param value is located in [left right];
     **/
    static bool isBetween( const int value, const int left, const int right)
    {
        return left<=value && value<=right;
    }
    
    static int randomBool()
    {
        return randomBetween(0, 1);
    }
}



#endif
