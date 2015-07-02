//
//  NewsBlast.m
//  NewsBlast
//
//  Created by anonymous on 2/11/11.
//  Copyright 2011 MyCompany. All rights reserved.
//

#import "NewsBlast.h"
#import "UIDevice-Hardware.h" 
#import "GDataXMLNode.h"
#import "OpenUDID.h"

@interface NewsBlast()

@property (nonatomic, retain) NSURLConnection *connection;

@end

static NewsBlast* _instance;

#define KEY_NEWSID_VIEWED @"news_viewed"

NSString * const kNewsBlastClickOKNotification = @"newsblast_ok";
NSString * const kNewsBlastClickCancelNotification = @"newsblast_cancel";
NSString * const kNewsBlastServedNotification = @"newsblast_served";

@implementation NewsBlast
{
    BOOL _hasRequestedNews;
    BOOL _canShowAlert;
}

@synthesize serverPath=_serverPath;
@synthesize domainName;
@synthesize delegate = _delegate;
@synthesize timeOutSeconds, connection;

@synthesize invokeMode = _invokeMode;

static NSString* modes[kInvokeModeCount] = {@"launch",@"resume",@"return_home"};

+(void)startNews{
	[[self shareNews] sendNews];
}

+ (void) startNewsUsingDebugMode {
	[[self shareNews] sendNews:YES];
}

+(id)shareNews{
	if (nil == _instance) {
		_instance = [[NewsBlast alloc] init];
	}
	return _instance;
}

- (void) sendNews:(BOOL) isDebugMode_ {
    
//    if (_alertView && _alertView.isVisible) {
//        NSLog(@"alert view is visible!");
//        return;
//    }
    
    if (_hasRequestedNews) {
        return;
    }
	
    _canShowAlert = YES;
    _hasRequestedNews = YES;
    
	isDebugMode = isDebugMode_;
	
    [_data release];
	_data = [[NSMutableData data] retain];
	
//	NSURLRequest *request = [[NSURLRequest alloc] initWithURL: [NSURL URLWithString:self.serverPath]];
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:[NSURL URLWithString:self.serverPath]];
    if (self.timeOutSeconds > 0) {
        request.timeoutInterval = self.timeOutSeconds;
    }
	
    [self.connection cancel];
    
	self.connection = [[[NSURLConnection alloc] initWithRequest:request delegate:self] autorelease];
	
	[request release];
}

-(NSString*)serverPath
{
	NSMutableString *url = nil;
	NSArray *_appIds = [[[NSBundle mainBundle] bundleIdentifier] componentsSeparatedByString:@"."];
	
	if (nil == _serverPath) {
		url = [NSMutableString stringWithString:@""];
		if (nil!= _appIds && [_appIds count]>=3) {
			[url appendFormat:@"http://services.%@.%@/news/%@/", (self.domainName?self.domainName:[_appIds objectAtIndex:1]),[_appIds objectAtIndex:0], isDebugMode?@"news":[_appIds objectAtIndex:2]];
		}
	}else {
		url = [NSMutableString stringWithFormat:@"http://%@/news/%@/",_serverPath,isDebugMode?@"news":[_appIds objectAtIndex:2]];
	}

	// get current language
	NSUserDefaults* defs = [NSUserDefaults standardUserDefaults];
	NSArray* languages = [defs objectForKey:@"AppleLanguages"];
	NSString* preferredLang = [languages objectAtIndex:0];
	[url appendFormat:@"%@/",preferredLang];
	
	UIDevice *_device = [UIDevice currentDevice];
	// append udid - openudid changed at 2.1.0rc
	[url appendFormat:@"%@/",[OpenUDID value]];
	// append model
	[url appendFormat:@"?model=%@",[[_device platformString] stringByReplacingOccurrencesOfString:@" " withString:@"_"]];
	// append systemVersion
	[url appendFormat:@"&sysVer=%@",[_device systemVersion]];
	
	// append bundleVersion
	NSString *bundleVer = [[[NSBundle mainBundle] infoDictionary] valueForKey:@"CFBundleVersion"];
	[url appendFormat:@"&bundleVer=%@",bundleVer];
	
	// append full bundleID
	NSString *bundleID = [[NSBundle mainBundle] bundleIdentifier];
	[url appendFormat:@"&bundleID=%@",bundleID];
    
    //  new api
    [url appendFormat:@"&mode=%@", modes[self.invokeMode]];
	
	// add news_viewed
	NSString* news_viewed_Str = [[NSUserDefaults standardUserDefaults] objectForKey:KEY_NEWSID_VIEWED];
	if (nil != news_viewed_Str) {
		[url appendFormat:@"&news_viewed=%@",news_viewed_Str];
	}
	
	NSLog(@"NewsPop ---> url:%@", url);
	
	return url;
}

