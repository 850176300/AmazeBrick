
//
//  SuperGlobal.h
//  DND2052_Baby_Play_Town
//
//  Created by liuwei on 14-12-25.
//
//

#ifndef DND2052_Baby_Play_Town_SuperGlobal_h
#define DND2052_Baby_Play_Town_SuperGlobal_h

#include <iostream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;


inline string convertIntToString(int num);
string convertIntToString(int num){
    __String* tempString = __String::createWithFormat("%d", num);
    stringstream ss;
    ss<<tempString->getCString();
    return ss.str();
}
enum ALLItemOrder{
    kHomeBtn = 100,
    kPrompt,
    kDialog,
    
    kHomeDialog,
    kBackDialog,
    
    kLockTags = 120125,
};

#define IAPCOUTNS 6
#define DealAllIAP string("net.babyandmommy.ponyoutdoor.bestdeal")
#define MoreBabyIAP string("net.babyandmommy.ponyoutdoor.unlockallponies")
#define MazeGameIAP string("net.babyandmommy.ponyoutdoor.unlockfariytaleforest")
#define GoldCoaseIAP string("net.babyandmommy.ponyoutdoor.unlockgoldcoast")
#define RemoveADIAP string("net.babyandmommy.ponyoutdoor.noads")
#define UnlockallIAP string("net.babyandmommy.ponyoutdoor.unlockall")


#define PURCHASESUCCEED "PurchaseSucceed"

#define kUnlockModel1 "eric"
#define kUnlockModel2 "danny"
#define kUnlockModel3 "sara"


#define kPuaseGame "pause"
#define kResumeGame "resume"
#define kLightOnOff "LightOnOff"
#define kPuaseTip "pauseTip"
#define kResumeTip "resumeTip"
#endif
