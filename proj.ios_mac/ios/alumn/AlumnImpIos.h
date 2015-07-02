//
//  AlumnImpIos.h
//  Doctor2
//
//  Created by tanshoumei on 13-9-18.
//
//

#import <Foundation/Foundation.h>
#import <MessageUI/MessageUI.h>

@interface AlumnImpIos : NSObject {
    bool isTakingPhoto;
}

+ (AlumnImpIos*) shared;
+ (void) purge;
//请求保存图片到相册
- (void) saveToAlumn:(UIImage*) apImg;

@end

