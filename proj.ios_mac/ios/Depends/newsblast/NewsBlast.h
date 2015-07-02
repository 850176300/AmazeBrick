//
//  NewsBlast.h
//  NewsBlast
//
//  Created by anonymous on 2/11/11.
//  Copyright 2011 MyCompany. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef enum {
    InvokeModeLaunch = 0,
    InvokeModeResume,
    InvokeModeReturnHome,
    kInvokeModeCount,
}InvokeMode;

extern NSString * const kNewsBlastClickOKNotification;
extern NSString * const kNewsBlastClickCancelNotification;
extern NSString * const kNewsBlastServedNotification;

@class NewsBlast;

@protocol NewsBlastDelegate <NSObject>

@optional
- (void)viewDidShow:(NewsBlast *)newsBlast;
- (void)viewDidNotShow:(NewsBlast *)newsBlast;
- (void)viewDidClickCancel:(NewsBlast *)newsBlast;
- (void)viewDidClickOK:(NewsBlast *)newsBlast;

- (BOOL)shouldDisplayNewsBlast;

@end

@interface NewsBlast : NSObject <UIAlertViewDelegate>{
    
	NSString* _serverPath;
    NSMutableData* _data;
	NSString* _newsLink;
	NSString* _id;
	
	BOOL isDebugMode;
    
    id<NewsBlastDelegate> _delegate;
    
    UIAlertView *_alertView;
}

@property (nonatomic,retain) NSString* serverPath;
@property (nonatomic, retain) NSString *domainName;
@property (nonatomic, assign) NSTimeInterval timeOutSeconds;
@property (nonatomic, assign) id<NewsBlastDelegate> delegate;

@property (nonatomic, assign) InvokeMode invokeMode;

+(id)shareNews;
+(void)startNews;
+(void)startNewsUsingDebugMode;

-(void)sendNews;
-(void)sendNews:(BOOL) isDebugMode_;

- (void)cancelShowNewsBlast;

@end
