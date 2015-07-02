//
//  AnalyticsTool.h
//  Central_Analytics
//
//  Created by jianghai on 4/9/14.
//  Copyright (c) 2014 jianghai. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import <CoreTelephony/CTCarrier.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>
#import <SystemConfiguration/SystemConfiguration.h>

@interface AnalyticsTool : NSObject<SKPaymentTransactionObserver>

@property (nonatomic , assign) long long session_start;
@property (nonatomic , assign) long long session_end;
@property (nonatomic , assign) long long install_date;
@property (nonatomic , assign) long long newsblast_served;
@property (nonatomic , assign) long long moregame_served;
@property (nonatomic , assign) UIBackgroundTaskIdentifier bgTask;
@property (nonatomic , retain) NSString* SessionID;
@property (nonatomic , assign) BOOL SengData;
+ (AnalyticsTool *)sharedTool;
/*
 **开始会话
 **需要在application:application didFinishLaunchingWithOptions:里面调用
 */
- (void)StartSession;
- (void)StartSessionWithSentFile:(BOOL)sendData;
@end
