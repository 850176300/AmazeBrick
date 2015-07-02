//
//  MoreGameURL.m
//  BBQParty
//
//  Created by liuwei on 14-8-1.
//
//

#import "MoreGameURL.h"
#import "OpenUDID.h"
#import "UIDevice-Hardware.h"

@implementation MoreGameURL

+(NSString*)MoreGameUrl{
    NSString *appId = [[[[NSBundle mainBundle] bundleIdentifier] componentsSeparatedByString:@"."] lastObject];
    NSString *bundleID = [[NSBundle mainBundle] bundleIdentifier];
    NSString *suffix = [[bundleID componentsSeparatedByString:@"."] objectAtIndex:0];
    NSString *kurl_ = [NSString stringWithFormat:@"http://services.%@.%@/more/",[[bundleID componentsSeparatedByString:@"."] objectAtIndex:1],suffix];
    NSMutableString *url = [NSMutableString stringWithString:kurl_];
    [url appendFormat:@"%@/",appId];
    
    // get current language
    NSUserDefaults* defs = [NSUserDefaults standardUserDefaults];
    NSArray* languages = [defs objectForKey:@"AppleLanguages"];
    NSString* preferredLang = [languages objectAtIndex:0];
    [url appendFormat:@"%@/",preferredLang];
    
    UIDevice *_device = [UIDevice currentDevice];
    // append udid - changed to OpenUDID at 2.1.0rc
    [url appendFormat:@"%@/",[OpenUDID value]];
    // append model
    [url appendFormat:@"?model=%@",[[_device platformString] stringByReplacingOccurrencesOfString:@" " withString:@"_"]];
    // append systemVersion
    [url appendFormat:@"&sysVer=%@",[_device systemVersion]];
    
    // append bundleVersion
    NSString *bundleVer = [[[NSBundle mainBundle] infoDictionary] valueForKey:@"CFBundleVersion"];
    [url appendFormat:@"&bundleVer=%@",bundleVer];
    
    // append full bundleID
    [url appendFormat:@"&bundleID=%@",bundleID];
    
    [url appendString:@"&format=json"];
    
    return url;
}

@end
