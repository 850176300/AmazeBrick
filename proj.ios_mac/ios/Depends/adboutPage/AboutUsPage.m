//
//  AboutUsPage.m
//  AboutUsPage
//
//  Created by anonymous on 10-12-29.
//  Copyright 2010 MyCompany. All rights reserved.
//

#import "AboutUsPage.h"
#import "OpenUDID.h"

@interface AboutUsPage(Private)
//  Utility
- (CGRect)getCurrentFrame;
- (void)createViews;
- (UIColor *)getBgColor;
- (BOOL) contentBgIsOpacity;
- (CGPoint) getCloseBtnOffset;
- (void) loadContentsFromURL:(NSURL *)url;
//  init
- (AboutUsPage *)initAboutUsPageWithDelegate:(id<AboutUsPageDelegate>)theDelegate;
@end

NSString * const kAboutPageWillShowNotification = @"moregame_click";
NSString * const kAboutPageWillDismissNotification = @"moregame_close";

@implementation AboutUsPage

@synthesize delegate = _delegate;
@synthesize didAppearBlock = _didAppearBlock, didDisappearBlock = _didDisappearBlock;

#define kTITLE_HEIGHT 44
#define kTAG_CLOSE_BUTTON 891

#define IS_IPAD (UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPad)
#define RGBACOLOR(r,g,b)    [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]

#pragma mark - life cycle
- (id)init {
    
	return [self initWithFrame:CGRectZero];
}

- (void)dealloc {
    
	[_indicator release];
	[_contentView release];
    [_appsKey release];
    
    [super dealloc];
}

- (id)initWithFrame:(CGRect)frame {
    
	return [self initAboutUsPageWithDelegate:nil];
}

+ (AboutUsPage *)aboutUsPage {
    
	return [[[AboutUsPage alloc] initAboutUsPageWithDelegate:nil] autorelease];
}

+ (AboutUsPage *)aboutUsPageWithDelegate:(id<AboutUsPageDelegate>)theDelegate {
    
	return [[[AboutUsPage alloc] initAboutUsPageWithDelegate:theDelegate] autorelease];
}

- (AboutUsPage *)initAboutUsPageWithDelegate:(id<AboutUsPageDelegate>)theDelegate {
    
	CGRect rect = [self getCurrentFrame];
	self = [super initWithFrame:rect];
	if (self) {
        
		_delegate = theDelegate;
        self.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		
		NSString *appId = [[[[NSBundle mainBundle] bundleIdentifier] componentsSeparatedByString:@"."] lastObject];
		NSString *bundleID = [[NSBundle mainBundle] bundleIdentifier];
        
        NSString *dataFile=[[NSBundle mainBundle] pathForResource:@"aboutpage" ofType:@"plist"];
        NSAssert(dataFile,@"aboutpage.plist not found,error!");
        NSDictionary *dataDic=[NSDictionary dictionaryWithContentsOfFile:dataFile];
        NSString *appsKey=[dataDic objectForKey:@"domain"];
        
        //  bundle name or domain name
		_appsKey = appsKey?appsKey:[[bundleID componentsSeparatedByString:@"."] objectAtIndex:1];
        [_appsKey retain];
		
        BOOL isOpacity = [self contentBgIsOpacity];
        UIColor *bgColor=[self getBgColor];
		self.backgroundColor = bgColor;
		
        //  create views
        [self createViews];
        
		// init content view
		_contentView = [[UIWebView alloc] initWithFrame:CGRectMake(0, kTITLE_HEIGHT, rect.size.width, rect.size.height-kTITLE_HEIGHT)];
        _contentView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		_contentView.delegate = self;
		_contentView.backgroundColor = [UIColor clearColor];
		[self addSubview:_contentView];
        _contentView.opaque = isOpacity?NO:YES;
		
        //  get the url
        NSString *suffix = [[bundleID componentsSeparatedByString:@"."] objectAtIndex:0];
		NSString *kurl_ = [NSString stringWithFormat:@"http://services.%@.%@/more/",_appsKey,suffix];
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
		[self loadContentsFromURL:[NSURL URLWithString:url]];
	}
	return self;
}

