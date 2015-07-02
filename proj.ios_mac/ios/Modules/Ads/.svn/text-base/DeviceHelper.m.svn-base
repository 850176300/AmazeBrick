//
//  DeviceHelper.m
//  Poochie
//
//  Created by jordenwu on 8/29/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DeviceHelper.h"
#import <SystemConfiguration/SystemConfiguration.h>
#import <CoreFoundation/CoreFoundation.h>
#include <sys/socket.h> // Per msqr
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#import <netinet/in.h>
#import <netinet6/in6.h>
#import <arpa/inet.h>
#import <ifaddrs.h>
#import <netdb.h>



@implementation DeviceHelper

//是否是iphone 3G 
+(BOOL)isIphone3G
{   
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    
    char *answer = malloc(size);
    sysctlbyname("hw.machine", answer, &size, NULL, 0);
    
    NSString *results = [NSString stringWithCString:answer encoding: NSUTF8StringEncoding];
    
    free(answer);
    
    if ([results isEqualToString:@"iPhone1,2"])    
        return YES;
    else
        return NO;    
}
//是否是iphone平台 否者就是ipad平台了
+(BOOL)isIphoneTarget
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        return NO;
    }
    return YES;
}
+(BOOL)isRetina
{
    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]
        && [[UIScreen mainScreen] scale] == 2.0) {
        // Retina
        return YES;
    } else {
        // Not Retina
        return NO;
    }
}

+(BOOL)isLessOS4
{
    NSString *osVersion=[[UIDevice currentDevice] systemVersion];
    NSString *fristVersion=[[osVersion componentsSeparatedByString:@"."] objectAtIndex:0];
    int num=0;
    num=[fristVersion intValue];
    if (num<4) {
        return YES;
    }else {
        return NO;
    }
}

+(BOOL)isIphone5 {
    return [UIScreen mainScreen].bounds.size.height == 568;
}

+(BOOL)isNetworkAvaliable {
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
    
    SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
    SCNetworkReachabilityFlags flags;
    
    BOOL didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
    CFRelease(defaultRouteReachability);
    
    if (!didRetrieveFlags) {
        return NO;
    }
    
    BOOL isReachable = flags & kSCNetworkFlagsReachable;
    BOOL needsConnection = flags & kSCNetworkFlagsConnectionRequired;
    // = flags & kSCNetworkReachabilityFlagsIsWWAN;
    BOOL nonWifi = flags & kSCNetworkReachabilityFlagsTransientConnection;
    BOOL moveNet = flags & kSCNetworkReachabilityFlagsIsWWAN;
    
    return ((isReachable && !needsConnection) || nonWifi || moveNet) ? YES : NO;
}

@end
