#include "STFileUtility.h"
#include "STSystemFunction.h"



bool STFileUtility::createDirectory(const char *path)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	mode_t processMask = umask(0);
	int ret = mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
	{
		return false;
	}

	return true;
#else
	BOOL ret = CreateDirectoryA(path, NULL);
	if (!ret && ERROR_ALREADY_EXISTS != GetLastError())
	{
		return false;
	}
	return true;
#endif
}

std::string STFileUtility::getFileDirectory(std::string fileName)
{
	if(fileName.size() < 1) return fileName;

	int index = fileName.find_last_of("/");
	if(index > 1 && index <= (int)fileName.size())
	{
		return fileName.substr(0, index);
	}
	else
	{
		return fileName;
	}
}

bool STFileUtility::isFileExist(std::string filePath)
{
	if(filePath.size() < 1) return false;

	FILE *fp = fopen(filePath.c_str(),"r");
	if(fp)
	{
		fclose(fp);
		return true;
	}
	return false;
}

bool STFileUtility::createFile(std::string filePath)
{
	if(filePath.size() < 1) return false;
	FILE* fp = fopen(filePath.c_str(), "w");
	if(fp)
	{
		fclose(fp);
		return true;
	}
	return false;
}

std::string STFileUtility::getStoragePath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return CCFileUtils::sharedFileUtils()->getWritablePath();
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	STSystemFunction* sys = new STSystemFunction();
	std::string path = sys->getSdCardPath();
	delete sys;
	return path;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return CCFileUtils::sharedFileUtils()->getWritablePath();
#endif
}

bool STFileUtility::removeDir( string path )
{
	#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	DIR *dir;
	dirent *dir_info;
	char file_path[PATH_MAX];
	if(is_file(path.c_str()))
	{
		remove(path.c_str());
		return true;
	}
	if(is_dir(path.c_str()))
	{
		if((dir = opendir(path.c_str())) == NULL)
			return false;
		while((dir_info = readdir(dir)) != NULL)
		{
			get_file_path(path.c_str(), dir_info->d_name, file_path);
			if(strcmp(dir_info->d_name, ".") == 0 || strcmp(dir_info->d_name, "..") == 0)
				continue;
			if(is_dir(file_path))
			{
				removeDir(file_path);
				rmdir(file_path);
			}
			else if(is_file(file_path))
				remove(file_path);

		}
	}
	#else
		
	
	#endif
	return true;
}

void  STFileUtility::get_file_path(const char *path, const char *file_name,  char *file_path)
{
	strcpy(file_path, path);
	if(file_path[strlen(path) - 1] != '/')
		strcat(file_path, "/");
	strcat(file_path, file_name);
}

//判断是否为目录
bool STFileUtility::is_dir(const char *path)
{
	#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	struct stat statbuf;
	if(lstat(path, &statbuf) ==0)//lstat返回文件的信息，文件信息存放在stat结构中
	{
		return S_ISDIR(statbuf.st_mode) != 0;//S_ISDIR宏，判断文件类型是否为目录
	}
	return false;
#else

	return false;
#endif
	
}

//判断是否为常规文件
bool STFileUtility::is_file(const char *path)
{
	#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	struct stat statbuf;
	if(lstat(path, &statbuf) ==0)
		return S_ISREG(statbuf.st_mode) != 0;//判断文件是否为常规文件
	return false;
#else

	return false;
#endif
}

