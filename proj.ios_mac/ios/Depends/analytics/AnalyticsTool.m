//
//  AnalyticsTool.m
//  Central_Analytics
//
//  Created by jianghai on 4/9/14.
//  Copyright (c) 2014 jianghai. All rights reserved.
//

#import "AnalyticsTool.h"
#import "OpenUDID.h"
#import <CommonCrypto/CommonDigest.h>

#define EVENT_MOREGAME_CLICK @"moregame_click"
#define EVENT_MOREGAME_CLOSE @"moregame_close"
#define EVENT_NEWSBLAST_OK  @"newsblast_ok"
#define EVENT_NEWSBLAST_CANCEL @"newsblast_cancel"
#define EVENT_NEWSBLAST_SERVED @"newsblast_served"

#define IsUPLOADING @"isuploading"
#define INSTALL @"isfirst"
#define INSTALL_DATE @"installdate"

#define DidCallEnterBackground @"HadCallEnterBackground"


#define ServedTime @"serverTime"
#define localTime_getServer @"localTime_getServer"

@interface AnalyticsTool ()
{
    BOOL _isUploading;
}
@property (nonatomic, retain) SKProductsRequest *productRequest;
@end

@implementation AnalyticsTool
@synthesize productRequest,session_start,
install_date,moregame_served;

+ (AnalyticsTool *)sharedTool
{
    static AnalyticsTool *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (!instance) {
            instance = [[AnalyticsTool alloc] init];
            [[SKPaymentQueue defaultQueue] addTransactionObserver:instance];    //观察是否往队列里添加了产品
        }
    });
    return instance;
}
- (id)init {
    
    self = [super init];
    if (self) {
        
        _isUploading = NO;
        moregame_served = self.newsblast_served = 0;
        [[NSUserDefaults standardUserDefaults] setBool:NO forKey:DidCallEnterBackground];
        [[NSUserDefaults standardUserDefaults] setBool:NO forKey:IsUPLOADING];
        if(![[NSUserDefaults standardUserDefaults] boolForKey:INSTALL]){
            
            [[NSUserDefaults standardUserDefaults] setBool:YES forKey:INSTALL];
            install_date = [self getCurrentTime];
            [[NSUserDefaults standardUserDefaults] setDouble:install_date forKey:INSTALL_DATE];
        }else{
            install_date =(long long)[[NSUserDefaults standardUserDefaults] doubleForKey:INSTALL_DATE];
        }
        //Application 进入前台添加一个观察者，因为无法去取得appdelegate里面的方法，只好用通知来处理。
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(ApplicationEnterForeground) name:UIApplicationWillEnterForegroundNotification object:nil];
        //Application 进入后台
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(ApplicationEnterBackground) name:UIApplicationDidEnterBackgroundNotification object:nil];
//        //Application 进入中断
//        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(ApplicationWillTerminate) name:UIApplicationWillTerminateNotification object:nil];
        
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(moreGameClicked) name:EVENT_MOREGAME_CLICK object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(moreGameClose) name:EVENT_MOREGAME_CLOSE object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newsblastOK) name:EVENT_NEWSBLAST_OK object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newsblastCancel) name:EVENT_NEWSBLAST_CANCEL object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(newsblastServed) name:EVENT_NEWSBLAST_SERVED object:nil];
    }
    return self;
}
-(void)dealloc
{
    //移除观察者
    [[NSNotificationCenter defaultCenter] removeObserver:self name:EVENT_MOREGAME_CLICK object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:EVENT_MOREGAME_CLOSE object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:EVENT_NEWSBLAST_OK object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:EVENT_NEWSBLAST_CANCEL object:nil];
    
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [super dealloc];
}
- (void)StartSession
{
    
    self.SengData = YES;
    [self StartSessionWithSentFile:YES];
}
- (void)StartSessionWithSentFile:(BOOL)sendData
{
//    if (![self isNetWorkAvailable]) return;
    
    self.SengData = sendData;
    
    session_start = [self getCurrentTime];
    self.SessionID = [self CreateSessionID];
    
    [self setNetwokTime];
}

