//
//  AboutUsPage.h
//  AboutUsPage
//
//  Created by anonymous on 10-12-29.
//  Copyright 2010 MyCompany. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import "UIDevice-Hardware.h"

@protocol AboutUsPageDelegate;

@class AboutUsPage;
typedef void(^AboutBlock)(AboutUsPage *);

extern NSString * const kAboutPageWillShowNotification;
extern NSString * const kAboutPageWillDismissNotification;

@interface AboutUsPage : UIView <UIWebViewDelegate> {
    
	UIWebView                   *_contentView;
    UIActivityIndicatorView     *_indicator;
    
    NSString                    *_appsKey;
	id<AboutUsPageDelegate>  _delegate;
    
    //  iOS4+ support
    AboutBlock     _didAppearBlock;
    AboutBlock     _didDisappearBlock;
}

@property(nonatomic, assign) id<AboutUsPageDelegate> delegate;

@property(nonatomic, assign) AboutBlock didAppearBlock, didDisappearBlock;

//  create about us page
+ (AboutUsPage *)aboutUsPage;
+ (AboutUsPage *)aboutUsPageWithDelegate:(id<AboutUsPageDelegate>)theDelegate;

//  show & dismiss
- (void)showInView:(UIView *)theView;
- (void)dismiss;

@end

@protocol AboutUsPageDelegate <NSObject>
@optional
- (void)pageDidAppear:(AboutUsPage *)aboutusPage;
- (void)pageDidDisappear:(AboutUsPage *)aboutusPage;
@end

