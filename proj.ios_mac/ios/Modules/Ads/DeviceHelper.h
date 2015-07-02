//
//  DeviceHelper.h
//  Poochie
//
//  Created by jordenwu on 8/29/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**设备系统版本查找类*/
@interface DeviceHelper : NSObject
/**是否是iphone 3G机子 */
+(BOOL)isIphone3G;
/**是否是iphone平台 否者就是ipad平台了*/
+(BOOL)isIphoneTarget;
/**是否是iphone高清屏 */
+(BOOL)isRetina;
/**系统版本是否低于IOS4*/
+(BOOL)isLessOS4;
/**是否是iphone5*/
+(BOOL)isIphone5;
+(BOOL)isNetworkAvaliable;
@end
