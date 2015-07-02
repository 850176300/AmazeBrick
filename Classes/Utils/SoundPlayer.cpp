//
//  SoundPlayer.cpp
//  Doctor
//
//  Created by tanshoumei on 13-8-23.
//
//

#include "SoundPlayer.h"
//#include "MathUtil.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

#define RoleCount 4

SoundPlayer::SoundPlayer():
bgMusic("nomusic"),
washingID(0),
addPipeID(0)
{

    canPlaySound = UserDefault::getInstance()->getBoolForKey("isSoundOpen", true);

    canPlayMusic = UserDefault::getInstance()->getBoolForKey("isMusicOpen", true);
    
    if (canPlayMusic) {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.8f);
    }else {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
    }
    if (canPlaySound) {
        SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
    }else {
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
    }
    
}

void SoundPlayer::switchMusic(){
    canPlayMusic = !canPlayMusic;
    
    UserDefault::getInstance()->setBoolForKey("isMusicOpen", canPlayMusic);
    UserDefault::getInstance()->flush();
    if (canPlayMusic) {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.8f);
    }else {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
    }
    if (canPlaySound) {
        SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
    }else {
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
    }
}
void SoundPlayer::switchSound(){
    canPlaySound = !canPlaySound;
    UserDefault::getInstance()->setBoolForKey("isSoundOpen", canPlaySound);
    UserDefault::getInstance()->flush();
    if (canPlayMusic) {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.8f);
    }else {
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
    }
    if (canPlaySound) {
        SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
    }else {
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
    }
}

void SoundPlayer::switchVolume(){
    switchMusic();
    switchSound();
}

bool SoundPlayer::isMusicOpen(){
    return canPlayMusic;
}
bool SoundPlayer::isSoundOpen(){
    return canPlaySound;
}

#pragma mark 背景音效播放
void SoundPlayer::playBackGroundMusic(const char *bgMusic) {
    stringstream s;
    s<<bgMusic;
    if (this->bgMusic.compare(s.str()) == 0) {
        return;
    }
    this->bgMusic = s.str();
    if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
    SimpleAudioEngine::getInstance()->playBackgroundMusic(bgMusic, true);
    
}

void SoundPlayer::stopBackGroundMusic(){
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void SoundPlayer::resumeBackGroundMusic(){
    if (bgMusic.compare("nomusic") != 0) {
        
        SimpleAudioEngine::getInstance()->playBackgroundMusic(bgMusic.c_str(), true);
    }
}

void SoundPlayer::stopAlleffect(){
    addPipeID = 0;
    SimpleAudioEngine::getInstance()->stopAllEffects();
}
#pragma mark 基本音效播放
void SoundPlayer::playclickeffect(){
    SimpleAudioEngine::getInstance()->playEffect("click.wav");
}


void SoundPlayer::playHomeClickedEffect(){
    SimpleAudioEngine::getInstance()->playEffect("sound/studio basic/home.mp3");
}

void SoundPlayer::playNextClickedEffect(){
    SimpleAudioEngine::getInstance()->playEffect("sound/studio basic/next.mp3");
}

void SoundPlayer::playPreviousClickedEffect(){
    SimpleAudioEngine::getInstance()->playEffect("sound/studio basic/previous.mp3");
}

void SoundPlayer::playResetClickedEffect(){
    SimpleAudioEngine::getInstance()->playEffect("sound/studio basic/reset.mp3");
}

void SoundPlayer::playStartClickedEffect(){
    SimpleAudioEngine::getInstance()->playEffect("sound/studio basic/start.mp3");
}

void SoundPlayer::playCommonEffect(const string &effect) {
    SimpleAudioEngine::getInstance()->playEffect(effect.c_str());

}

void SoundPlayer::playCommonLoopEffect(const string &effect) {
    SimpleAudioEngine::getInstance()->playEffect(effect.c_str(), true);
}