#pragma mark privateMethod
-(NSString*)getCountry
{
    NSLocale *locale = [NSLocale currentLocale];
    NSString *countryCode = [locale objectForKey: NSLocaleCountryCode];
    return countryCode;
}

- (long long)getCurrentTime
{
    NSDate *date = [NSDate date];
    long long time=[date timeIntervalSince1970]*1000;
    
    //格式化对象
//    NSDateFormatter *formater=[[NSDateFormatter alloc] init];
//    
//    [formater setDateFormat:@"yyyy/MM/dd HH:mm"];
//    
//    NSString *dateStr=[formater stringFromDate:date];
//    [formater release];
    
    return time;
}

-(long long)formatHttpDate:(NSString*)date{
    
    NSArray *format = [date componentsSeparatedByString:@" "];
    //日期格式化工具
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    [dateFormatter setTimeZone:[NSTimeZone timeZoneForSecondsFromGMT:0]];
    //字符串构造NADate
    NSArray *monthSysmbols=@[@"Jan",@"Feb",@"Mar",@"Apr",@"May",@"Jun",@"Jul",@"Aug",@"Sep",@"Oct",@"Nov",@"Dec"];
    
    int month = 0 ;
    for (int i=0; i<[monthSysmbols count]; i++) {
        NSString *st1 = [format objectAtIndex:2];
        NSString *st2 = [monthSysmbols objectAtIndex:i];
        if([st1 isEqualToString:st2])
        {
            month = i+1;
        }
    }
    NSDate *serverDate = [dateFormatter dateFromString:[NSString stringWithFormat:@"%@-%d-%@ %@",[format objectAtIndex:3],month,[format objectAtIndex:1],[format objectAtIndex:4]]];
    long long temp = [serverDate timeIntervalSince1970]*1000;
    return temp;
}

-(void)setNetwokTime
{
    // 初始化目标地址的URL
    NSArray* components = [[self getBundleIdentifier] componentsSeparatedByString:@"."];
    NSAssert([components count] == 3, @"不正确的bundle id");
    
    NSString *strURL=[NSString stringWithFormat:@"http://services.%@.%@",[components objectAtIndex:1], [components objectAtIndex:0]];
    
    [NSURLConnection sendAsynchronousRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:strURL]]
                                       queue:[NSOperationQueue mainQueue]
                           completionHandler:^(NSURLResponse *response, NSData *data, NSError *connectionError) {
                               long long service_time = 0;
                               if ( !connectionError ) {
                                   // 成功拿到时间
                                   NSHTTPURLResponse* httpResp = (NSHTTPURLResponse *)response;
                                   NSDictionary* headers = [httpResp allHeaderFields];
                                   
//                                   NSDateFormatter* df = [[[NSDateFormatter alloc] init] autorelease];
//                                   df.dateFormat = @"EEE, dd MM yyyy HH:mm:ss z";
//                                   NSDate* date = [df dateFromString:[headers objectForKey:@"Date"]];
//                                   service_time = [date timeIntervalSince1970] * 1000;
                                   service_time = [self formatHttpDate:[headers objectForKey:@"Date"]];
                               } else {
//                                   service_time = [self getCurrentTime];
                               }
                               
                               NSString* serverTimes = [[NSUserDefaults standardUserDefaults] stringForKey:@"serverTimes"];
                               long long tempTime = service_time;
                               if ( tempTime == 0 ) {
                                   tempTime = [self getCurrentTime];
                               }
                               
                               [[NSUserDefaults standardUserDefaults] setObject:[NSString stringWithFormat:@"%lld",tempTime] forKey:@"csvFileName"];
                               
                               if ( [serverTimes length] == 0 ) {
                                   serverTimes = [NSString stringWithFormat:@"%lld",tempTime];
                               } else {
                                   serverTimes = [NSString stringWithFormat:@"%@,%lld", serverTimes, tempTime];
                               }
                               
                               [[NSUserDefaults standardUserDefaults] setObject:serverTimes forKey:@"serverTimes"];
                               [[NSUserDefaults standardUserDefaults] synchronize];
                               
#if DEBUG
                               NSLog(@"serverTimes:%@", serverTimes);
#endif
                               
                               if ( service_time == 0 ) {
                                   [[NSUserDefaults standardUserDefaults] setObject:@"" forKey:ServedTime];
                               } else {
                                   [[NSUserDefaults standardUserDefaults] setObject:[NSString stringWithFormat:@"%lld",service_time] forKey:ServedTime];
                               }
                               [[NSUserDefaults standardUserDefaults] setObject:[NSString stringWithFormat:@"%lld",[self getCurrentTime]] forKey:localTime_getServer];
                               
                               [self SaveEventWithTime:[self getCurrentTime] EventName:@"session_start" AndEventValue:nil];

                           }];
}
-(long long)getCurrentNetWorkTime
{
    NSString *server_str = [[NSUserDefaults standardUserDefaults] objectForKey:ServedTime];
    NSString *local_str = [[NSUserDefaults standardUserDefaults] objectForKey:localTime_getServer];
    long long server_time = [server_str longLongValue];
    long long local_time = [local_str longLongValue];

    return server_time+([self getCurrentTime]-local_time);
}

