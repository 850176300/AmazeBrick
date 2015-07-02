//
//  SoundPlayer.h
//  Doctor
//
//  Created by tanshoumei on 13-8-23.
//
//

#ifndef __Doctor__SoundPlayer__
#define __Doctor__SoundPlayer__

#include <iostream>
#include <sstream>
#include "SingleTon.h"
using namespace std;

class SoundPlayer: public SingleTon<SoundPlayer>
{
    friend class SingleTon<SoundPlayer>;
private:
    SoundPlayer();
public:
    //背景音乐
    void switchMusic();
    void switchSound();
    void switchVolume();
    bool isMusicOpen();
    bool isSoundOpen();
#pragma mark 背景音效播放
    void playBackGroundMusic(const char* bgMusic);
    void stopBackGroundMusic();
    void resumeBackGroundMusic();
    void stopAlleffect();
#pragma mark 基本音效比如：返回，首页，下一步等等
    void playResetClickedEffect();
    void playNextClickedEffect();
    void playHomeClickedEffect();
    void playStartClickedEffect();
    void playPreviousClickedEffect();
    void playclickeffect();
    

    void playCommonEffect(const string& effect);
    void playCommonLoopEffect(const string& effect);
    
    
private:
    unsigned int washingID;
    unsigned int addPipeID;
    string bgMusic;
    bool canPlayMusic;
    bool canPlaySound;
//    bool haveVolume;
    
    
};

#define SoundPlayerInstance SoundPlayer::getInstance()

#endif /* defined(__Doctor__SoundPlayer__) */
