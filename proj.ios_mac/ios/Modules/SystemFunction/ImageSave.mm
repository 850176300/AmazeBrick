//
//  ImageSave.m
//  KidsSalon
//
//  Created by chenxi1 on 13-11-5.
//
//

#import "ImageSave.h"
#import <UIKit/UIKit.h>
#include <cocos2d.h>
using namespace::cocos2d;
#include<AssetsLibrary/AssetsLibrary.h>



@implementation ImageSave

- (void)saveImage : (char *)pImagePath withTarget:(CCObject*) target withCallFun : (CallFunction)callFun;{
    UIImage *lImage = [[UIImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:pImagePath]];
    ALAssetsLibrary* library = [[ALAssetsLibrary alloc] init];
    [library writeImageToSavedPhotosAlbum: lImage.CGImage metadata:nil completionBlock:^(NSURL *assetURL, NSError *error2)
     {
         //             report_memory(@"After writing to library");
   //      [[[error2 userInfo] objectForKey:@"NSLocalizedDescription" ] UTF8String]
         if (error2) {
             NSLog(@"ERROR: the image failed to be written");
             (target->*callFun)((void*) false,(void*)[[error2 localizedDescription] UTF8String]);
         }
         else {
             NSLog(@"PHOTO SAVED - assetURL: %@", assetURL);
             (target->*callFun)((void*) true,(void*)[[error2 localizedDescription] UTF8String]);
         }
         
         //runOnMainQueueWithoutDeadlocking(^{
             //                 report_memory(@"Operation completed");
             //[photoCaptureButton setEnabled:YES];
         //});
     }];
}

@end