-(NSString*)getAppVersion
{
    NSString *version =[[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleVersionKey];
    return version;
}
-(NSString*)getBundleIdentifier
{
    return [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleIdentifierKey];
}
- (BOOL)isNetWorkAvailable
{
    SCNetworkReachabilityFlags flags;
    BOOL receivedFlags;
    SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithName(CFAllocatorGetDefault(), [@"google.com" UTF8String]);
    receivedFlags = SCNetworkReachabilityGetFlags(reachability, &flags);
    CFRelease(reachability);
    if (!receivedFlags || (flags == 0) )
    {
        return NO;
    } else {
        return YES;
    }
}
#pragma mark DeviceInfo
-(NSString*)getDeviceModel
{
    return [[UIDevice currentDevice] model];
}
-(NSString*)getFirmwareVersion
{
    NSString *mode = [[self getDeviceModel] stringByAppendingString:@" "];
    return [mode stringByAppendingString:[[UIDevice currentDevice] systemVersion]];
}
-(NSString*)getCarrier
{
    
    CTTelephonyNetworkInfo *netinfo = [ [ [CTTelephonyNetworkInfo alloc] init] autorelease];
	CTCarrier *carrier = [netinfo subscriberCellularProvider];
    
    if(![self isNetWorkAvailable])
        return @"";
    if ([carrier.carrierName isEqualToString:@""]){
        if([self isNetWorkAvailable]){
            NSString *name = [NSString stringWithFormat:@"WIFI/Other(%@)",[self getCountry]];
            return name;
        }
    }
    SCNetworkReachabilityFlags flags;
    BOOL receivedFlags;
    SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithName(CFAllocatorGetDefault(), [@"google.com" UTF8String]);
    receivedFlags = SCNetworkReachabilityGetFlags(reachability, &flags);
    if((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN){
        CFRelease(reachability);
        return [NSString stringWithFormat:@"\"%@\"",carrier.carrierName];//取出的运营商为中文的时候容易乱码，加上引号是为了当其中出现逗号的时候不会破坏文件的结构
    }
    if([[[UIDevice currentDevice] model] isEqualToString:@"iPhone"])
        return [NSString stringWithFormat:@"\"Wifi/%@\"",carrier.carrierName];
    return @"Wifi";
}
-(NSString*)getLanguage
{
   return [[NSLocale preferredLanguages] objectAtIndex:0];
}
-(NSString*)getTimeZone
{
    NSTimeZone *local=[NSTimeZone systemTimeZone];
    float offset = ([local secondsFromGMT]/1800)/2.0;
    
    if(offset>=0){
        int flag = offset/0.5;
        if(flag%2==0)
            return [NSString stringWithFormat:@"+%d:00",(int)offset];
        else
            return [NSString stringWithFormat:@"+%d:30",(int)(offset-0.5)];
    }else{
        int flag = offset/0.5;
        if(flag%2==0)
            return [NSString stringWithFormat:@"%d:00",(int)offset];
        else
            return [NSString stringWithFormat:@"%d:30",(int)(offset+0.5)];
    }
    
}

/*#pragma mark - SKProductsRequestDelegate

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    
    self.productRequest=nil;
    // 最后一个产品
    SKProduct *curProduct=[[response products] lastObject];
    // 产品不存在
    NSString *info=[NSString stringWithFormat:@"\"%@,%@\"",curProduct.productIdentifier,curProduct.price];
    [self SaveEventWithTime:[self getCurrentTime] EventName:@"Iap_purchase" AndEventValue:info];
}*/
#pragma mark - SKPaymentTransactionObserver

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    for(SKPaymentTransaction *transaction in transactions) {
        switch(transaction.transactionState){
            case SKPaymentTransactionStatePurchased:{
                //获取解锁产品的信息-------------not need
//                self.productRequest = [[[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:transaction.originalTransaction.payment.productIdentifier]] autorelease];
//                self.productRequest.delegate = self;
//                [self.productRequest start];
                
                NSString* productName = [[transaction.payment.productIdentifier componentsSeparatedByString:@"."] objectAtIndex:3];
                NSString *value=nil;
                //判断服务器上该iap是否购买
                if(transaction.originalTransaction == nil)
                {
//                    NSLog(@"________________购买");
                    value = [NSString stringWithFormat:@"\"%@,result_succeed\"",productName];
                }else{
//                    NSLog(@"________________购买免费");
                    value = [NSString stringWithFormat:@"\"%@,result_succeed,free\"",productName];
                }
                //如果本地不存在产品的购买信息，才将购买操作记录，防止因为网络问题出现的重复记录问题
                if(![[NSUserDefaults standardUserDefaults] boolForKey:transaction.payment.productIdentifier])
                {
                    [self SaveEventWithTime:[self getCurrentTime] EventName:@"IAP" AndEventValue:value];
                    [[NSUserDefaults standardUserDefaults] setBool:YES forKey:transaction.payment.productIdentifier];
                }
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                break;
                
            }case SKPaymentTransactionStateRestored:{
                
                NSLog(@"abcd");
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
                break;
            }case SKPaymentTransactionStateFailed:{
                //  user canceled
                if (transaction.error.code == SKErrorPaymentCancelled)
                {
                     NSString* productName = [[transaction.payment.productIdentifier componentsSeparatedByString:@"."] objectAtIndex:3];
                    NSString *value = [NSString stringWithFormat:@"\"%@,result_cancelled\"",productName];
                    [self SaveEventWithTime:[self getCurrentTime] EventName:@"IAP" AndEventValue:value];
                    
                }else{
                     NSString* productName = [[transaction.payment.productIdentifier componentsSeparatedByString:@"."] objectAtIndex:3];
                    NSString *value = [NSString stringWithFormat:@"\"%@,result_error\"",productName];
                    [self SaveEventWithTime:[self getCurrentTime] EventName:@"IAP" AndEventValue:value];
                }
                //  ui refresh
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
                break;
            }
        }
    }
}

//restore失败
- (void) paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error {
    
    if (error.code == SKErrorPaymentCancelled) {
        NSString *value = [NSString stringWithFormat:@"\"restore,result_cancelled\""];
        [self SaveEventWithTime:[self getCurrentTime] EventName:@"IAP" AndEventValue:value];
    }else {
        //  restore failed
        NSString *value = [NSString stringWithFormat:@"\"restore,result_error\""];
        [self SaveEventWithTime:[self getCurrentTime] EventName:@"IAP" AndEventValue:value];
    }
    
    //  request end
}
//restore成功
- (void) paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    NSString *value = [NSString stringWithFormat:@"\"restore,result_succeed\""];
    [self SaveEventWithTime:[self getCurrentTime] EventName:@"IAP" AndEventValue:value];
}

