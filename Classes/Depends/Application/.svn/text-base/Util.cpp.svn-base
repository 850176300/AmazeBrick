#include "Util.h"
#include <string>


using namespace std;
bool Util::isExistFile(const char *pszFileName)
{
	FILE *fp = fopen(pszFileName, "rb");
    if(fp == NULL)
        return false;
    fclose(fp);
    return true;
}

const char* Util::getLanguageType()
{
	LanguageType currentLanguageType = Application::getInstance()->getCurrentLanguage();
//	char *path;
    switch (currentLanguageType)
    {
    case LanguageType::CHINESE:
		return "zh";
    case LanguageType::FRENCH:
		return "fr";
    case LanguageType::GERMAN:
		return "de";
    case LanguageType::ITALIAN:
		return "it";
    case LanguageType::RUSSIAN:
		return "ru";
    case LanguageType::SPANISH:
		return "es";
	case LanguageType::KOREAN:
		return "ko";
	default:
		return "en";
	
    }
}

Sprite* Util::getUISprite(const char* fileName)
{
	Sprite* sprite=NULL;
	
	sprite=Sprite::create(getUIFilePath(fileName).c_str());

	return sprite;
}

bool Util::loadUITexture(const char* language,const char* file)
{
	string plist="UI";
	string plist_resolution="UI";
	string plist_lang="UI";

	if(language!=0)
	{
		plist.append("-");
		plist.append(language);
		plist_lang.append("-");
		plist_lang.append(language);


	}
	plist.append("/");
	plist.append(file);
	plist_lang.append("/");
	plist_lang.append(file);
	plist_resolution.append("/");
	plist_resolution.append(file);




    if(!FileUtils::getInstance()->isFileExist(plist.append(".png").c_str())||!Util::isExistFile(plist.append(".plist").c_str()))
	{
		if (!FileUtils::getInstance()->isFileExist(plist_resolution.append(".png").c_str())||!FileUtils::getInstance()->isFileExist(plist_resolution.append(".plist").c_str()))
		{
			if (!FileUtils::getInstance()->isFileExist(plist_lang.append(".png").c_str())||!Util::isExistFile(plist_lang.append(".plist").c_str()))
			{
				plist="UI/";
				plist.append(file);
				plist.append(".plist");
			}else
			{
				plist=plist_lang;
			}
		}else
		{
			plist=plist_resolution;
		}
	}
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist.append(".png").c_str(),plist.append(".plist").c_str());

	return true;
}

Sprite* Util::getContentSprite( const char* fileName )
{
	Sprite* sprite=NULL;
	
 
	sprite=Sprite::create(getContentFilePath(fileName).c_str());

	return sprite;
}
Texture2D* Util::getContentTexture( const char* fileName )
{
	return Director::getInstance()->getTextureCache()->addImage(getContentFilePath(fileName).c_str());
}
Texture2D* Util::getUITexture( const char* fileName )
{
	return Director::getInstance()->getTextureCache()->addImage(getUIFilePath(fileName).c_str());
}
std::string Util::getContentFilePath( const char* fileName )
{
	const char* language=getLanguageType();
	string path="Content";
	string path_resolution="Content";
	string path_lang="Content";
    
	if(language!=0)
	{
		path.append("-");
		path.append(language);
		path_lang.append("-");
		path_lang.append(language);
	}
	path.append("/");
	path.append(fileName);
	path_lang.append("/");
	path_lang.append(fileName);
	path_resolution.append("/");
	path_resolution.append(fileName);
    
	if(!FileUtils::getInstance()->isFileExist(path.c_str()))
	{
        
        bool lRes = FileUtils::getInstance()->isFileExist(path_resolution);
		if(!lRes)
		{
            
			if(!FileUtils::getInstance()->isFileExist(path_lang.c_str()))
			{
				path="Content/";
				path.append(fileName);
			}else
			{
				path=path_lang;
			}
		}else
		{
			path=path_resolution;
		}
	}
	return path;
}
std::string Util::getUIFilePath( const char* fileName )
{
	const char* language=getLanguageType();
	string path="UI";
	string path_resolution="UI";
	string path_lang="UI";

    
	if(language!=0)
	{
		path.append("-");
		path.append(language);
		path_lang.append("-");
		path_lang.append(language);
	}
	path.append("/");
	path.append(fileName);
	path_lang.append("/");
	path_lang.append(fileName);
	path_resolution.append("/");
	path_resolution.append(fileName);

	if(!FileUtils::getInstance()->isFileExist(path.c_str()))
	{

        bool lRes = FileUtils::getInstance()->isFileExist(path_resolution);
		if(!lRes)
		{

			if(!FileUtils::getInstance()->isFileExist(path_lang.c_str()))
			{
				path="UI/";
				path.append(fileName);
			}else
			{
				path=path_lang;
			}
		}else
		{
			path=path_resolution;
		}
	}

	return path;
}
long Util::getCurrentTime()     
{      
	struct timeval tv;      
	gettimeofday(&tv,NULL);      
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;      
}    



std::string Util::replaceStr(std::string &str, const char *string_to_replace, const char *new_string)
{
	int index = str.find(string_to_replace);
	while(index != std::string::npos)
	{
		str.replace(index, strlen(string_to_replace), new_string);
		index = str.find(string_to_replace, index + strlen(new_string));
	}
	return str;
}
int Util:: randomNum(int start,int end){
    
//    srand((int)clock());
    return CCRANDOM_0_1()*end+start;
}
