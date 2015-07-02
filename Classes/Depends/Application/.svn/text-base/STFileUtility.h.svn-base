#ifndef _STFILEUTILITY_H_
#define _STFILEUTILITY_H_
#include <iostream>

#include "cocos2d.h"

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#endif
using namespace std;

USING_NS_CC;
class STFileUtility {
public:
    //在设备的存储空间里创建一个目录
	static bool createDirectory(const char *path);
	//获取文件所在的目录
    static std::string getFileDirectory(std::string fileName);
	//判断文件是否存在
    static bool isFileExist(std::string filePath);
	//创建文件
    static bool createFile(std::string filePath);
    //获取设备的存储路径
    static std::string getStoragePath();
	//删除一个目录，包含里面文件
    static bool removeDir(string path);
	//
    static void get_file_path(const char *path, const char *file_name,  char *file_path);
	//
    static bool is_dir(const char *path);
	//
    static bool is_file(const char *path);
};


#endif