- (UIColor*) getBgColor
{
    NSString *dataFile=[[NSBundle mainBundle] pathForResource:@"aboutpage" ofType:@"plist"];
    NSAssert(dataFile,@"aboutpage.plist not found,error!");
    NSDictionary *dataDic=[NSDictionary dictionaryWithContentsOfFile:dataFile];
    NSString *bgColorInfo=[dataDic objectForKey:@"bgcolor"];
    if([bgColorInfo hasPrefix:@"bg"]) 
    {
        NSString *theName = [NSString stringWithFormat:@"bg_%@%@.jpg", _appsKey, IS_IPAD?@"_ipad":@""];
        return [UIColor colorWithPatternImage:[UIImage imageNamed:theName]];
    }
    else
    {
        NSArray *colorComponents=[bgColorInfo componentsSeparatedByString:@","];
        NSAssert(colorComponents.count==3,@"bg clolr components not equal to 3");
        float r=[[colorComponents objectAtIndex:0] floatValue];
        float g=[[colorComponents objectAtIndex:1] floatValue];
        float b=[[colorComponents objectAtIndex:2] floatValue];
        return RGBACOLOR(r, g, b);
    }
    return nil;
}

- (BOOL) contentBgIsOpacity
{
    NSString *dataFile=[[NSBundle mainBundle] pathForResource:@"aboutpage" ofType:@"plist"];
    NSDictionary *dataDic=[NSDictionary dictionaryWithContentsOfFile:dataFile];
    return [[dataDic objectForKey:@"opacity"] boolValue];
}

- (CGPoint) getCloseBtnOffset
{
    NSString *dataFile=[[NSBundle mainBundle] pathForResource:@"aboutpage" ofType:@"plist"];
    NSDictionary *dataDic=[NSDictionary dictionaryWithContentsOfFile:dataFile];
    NSString *closeInfo=[dataDic objectForKey:@"close_offset"];
    NSArray *universalOffsetArr=[closeInfo componentsSeparatedByString:@"#"];
    NSAssert(universalOffsetArr.count==2,@"close btn offset not equal to 2");
    BOOL isIpad=UI_USER_INTERFACE_IDIOM()==UIUserInterfaceIdiomPad;
    return CGPointFromString(isIpad? [universalOffsetArr objectAtIndex:1] : [universalOffsetArr objectAtIndex:0]);
}

#pragma mark - show & dismiss
- (void)showInView:(UIView *)theView {
    
    // 添加一个通知
    [[NSNotificationCenter defaultCenter] postNotificationName:kAboutPageWillShowNotification object:self];
    
	CGRect rect = [self getCurrentFrame];
//	float width = rect.size.width;
//	float height = rect.size.height;
    
    rect = [[UIScreen mainScreen] bounds];
    if (UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation])) {
        CGFloat width = MAX(CGRectGetHeight(rect), CGRectGetWidth(rect));
        CGFloat height = MIN(CGRectGetHeight(rect), CGRectGetWidth(rect));
        rect = CGRectMake(0, 0, width, height);
    }
	
    CGFloat dt = 0;
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0) {
        dt = [self getStatusBarHeight];
    }
    
//	self.center = CGPointMake(width/2, height/2*3 + dt);
    
    CGRect frame = self.frame;
    frame.origin.y = CGRectGetHeight(rect);
    self.frame = frame;
    
	[theView addSubview:self];
	[UIView beginAnimations:@"show" context:nil];
	[UIView setAnimationDelegate:self];
	[UIView setAnimationDuration:.3];
//	self.center = CGPointMake(width/2, height/2 + dt);
    frame.origin.y = CGRectGetHeight(rect) - CGRectGetHeight(self.bounds);
    self.frame = frame;
	[UIView commitAnimations];
	
	if (_delegate && [_delegate respondsToSelector:@selector(pageDidAppear:)]) {
        [_delegate pageDidAppear:self];
	}else if(_didAppearBlock) {
        _didAppearBlock(self);
    }
}

- (CGFloat)getStatusBarHeight
{
    if (UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation])) {
        return [[UIApplication sharedApplication] statusBarFrame].size.width;
    }
    
    return [[UIApplication sharedApplication] statusBarFrame].size.height;
}

- (void)dismiss {
    // 添加一个通知
    [[NSNotificationCenter defaultCenter] postNotificationName:kAboutPageWillDismissNotification object:self];
	[UIView beginAnimations:@"dismiss" context:nil];
	[UIView setAnimationDelegate:self];
	[UIView setAnimationDuration:.3];
	self.center = CGPointMake(self.bounds.size.width/2, self.bounds.size.height/2*3);
	[UIView commitAnimations];
	
	if (_delegate && [_delegate respondsToSelector:@selector(pageDidDisappear:)]) {
        [_delegate pageDidDisappear:self];
	}else if(_didDisappearBlock) {
        _didDisappearBlock(self);
    }
}