#pragma mark - sessionID/user_ID生成
-(NSString*)CreateSessionID
{
    NSString *sessionID=[NSString stringWithFormat:@"%lld%@%@",[self getCurrentTime],[self getBundleIdentifier],[self getUserID]];
    
    return [self sha1:sessionID];
    //创建sessionID的方式：当前时间+bundleID+userID，拼接后用sha-1生成摘要，如此处理，session重复的可能性极小，userID用OPenUDID生成。
}
-(NSString*)getUserID
{
    return [OpenUDID value];
    
}
#pragma mark - CSV文件操作

- (NSString *)GetfilePath {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
//    return [documentsDirectory stringByAppendingPathComponent:@"file.csv"];
    return [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.csv", [[NSUserDefaults standardUserDefaults] objectForKey:@"csvFileName"]]];
}

- (void)SaveEventWithTime:(long long)time EventName:(NSString*)eventName AndEventValue:(NSString*)value
{
    if(value==nil)
        value=@"";
    
    if(![[NSFileManager defaultManager] fileExistsAtPath:[self GetfilePath]]){
        //不存在，创建csv文件
        [[NSFileManager defaultManager] createFileAtPath: [self GetfilePath] contents:nil attributes:nil];
    }
    NSString *str =  [[NSUserDefaults standardUserDefaults] objectForKey:ServedTime];
    NSString *NET_TIME;
    if(str.length > 0)
        NET_TIME = [NSString stringWithFormat:@"%lld",[self getCurrentNetWorkTime]];
    else
        NET_TIME = @"";
    
    NSMutableString *writeString = [NSMutableString stringWithCapacity:0];
    [writeString appendString:[NSString stringWithFormat:@"%@,%@,%@,%@,%@,%@,%@,%@,%@,%lld,%@,%@,%lld,%@,%@,%@\n",[self getBundleIdentifier],@"IOS",[self getAppVersion],[self getUserID],self.SessionID,[self getCountry],[self getDeviceModel],[self getCarrier],[self getFirmwareVersion],install_date,[self getLanguage],NET_TIME,time,[self getTimeZone],eventName,value]];
    
    NSFileHandle *handle;
    handle = [NSFileHandle fileHandleForWritingAtPath: [self GetfilePath]];
    [handle truncateFileAtOffset:[handle seekToEndOfFile]];
    [handle writeData:[writeString dataUsingEncoding:NSUTF8StringEncoding]];
}

#pragma mark 发送文件
-(void)uploadfile
{
    if ( _isUploading ) {
        return;
    }
    
    _isUploading = YES;
    
    UIApplication *app = [UIApplication sharedApplication];
    _bgTask = [app beginBackgroundTaskWithExpirationHandler:^{//按Home退出，系统会立即停止app，所以必须要在后台处理，这样才能保证上传的成功。
        [app endBackgroundTask:_bgTask];
        _bgTask = UIBackgroundTaskInvalid;
    }];
    
    // 初始化目标地址的URL
    NSArray* components = [[self getBundleIdentifier] componentsSeparatedByString:@"."];
    
    NSString *strURL=[NSString stringWithFormat:@"http://services.%@.%@/analytics/csv_merge/upload/v1.8/",[components objectAtIndex:1], [components objectAtIndex:0]];
    strURL = [strURL stringByAddingPercentEscapesUsingEncoding: NSUTF8StringEncoding];
    NSURL *serverURL=[NSURL URLWithString:strURL];
    
    NSMutableURLRequest* request = [NSMutableURLRequest requestWithURL:serverURL];
    [request setHTTPMethod:@"POST"];
    [request setValue:@"multipart/form-data" forHTTPHeaderField:@"Content-Type"];
    
    //获得文件大小
    NSArray* fileNames = [[[NSUserDefaults standardUserDefaults] objectForKey:@"serverTimes"] componentsSeparatedByString:@","];
    
    if ( [fileNames count] == 0 ) {
        return;
    }
    
    NSMutableData* tmpData = [NSMutableData data];
    for (NSString *file in fileNames) {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        NSString* filePath = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.csv", file]];
        NSData *data = [NSData dataWithContentsOfFile:filePath];
        [tmpData appendData:data];
    }
    
    [request setValue:[NSString stringWithFormat:@"%ud", [tmpData length]] forHTTPHeaderField:@"Content-Length"];
    
    [request setHTTPBody:tmpData];
    
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue]
                           completionHandler:^(NSURLResponse *response, NSData *data, NSError *connectionError) {
                               _isUploading = NO;
                               NSLog(@"result:%@", [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding]);
                               if ( !connectionError ) {
                                   NSHTTPURLResponse *HTTP_response=(NSHTTPURLResponse*)response;
                                   if(HTTP_response.statusCode == 200)
                                   {
                                       NSLog(@"success!");
                                       NSArray* newFileNames = [[[NSUserDefaults standardUserDefaults] objectForKey:@"serverTimes"] componentsSeparatedByString:@","];
                                       
                                       NSMutableArray* temp = [NSMutableArray arrayWithArray:newFileNames];
                                       for (NSString* file in fileNames) {
                                           NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
                                           NSString *documentsDirectory = [paths objectAtIndex:0];
                                           NSString* filePath = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.csv", file]];
                                           [[NSFileManager defaultManager] removeItemAtPath:filePath error:nil];
                                           [temp removeObject:file];
                                       }
                                       
                                       if ( temp > 0 ) {
                                           [[NSUserDefaults standardUserDefaults] setObject:[temp componentsJoinedByString:@","] forKey:@"serverTimes"];
                                       } else {
                                           [[NSUserDefaults standardUserDefaults] setObject:@"" forKey:@"serverTimes"];
                                       }
                                       
                                       [[NSUserDefaults standardUserDefaults] synchronize];
                                       
                                       if (_bgTask != UIBackgroundTaskInvalid) {
                                           [[UIApplication sharedApplication] endBackgroundTask:_bgTask];
                                           _bgTask = UIBackgroundTaskInvalid;
                                       }
                                   }
                                   else
                                   {
                                       NSLog(@"field!");
                                   }
                               } else {
                                   NSLog(@"upload error: %@",connectionError);
                               }
                           }];
}

