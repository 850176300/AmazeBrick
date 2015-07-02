//
//  AnalysisManager.m
//  AdsPopupDemo
//
//  Created by tang.wei on 13-12-13.
//  Copyright (c) 2013年 tang.wei. All rights reserved.
//

#import "AnalysisManager.h"
#import "Flurry.h"
#import "AppConfigs.h"

@implementation AnalysisManager
{
    BOOL _enabled;
}

+ (id)sharedManager
{
    static AnalysisManager *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (!instance) {
            instance = [[AnalysisManager alloc] init];
        }
    });
    return instance;
}

- (id)init { if (self = [super init]) _enabled = YES; return self; }

// 如果不设置默认会从AppConfigs里面读取Flurry key
- (void)startSession
{ 
    [self startSession:FLURRY_KEY];
}

// 启动Flurry key会话
- (void)startSession:(NSString *)flurryKey
{
    if (_enabled && flurryKey.length > 0) {
        [self performSelector:@selector(realStartSession:) withObject:flurryKey afterDelay:2.0];
#if DEBUG+COCOS2D_DEBUG>0
        NSLog(@"Flurry Key: %@",flurryKey);
#endif

    }
}

// 是否支持Flurry
- (void)setEnabled:(BOOL)yesOrNo
{
    _enabled = yesOrNo;
}

- (void)realStartSession:(NSString *)key
{
    [Flurry startSession:key];
}

@end