#pragma mark - Animation delegate methods
- (void)animationDidStop:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context {
    
	if ([animationID isEqualToString:@"show"]) {
		UIButton* close_btn = (UIButton*)[self viewWithTag:kTAG_CLOSE_BUTTON];
		[close_btn setUserInteractionEnabled:YES];
	}
	if ([animationID isEqualToString:@"dismiss"]) {
		[self removeFromSuperview];
	}
}

// 重写touch方法，防止touch传到下一层
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event { }
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event { }
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event { }
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event { } 

#pragma mark - Utility methods
- (CGRect)getCurrentFrame {
    
	CGRect rect = [UIScreen mainScreen].applicationFrame;
    UIInterfaceOrientation orit = [UIApplication sharedApplication].statusBarOrientation;
	if (UIInterfaceOrientationIsLandscape(orit)) {
        CGFloat width = MAX(rect.size.width, rect.size.height);
        CGFloat height = MIN(rect.size.width, rect.size.height);
		rect = CGRectMake(0, 0, width, height);
	}
	return rect;
}

- (void)createViews {
    
    float w = [self getCurrentFrame].size.width;
    
    // init title view
    UIImageView *titleView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, w, kTITLE_HEIGHT)];
    titleView.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    UIImage *bg_img = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"top-bg_%@",_appsKey] ofType:@"png"]];
    titleView.image = bg_img;
    
    //  init logo view
    UIImage *title_img = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"logo_%@",_appsKey] ofType:@"png"]];
    UIImageView *title_imgv = [[UIImageView alloc] initWithImage:title_img];
    title_imgv.center = CGPointMake(w/2, kTITLE_HEIGHT/2);
    title_imgv.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
    [titleView addSubview:title_imgv];
    [title_imgv release];
    [self addSubview:titleView];
    [titleView release];
    
    // init close button
    UIImage *img = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"close_%@",_appsKey] ofType:@"png"]];
    UIImage *img_h = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"close_%@_h",_appsKey] ofType:@"png"]];
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    [btn setUserInteractionEnabled:NO];
    btn.tag = kTAG_CLOSE_BUTTON;
    btn.exclusiveTouch = YES;
    [btn setImage:img forState:UIControlStateNormal];
    if (img_h) {
        [btn setImage:img_h forState:UIControlStateHighlighted];
    }
    [btn sizeToFit];
    [btn addTarget:self	action:@selector(dismiss) forControlEvents:UIControlEventTouchUpInside];
    btn.frame = CGRectOffset(btn.frame, titleView.bounds.size.width-btn.bounds.size.width, 0);
    CGPoint btnOffset=[self getCloseBtnOffset];
    btn.frame=CGRectOffset(btn.frame, btnOffset.x, btnOffset.y);
    btn.autoresizingMask = UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
    [self addSubview:btn];
    
    //  init indicator
    _indicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    _indicator.autoresizingMask = UIViewAutoresizingFlexibleTopMargin | UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleBottomMargin | UIViewAutoresizingFlexibleRightMargin;
    _indicator.hidesWhenStopped = YES;
    _indicator.center = CGPointMake(self.bounds.size.width/2, self.bounds.size.height/2);
    [self addSubview:_indicator];
}


- (void)loadContentsFromURL:(NSURL *)url {
    
	[_indicator startAnimating];
	[_contentView loadRequest:[NSMutableURLRequest requestWithURL:url]];
}

#pragma mark - UIWebViewDelegate methods
- (void)webViewDidFinishLoad:(UIWebView *)webView {
    
	[_indicator stopAnimating];
    
    NSString *schemes = [webView stringByEvaluatingJavaScriptFromString:@"get_apps_ios();"];
    NSArray *array = [schemes componentsSeparatedByString:@"\n"];
    
    NSMutableArray *installedApps = [NSMutableArray arrayWithCapacity:[array count]];
    for (NSString *scheme in array) {
        if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:scheme]]) {
            [installedApps addObject:@"1"];
        } else {
            [installedApps addObject:@"0"];
        }
    }
    NSString *string = [installedApps componentsJoinedByString:@","];
    string = [NSString stringWithFormat:@"set_apps_ios([%@]);", string];
    [webView stringByEvaluatingJavaScriptFromString:string];
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType {
    
	if (navigationType == UIWebViewNavigationTypeLinkClicked) {
		[[UIApplication sharedApplication] openURL:[request URL]];
		return NO;
	}
	return YES;
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
    
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:[error localizedDescription] delegate:nil cancelButtonTitle:nil otherButtonTitles:@"OK",nil];
	[alert show];
	[alert release];
}

@end