- (NSString*)sha1:(NSString*)input
{
    const char *cstr = [input cStringUsingEncoding:NSUTF8StringEncoding];
    NSData *data = [NSData dataWithBytes:cstr length:input.length];
    
    uint8_t digest[CC_SHA1_DIGEST_LENGTH];
    
    CC_SHA1(data.bytes, data.length, digest);
    
    NSMutableString* output = [NSMutableString stringWithCapacity:CC_SHA1_DIGEST_LENGTH * 2];
    
    for(int i = 0; i < CC_SHA1_DIGEST_LENGTH; i++)
        [output appendFormat:@"%02x", digest[i]];
    return output;
}

#pragma mark moregame Observer
//点击moregame
-(void)moreGameClicked
{
    moregame_served = [self getCurrentTime];
    NSString *value =@"";
    [self SaveEventWithTime:[self getCurrentTime] EventName:@"more_game_clicked" AndEventValue:value];
}
-(void)moreGameClose
{
    NSString *value = [NSString stringWithFormat:@"\"closed,%lld\"",[self getCurrentTime]-moregame_served];
    [self SaveEventWithTime:[self getCurrentTime] EventName:@"more_game_served" AndEventValue:value];
    moregame_served = 0;
}
#pragma mark newsblast Observer
//收到newblast相关本地通知的处理
-(void)newsblastOK
{
    NSString *value = [NSString stringWithFormat:@"\"OK,%lld\"",[self getCurrentTime]-self.newsblast_served];
    [self SaveEventWithTime:[self getCurrentTime] EventName:@"news_blast_clicked" AndEventValue:value];
}
-(void)newsblastCancel
{
    NSString *value = [NSString stringWithFormat:@"\"cancel,%lld\"",[self getCurrentTime]-self.newsblast_served];
    [self SaveEventWithTime:[self getCurrentTime] EventName:@"news_blast_clicked" AndEventValue:value];
}
-(void)newsblastServed
{
    self.newsblast_served = [self getCurrentTime];
    [self SaveEventWithTime:[self getCurrentTime] EventName:@"news_blast_served" AndEventValue:nil];
}
#pragma mark 程序进入后台/前台处理
-(void)ApplicationEnterForeground
{
    [self StartSessionWithSentFile:self.SengData];
}

-(void)ApplicationEnterBackground
{
    [self SaveEventWithTime:[self getCurrentTime] EventName:@"session_end" AndEventValue:nil];
    if(self.SengData)
        [self uploadfile];
}

@end