-(void)sendNews
{
	[self sendNews:NO];
}

- (void)cancelShowNewsBlast
{
    NSLog(@"Cancel showing news blast....");
    _canShowAlert = NO;
    _hasRequestedNews = NO;
    
    [self.connection cancel];
    self.connection = nil;
    [_data release];
    _data = nil;
}

-(void)processNews
{
	if (nil != _data ) {
		NSString* title =@"";
		NSString* content=@"";
		NSString* link=@"";
		NSString* newsId = @"";
		
		NSString* result = [[[NSString alloc] initWithData:_data encoding:NSUTF8StringEncoding] autorelease];
		NSError *error;
		GDataXMLDocument *doc = [[[GDataXMLDocument alloc] initWithXMLString: result options:0 error:&error] autorelease];
		if (doc == nil) { return; }
		//NSLog(@"LOG=%@", [[NSString alloc] initWithData:doc.XMLData encoding:NSUTF8StringEncoding]);
		NSArray *newsIds = [doc.rootElement nodesForXPath:@"//news/id" error:nil];
		if (newsIds.count > 0) {
			GDataXMLElement *newsIdElement = (GDataXMLElement *) [newsIds objectAtIndex:0];
			newsId = newsIdElement.stringValue;
		}
		
		NSArray *titles = [doc.rootElement nodesForXPath:@"//news/title" error:nil];
		if (titles.count > 0) {
			GDataXMLElement *titleElement = (GDataXMLElement *) [titles objectAtIndex:0];
			title = titleElement.stringValue;
			
		}
		
		NSArray *contents = [doc.rootElement nodesForXPath:@"//news/content" error:nil];
		if (contents.count > 0) {
			GDataXMLElement *contentElement = (GDataXMLElement *) [contents objectAtIndex:0];
			content = contentElement.stringValue;
			
		}
		
		NSArray *links = [doc.rootElement nodesForXPath:@"//news/link" error:nil];
		if (links.count > 0) {
			GDataXMLElement *linkElement = (GDataXMLElement *) [links objectAtIndex:0];
			link = linkElement.stringValue;
			
		}
		NSCharacterSet *trim = [NSCharacterSet whitespaceAndNewlineCharacterSet];
		_id = [[newsId stringByTrimmingCharactersInSet:trim] retain];
		_newsLink = [[link stringByTrimmingCharactersInSet:trim]retain];
		content = [content stringByTrimmingCharactersInSet:trim];
		title = [title stringByTrimmingCharactersInSet:trim];
		if ([content compare:@""]!= NSOrderedSame) {
            
            BOOL flag = YES;
            if ([self.delegate respondsToSelector:@selector(shouldDisplayNewsBlast)]) {
                flag = [self.delegate shouldDisplayNewsBlast];
            }
            if (!_canShowAlert && flag) {
                return;
            }
            
			if ([_newsLink compare:@"" ]== NSOrderedSame) {
				_alertView = [[UIAlertView alloc] initWithTitle:title message:content delegate:nil cancelButtonTitle:NSLocalizedString(@"OK",nil) otherButtonTitles:nil];
			}else {
				_alertView = [[UIAlertView alloc] initWithTitle:title message:content delegate:nil cancelButtonTitle:NSLocalizedString(@"Cancel",nil) otherButtonTitles:NSLocalizedString(@"OK",nil),nil];
			}
			_alertView.delegate = self;
			[_alertView show];
            [_alertView release];
            
            [[NSNotificationCenter defaultCenter] postNotificationName:kNewsBlastServedNotification object:self];
            if ([self.delegate respondsToSelector:@selector(viewDidShow:)]) {
                [self.delegate viewDidShow:self];
            }
		}else {
            
            _hasRequestedNews = NO;
            NSLog(@"没有可以显示的内容");
            if (_delegate && [_delegate respondsToSelector:@selector(viewDidNotShow:)]) {
                [_delegate viewDidNotShow:self];
            }
        }
		
        /*
        //  anonymous大神以前的处理方式，先不去掉
		// 处理nsuserDefault中的newsId
		if (nil == userDefaults) {
			userDefaults = [NSUserDefaults standardUserDefaults];
		}
		NSString* news_viewed = [userDefaults objectForKey:KEY_NEWSID_VIEWED];
		if (nil == news_viewed) {
			news_viewed = @"";
		}
		news_viewed = [news_viewed stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
		if ([news_viewed isEqualToString:@""]) {
			news_viewed = [NSString stringWithFormat:@"%@",_id];
		}else {
			news_viewed = [NSString stringWithFormat:@"%@,%@", news_viewed, _id];
		}
		[userDefaults setObject:news_viewed forKey:KEY_NEWSID_VIEWED];
         */
        
        //
        //  更改后的处理方式
        //  
        NSString *news_viewed_str = [[NSUserDefaults standardUserDefaults] objectForKey:KEY_NEWSID_VIEWED];
        NSArray *news_viewed_arr = [news_viewed_str componentsSeparatedByString:@","];
        NSMutableArray *news_viewed_arr_filter = [NSMutableArray arrayWithCapacity:10];
        for (NSString *news_id in news_viewed_arr) {
            //  filter nil or "" strings
            if (news_id == nil || [[news_id stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] length] < 1) {
                continue;
            }
            if ([news_viewed_arr_filter containsObject:news_id] == NO) {
                [news_viewed_arr_filter addObject:news_id];
            }
        }
        NSMutableString *news_viewed = [NSMutableString string];
        for (NSString *news_id in news_viewed_arr_filter) {
            [news_viewed appendFormat:@"%@,", news_id];
        }
        [[NSUserDefaults standardUserDefaults] setObject:news_viewed forKey:KEY_NEWSID_VIEWED];
        
//		NSLog(@"news_viewed:%@   newsId:%@", news_viewed, _id);
	}
	
}

