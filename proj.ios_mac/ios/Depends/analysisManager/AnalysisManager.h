//
//  AnalysisManager.h
//  AdsPopupDemo
//
//  Created by tang.wei on 13-12-13.
//  Copyright (c) 2013年 tang.wei. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AnalysisManager : NSObject

+ (id)sharedManager;

// 如果不设置默认会从AppConfigs里面读取Flurry key
- (void)startSession;
// 启动Flurry会话
- (void)startSession:(NSString *)flurryKey;

// 设置是否支持Flurry
// 默认支持Flurry
- (void)setEnabled:(BOOL)yesOrNo;

@end
