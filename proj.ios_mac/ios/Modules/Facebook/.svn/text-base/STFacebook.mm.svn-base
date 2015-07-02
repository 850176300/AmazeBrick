//
//  STFacebook.mm
//  SweetDiscovery
//
//  Created by zhangguangzong1 on 9/3/13.
//
//

#include "STFacebook.h"

STFacebook *STFacebook::_instance = NULL;

STFacebook* STFacebook::getInstance(){
    if (NULL == _instance) {
        _instance = new STFacebook;
    }
    
    return _instance;
}

STFacebook::STFacebook()
{
}

STFacebook::~STFacebook()
{
}

void STFacebook::NativePostStatusUpdate(int tag, std::string text){
//    [[FBManager sharedManager] postStatus:[NSString stringWithUTF8String:text.c_str()]];
}

void STFacebook::NativePostPhotoFromAsset(int tag, std::string filename, std::string message){
//    [[FBManager sharedManager] postGraph:[NSString stringWithUTF8String:filename.c_str()] withMessage:[NSString stringWithUTF8String:message.c_str()]];
}

void STFacebook::NativePostPhotoFromFile(int tag, std::string filename, std::string message){
//    [[FBManager sharedManager] postGraph:[NSString stringWithUTF8String:filename.c_str()] withMessage:[NSString stringWithUTF8String:message.c_str()]];
}

void STFacebook::NativePostRichContentAsset(int tag, std::string message, std::string link, std::string assetFileName){
    
}

void STFacebook::NativePostRichContentFile(int tag, std::string message, std::string link, std::string fileName){
//    [[FBManager sharedManager] showFBDialog];
}

/*
 Help refrence: https://developers.facebook.com/docs/ios/publish-to-feed-ios-sdk/
                https://developers.facebook.com/docs/reference/api/post/
 
 example format:
 @"link" : @"https://developers.facebook.com/ios",
 @"picture" : @"https://developers.facebook.com/attachment/iossdk_logo.png",
 @"name" : @"Facebook SDK for iOS",
 @"caption" : @"Build great social apps and get more installs.",
 @"description" : @"The Facebook SDK for iOS makes it easier and faster to develop Facebook integrated iOS apps."
 */
void STFacebook::NativePostStory(map<string ,string > pStory){
//    NSMutableDictionary *lPostParams = [NSMutableDictionary dictionary];
//    map<string, string>::iterator lIterator = pStory.begin();
//    for (; lIterator != pStory.end(); ++lIterator) {
//        string lKey = lIterator->first;
//        string lValue = lIterator->second;
//        [lPostParams setObject:[NSString stringWithUTF8String:lValue.c_str()] forKey:[NSString stringWithUTF8String:lKey.c_str()]];
//        
//    }
//    [[FBManager sharedManager] postStory:lPostParams];
}