#pragma mark NSURLConnection delegate Method
- (void)connection:(NSURLConnection*)connection didReceiveData:(NSData*)data {
    //NSLog(@"connection: %d",[connection retainCount]);
    //NSLog(@"%@",[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
    [_data appendData:data];
}

- (void)connectionDidFinishLoading:(NSURLConnection*)connection {
    
    //NSLog(@"finish: %d",[connection retainCount]);
	//NSLog(@"%@",[[NSString alloc] initWithData:_data encoding:NSUTF8StringEncoding]);
    self.connection = nil;
	[self processNews];
}

-(void)connection: (NSURLConnection *) connection didFailWithError: (NSError *) error{
    NSLog(@"connection error %@" ,error);
    self.connection = nil;
    _hasRequestedNews = NO;
    if (_delegate && [_delegate respondsToSelector:@selector(viewDidNotShow:)]) {
        [_delegate viewDidNotShow:self];
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    _hasRequestedNews = NO;
    
	if (buttonIndex == 1 && nil!=_newsLink && [_newsLink compare:@""]!=NSOrderedSame) {
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:_newsLink]];
		[_newsLink release];
		_newsLink = nil;
		if (nil!=_id && [_id compare:@""]!=NSOrderedSame) {
			NSString* _trackURL = [NSString stringWithFormat:@"%@&id=%@",self.serverPath,_id];
			NSURLRequest *request = [[NSURLRequest alloc] initWithURL: [NSURL URLWithString:_trackURL]];
			NSURLConnection *conn = [[NSURLConnection alloc] initWithRequest:request delegate:nil];
			[conn release];
			[request release];
		}
        
        // 添加一个通知
        [[NSNotificationCenter defaultCenter] postNotificationName:kNewsBlastClickOKNotification object:self];
        if (_delegate && [_delegate respondsToSelector:@selector(viewDidClickOK:)]) {
            [_delegate viewDidClickOK:self];
        }
	}else {
        
        // 添加一个通知
        if ( alertView.numberOfButtons == 1 ) {
            [[NSNotificationCenter defaultCenter] postNotificationName:kNewsBlastClickOKNotification object:self];
        } else {
            [[NSNotificationCenter defaultCenter] postNotificationName:kNewsBlastClickCancelNotification object:self];
        }
        
        // 添加一个通知
//        [[NSNotificationCenter defaultCenter] postNotificationName:kNewsBlastClickCancelNotification object:self];
        
        /// canceled delegate
        if (_delegate && [_delegate respondsToSelector:@selector(viewDidClickCancel:)]) {
            [_delegate viewDidClickCancel:self];
        }
    }
}
@end
