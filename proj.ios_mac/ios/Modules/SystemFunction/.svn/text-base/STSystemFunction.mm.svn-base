//
//  STSystemFunction.cpp
//  MysteryGuardians
//
//  Created by Steven.Tian on 13-7-9.
//
//

#include "STSystemFunction.h"
#include "SystemFunctionIOSWrapper.h"
#import "ImageSave.h"
#import "MoreGameURL.h"

STSystemFunction::STSystemFunction()
{
}

STSystemFunction::~STSystemFunction()
{
}

void STSystemFunction::sendEmail(const char* subject, const char* body)
{
    [[SystemFunctionManager sharedManager]sendEmail : [NSString stringWithCString:subject encoding:NSUTF8StringEncoding]
                                             Content:[NSString stringWithCString:body encoding:NSUTF8StringEncoding]];
}

void STSystemFunction::popAlertDialog(const char *message)
{
    [[SystemFunctionManager sharedManager]popAlertDialog:[NSString stringWithCString:message encoding:NSUTF8StringEncoding]];
}

void STSystemFunction::showMoreGame()
{
    [[SystemFunctionManager sharedManager]showMorePage];
}

void STSystemFunction::go2MarketDetail(std::string packagename)
{
//    [[SystemFunctionManager sharedManager]go2Market:[NSString stringWithCString:packagename.c_str() encoding:NSUTF8StringEncoding]];
}

void STSystemFunction::makeToast(const char* message)
{
}

void STSystemFunction::rating()
{
}

void STSystemFunction::contactUs()
{
}

void STSystemFunction::sendEmailAndAssetPic(std::string subject, std::string message, std::string assetName)
{}

void STSystemFunction::sendEmailAndFilePic(std::string subject, std::string message, std::string fileName)
{
    
}

std::string STSystemFunction::getSdCardPath()
{
    return "";
}

bool STSystemFunction::checkNetworkAvailable()
{
    return true;
}

bool STSystemFunction::isTabletAvailable()
{
    return true;
}

float STSystemFunction::densityScale()
{
    return 0.0f;
}

void STSystemFunction::rateUs(){
    
}

void STSystemFunction::dismissRateUs(){
    
}

void STSystemFunction::saveImage(std::string fileCache,CCObject* selector,CallFunction callback){
    ImageSave *lImageSave = [[ImageSave alloc] init];
    [lImageSave saveImage:(char *)fileCache.c_str() withTarget:selector withCallFun:callback];
}

void STSystemFunction::goToPrivacy()
{
    [[SystemFunctionManager sharedManager]goToPrivacy];
}

void STSystemFunction::showNewsBlast()
{
    [[SystemFunctionManager sharedManager] showNewsBlast];
}


void STSystemFunction::showNewsBlast(NewsBlastMode mode){
    [[SystemFunctionManager sharedManager] showNewsBlast:mode];
}

void STSystemFunction::endAnalytics()
{
    
}

void STSystemFunction::refreshDCIM(std::string sFileDir)
{
    
}


//std::string STSystemFunction::getMoreGameUrl(){
//    NSString* urlString = [MoreGameURL MoreGameUrl];
//    std::stringstream stream;
//    stream<<[urlString UTF8String];
//    return stream.str();
//
//}

int STSystemFunction::getScreenRotation(){
    return 0;
}

