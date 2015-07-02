#ifndef __UTIL_H__
#define __UTIL_H__
#include <iostream>
#include "cocos2d.h"
using namespace std;

USING_NS_CC;

class Util{
    
public:
	//check the file exists
	static bool isExistFile(const char *pszFileName);
    //获取一个UI sprite，此方法只会到resource的UI目录下寻找资源
	static Sprite* getUISprite(const char* fileName);
    static Texture2D* getUITexture(const char* fileName);
     //获取一个content sprite，此方法只会到resource的Content目录下寻找资源
	static Sprite* getContentSprite(const char* fileName);
	static Texture2D* getContentTexture(const char* fileName);
	static string getContentFilePath(const char* fileName);
    static string getUIFilePath(const char* fileName);
	//get the device language type
	static const char* getLanguageType();
    
	static bool loadUITexture(const char* language,const char* file);
	static bool loadUITextureWithResolution(const char* language,const char* file);
    //获取当前系统时间
    static long getCurrentTime();

	//替换字符串中的内容
	static std::string replaceStr(std::string &str, const char *string_to_replace, const char *new_string);
   static int  randomNum(int start,int end);
};

#endif