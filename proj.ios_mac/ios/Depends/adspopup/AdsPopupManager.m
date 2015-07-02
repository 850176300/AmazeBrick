//
//  AdsPopupManager.m
//
//  Created by tang.wei on 13-11-8.
//  Copyright (c) 2013年 yixing. All rights reserved.
//

#import "AdsPopupManager.h"
#import "NewsBlast.h"
#import "MPInterstitialAdController.h"
#import "MPAdView.h"
#import <Chartboost/Chartboost.h>
#import "AppConfigs.h"

///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - BannerContainer class
///////////////////////////////////////////////////////////////////////////////////////////////
/********************** 此类用于处理UITouch向下传递的问题 **************************/
@interface BannerContainer : UIView

@end

@implementation BannerContainer

- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame]) {
        
    }
    
    return self;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {}
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {}
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {}
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {}

@end

@interface InterstitialWrapper : NSObject

@property (nonatomic, retain) MPInterstitialAdController* interstitialAd;
@property (nonatomic, assign) id<AdsPopupManagerDelegate> delegate;
@property (nonatomic, assign) UIViewController *viewController;
@property (nonatomic, assign) InterstitialAdType adType;

- (void)loadInterstitial;
- (BOOL)showInterstitial;
- (void)cancelShowInterstitial;

- (BOOL)interstitialAdIsShowing;

@end

@interface InterstitialWrapper () <MPInterstitialAdControllerDelegate>
{
    BOOL _interstitialIsShowing;
}

@end

@implementation InterstitialWrapper

- (id)init
{
    if ( self = [super init] ) {
        _interstitialIsShowing = NO;
        self.adType=InterstitialAdTypeDefault;
    }
    return self;
}

- (BOOL)interstitialAdIsShowing
{
    return _interstitialIsShowing;
}

- (void)loadInterstitial
{
    self.interstitialAd.delegate = self;
    if(!self.interstitialAd.ready){
        [self.interstitialAd loadAd];
    }
}

- (BOOL)showInterstitial
{
    if ( _interstitialIsShowing ) {
        return YES;
    }
    
    if ( self.interstitialAd.ready ) {
        _interstitialIsShowing = YES;
        [self.interstitialAd showFromViewController:self.viewController];
        return YES;
    }
    [self loadInterstitial];
    return NO;
}

- (void)cancelShowInterstitial
{
    _interstitialIsShowing = NO;
    UIWindow *window = [[[UIApplication sharedApplication] windows] objectAtIndex:0];
    for (UIView *view in [window subviews]) {
        if ([view isKindOfClass:NSClassFromString(@"CBNativeInterstitialView")]) {
            [view performSelector:@selector(close:) withObject:nil];
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - interstitial delegate
///////////////////////////////////////////////////////////////////////////////////////////////
- (void)interstitialDidLoadAd:(MPInterstitialAdController *)interstitial
{
    
    if ( [self.delegate respondsToSelector:@selector(interstitialDidLoad:)] ) {
        [self.delegate interstitialDidLoad:self.adType];
    }
}

- (void)interstitialDidFailToLoadAd:(MPInterstitialAdController *)interstitial
{
    if ( [self.delegate respondsToSelector:@selector(interstitialDidFailToLoad:)] ) {
        [self.delegate interstitialDidFailToLoad:self.adType];
    }
}

- (void)interstitialDidExpire:(MPInterstitialAdController *)interstitial
{
    _interstitialIsShowing = NO;
}

- (void)interstitialWillAppear:(MPInterstitialAdController *)interstitial
{
    
}

- (void)interstitialDidAppear:(MPInterstitialAdController *)interstitial
{
    //_interstitialIsShowing = YES;
    if ([self.delegate respondsToSelector:@selector(interstitialDidShow:)]) {
        [self.delegate interstitialDidShow:self.adType];
    }
}

- (void)interstitialWillDisappear:(MPInterstitialAdController *)interstitial
{
    
}

- (void)interstitialDidDisappear:(MPInterstitialAdController *)interstitial
{
    _interstitialIsShowing = NO;
    
    if ([self.delegate respondsToSelector:@selector(interstitialDidDismiss:)]) {
        [self.delegate interstitialDidDismiss:self.adType];
    }
    
    [self loadInterstitial];
}


@end

///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - AdsPopupManager class
///////////////////////////////////////////////////////////////////////////////////////////////
@interface AdsPopupManager () <MPAdViewDelegate, MPInterstitialAdControllerDelegate>
{
    BOOL    _newsBlastIsShowing;
    
    CGFloat         _bannerHeight;
    BOOL            _bannerIsShowing;
    
    BannerContainer *_container;
    BOOL            _bannerHasLoaded;
    
    NSMutableDictionary* _interstitialAdControllers;
}

// 横幅广告
@property (nonatomic, retain) MPAdView *adView;

// 方块广告
@property (nonatomic, retain) MPAdView *rectADView;

@end

@implementation AdsPopupManager

@synthesize viewController = _viewController, delegate = _delegate, adView, rectADView;
@synthesize bannerAdPosition = _bannerAdPosition;

+ (AdsPopupManager *)sharedManager
{
    static AdsPopupManager *instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (!instance) {
            instance = [[AdsPopupManager alloc] init];
        }
    });
    return instance;
}

- (id)init
{
    if (self = [super init]) {
        _interstitalAdType = InterstitialAdTypeDefault;
        _bannerAdPosition = BannerAdPositionBottom;
    }
    return self;
}

// 因为不是严格的单例
// 如果用init初始化，那么需要手动管理内存
- (void)dealloc
{
    self.adView = nil;
    self.rectADView = nil;
    [_interstitialAdControllers release];
    [_container release];
    _container = nil;
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [super dealloc];
}

///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Private methods
///////////////////////////////////////////////////////////////////////////////////////////////
- (NSString *)getInterstitialAdsIdForType:(InterstitialAdType)type
{
    if ( type == InterstitialAdTypeDefault ) {
        return [self isIphone] ? IPHONE_FULLSCREEN_ID : IPAD_FULLSCREEN_ID;
    }
    
    return [self isIphone] ? IPHONE_FULLSCREEN_ID_CROSSPROMO : IPAD_FULLSCREEN_ID_CROSSPROMO;
}

- (InterstitialWrapper *)getInterstitalWrapperForType:(InterstitialAdType)type
{
    if ( !_interstitialAdControllers ) {
        _interstitialAdControllers = [[NSMutableDictionary alloc] init];
    }
    
    NSString* interstitialAdId = [self getInterstitialAdsIdForType:type];
    
    InterstitialWrapper* wrapper = [_interstitialAdControllers objectForKey:interstitialAdId];
    if ( !wrapper ) {
        wrapper = [[InterstitialWrapper alloc] init];
        wrapper.adType=type;
        [_interstitialAdControllers setObject:wrapper forKey:interstitialAdId];
        [wrapper release];
    }
    
    wrapper.viewController = self.viewController;
    
    return wrapper;
}

- (void)loadInterstitialForType:(InterstitialAdType)type
{
    NSString* interstitialId = [self getInterstitialAdsIdForType:type];
    if ( interstitialId.length <= 0 ) {
        return;
    }
    
    NSLog(@"加载全屏:%@", interstitialId);
    
    InterstitialWrapper* wrapper = [self getInterstitalWrapperForType:type];
    
    wrapper.interstitialAd = [MPInterstitialAdController interstitialAdControllerForAdUnitId:interstitialId];
    [wrapper setDelegate:self.delegate];
    
    [wrapper loadInterstitial];
}

// 修改于2014-08-25
- (void)setDelegate:(id)delegate
{
    _delegate = delegate;
    
    for (id key in _interstitialAdControllers) {
        InterstitialWrapper* iw = [_interstitialAdControllers objectForKey:key];
        if ( iw ) {
            iw.delegate = _delegate;
        }
    }
}

- (void)loadBannerForID:(NSString *)bannerId
{
    if (!self.adView) {
        self.adView = [[[MPAdView alloc] initWithAdUnitId:bannerId
                                                     size:[self bannerSize]] autorelease];
        self.adView.delegate = self;
    }
    
    // 修改于2015-01-22 修复没显示banner，但是resume时会自动去拉广告内容
    self.adView.ignoresAutorefresh = YES;
    
    [self.adView loadAd];
}

- (CGSize)bannerSize
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
        return MOPUB_BANNER_SIZE;
    }
    return MOPUB_LEADERBOARD_SIZE;
}

- (CGRect)adViewFrame
{
    CGRect frame = self.adView.frame;
    CGSize size = [self bannerSize];//[self.adView adContentViewSize];
    frame.origin.x += (CGRectGetWidth([self getMainscreenBounds]) - size.width) / 2;
    // iOS7 状态条有问题
    if ([[[UIDevice currentDevice] systemVersion] compare:@"7.0" options:NSNumericSearch] == NSOrderedAscending) {
        frame.origin.y = _bannerAdPosition == BannerAdPositionTop ? 0.0 :
        CGRectGetHeight([self getMainscreenBounds]) - size.height;
    } else {
        frame.origin.y = _bannerAdPosition == BannerAdPositionTop ? 0.0 :
        CGRectGetHeight([self getMainscreenBounds]) - size.height + [self getStatusBarHeight];
    }
    
    return frame;
}

- (CGFloat)getStatusBarHeight
{
    if (UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation])) {
        return [[UIApplication sharedApplication] statusBarFrame].size.width;
    }
    
    return [[UIApplication sharedApplication] statusBarFrame].size.height;
}

- (CGRect)getMainscreenBounds
{
    CGRect frame = [[UIScreen mainScreen] applicationFrame];
    if (UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation])) {
        CGFloat width = MAX(frame.size.height, frame.size.width);
        CGFloat height = MIN(frame.size.height, frame.size.width);
        frame = CGRectMake(0, 0, width, height);
    }
    return frame;
}

- (UIWindow *)getWindow
{
    return [[[UIApplication sharedApplication] windows] objectAtIndex:0];
}

- (void)addBannerIfNeeded
{
    if (!self.adView.superview) {
        if (!_container) {
            _container = [[BannerContainer alloc] init];
            _container.userInteractionEnabled = NO;
        }
        
        
        _container.hidden = NO;
        
        if (!_container.superview) {
            [self.viewController.view addSubview:_container];
        }
        
        _container.frame = [self adViewFrame];
        self.adView.frame = _container.bounds;
        [_container addSubview:self.adView];
        
        _bannerIsShowing = YES;
    } else {
        if (_bannerHasLoaded)
            _container.userInteractionEnabled = YES;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Getter methods
///////////////////////////////////////////////////////////////////////////////////////////////
- (UIViewController *)viewController
{
    if (!_viewController) {
        _viewController = [[self getWindow] rootViewController];
    }
    NSAssert(!!_viewController, @"没有设置viewController,请先设置");
    return _viewController;
}

- (void)setViewController:(UIViewController *)viewController
{
    if (_viewController != viewController) {
        _viewController = viewController;
        
        // 移除重新添加
        [self.adView removeFromSuperview];
        [_container removeFromSuperview];
        
        //        [self showBannerAd];
    }
}

- (BOOL)isIphone
{
    return UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone;
}

///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Public methods
- (void)preloadAllAds
{
    // 加载全屏
    [self loadInterstitialForType:InterstitialAdTypeDefault];
    
    // 加载第2组全屏
    [self loadInterstitialForType:InterstitialAdTypeCrossPromo];
    
    // 加载横幅
    NSString *bannerId = [self isIphone] ? IPHONE_BANNER_ID : IPAD_BANNER_ID;
    if (bannerId.length > 0) {
        [self loadBannerForID:bannerId];
    }
    
    // 加载方块广告
    NSString *rectId = [self isIphone] ? IPHONE_MEDIUM_RECT_ID : IPAD_MEDIUM_RECT_ID;
    if (rectId.length > 0) {
        [self preloadMediumRectAdForId:rectId];
    }
}

- (void)preloadMediumRectAdForId:(NSString *)adsID
{
    if (!self.rectADView) {
        self.rectADView = [[[MPAdView alloc] initWithAdUnitId:adsID
                                                         size:MOPUB_MEDIUM_RECT_SIZE] autorelease];
        self.rectADView.delegate = self;
    }
    
    [self.rectADView loadAd];
}

- (void)showMediumRectAd
{
    CGPoint point = CGPointMake(CGRectGetWidth([self getMainscreenBounds]) * 0.5,
                                CGRectGetHeight([self getMainscreenBounds]) * 0.5);
    [self showMediumRectAdAtPoint:point];
}

- (void)showMediumRectAdAtPoint:(CGPoint)center
{
    if (!self.rectADView.superview) {
        [self.viewController.view addSubview:self.rectADView];
        self.rectADView.bounds = CGRectMake(0, 0, MOPUB_MEDIUM_RECT_SIZE.width, MOPUB_MEDIUM_RECT_SIZE.height);
    }
    
    self.rectADView.hidden = NO;
    self.rectADView.center = center;
    [self.viewController.view bringSubviewToFront:self.rectADView];
    
    [self.rectADView startAutomaticallyRefreshingContents];
}

// 设置广告的frame
- (void)showMediumRectAdAtFrame:(CGRect)frame
{
    if (!self.rectADView.superview) {
        [self.viewController.view addSubview:self.rectADView];
        self.rectADView.bounds = CGRectMake(0, 0, MOPUB_MEDIUM_RECT_SIZE.width, MOPUB_MEDIUM_RECT_SIZE.height);
    }
    
    self.rectADView.hidden = NO;
    self.rectADView.frame = frame;
    [self.viewController.view bringSubviewToFront:self.rectADView];
    
    [self.rectADView startAutomaticallyRefreshingContents];
}

- (void)hideMediumRectAd
{
    [self.rectADView stopAutomaticallyRefreshingContents];
    self.rectADView.hidden = YES;
}

- (void)removeMediumRectAd
{
    self.rectADView.delegate = nil;
    [self.rectADView removeFromSuperview];
    self.rectADView = nil;
}

- (void)showBannerAd
{
    
    [self addBannerIfNeeded];
    
    if (_bannerHasLoaded)
        _container.userInteractionEnabled = YES;
    
    _container.hidden = NO;
    [_container.superview bringSubviewToFront:_container];
    
    [self.adView startAutomaticallyRefreshingContents];
    
    _bannerHeight = [self.adView adContentViewSize].height;
    _bannerIsShowing = YES;
}

- (void)hideBannerAd
{
    _container.hidden = YES;
    _container.userInteractionEnabled = NO;
    
    [self.adView stopAutomaticallyRefreshingContents];
    
    _bannerHeight = 0.0;
    _bannerIsShowing = NO;
}

- (void)removeBannerAd
{
    [self.adView removeFromSuperview];
    [_container removeFromSuperview];
    self.adView.delegate = nil;
    self.adView = nil;
    
    [_container release];
    _container = nil;
    
    _bannerHeight = 0.0;
    _bannerIsShowing = NO;
    
    // 暂时对于全屏也这样处理
    // 不想增加更多接口
    //    self.interstitialController = nil;
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (CGFloat)bannerHeight { return _bannerHeight; }
- (BOOL)bannerIsShowing { return _bannerIsShowing; }

-(void)preloadshowInterstitialForType:(InterstitialAdType)adType{
    [self cancelInterstitialAdForType:adType];
    [[self getInterstitalWrapperForType:adType] loadInterstitial];
}
- (BOOL)showInterstitial
{
    return [self showInterstitialForType:InterstitialAdTypeDefault];
}

- (BOOL)showInterstitialForType:(InterstitialAdType)adType
{
    // 取消newsblast显示
    [[NewsBlast shareNews] cancelShowNewsBlast];
    
    //获取另一个广告
    InterstitialAdType type = adType == InterstitialAdTypeCrossPromo ? InterstitialAdTypeDefault : InterstitialAdTypeCrossPromo;
    
    // 取消其中一个全屏广告显示
    [self cancelInterstitialAdForType:type];
    
    // 如果有全屏广告正在显示,不再显示当前广告
    if ( [[self getInterstitalWrapperForType:type] interstitialAdIsShowing] ||
        [[self getInterstitalWrapperForType:adType] interstitialAdIsShowing] ) {
        NSLog(@"ad is showing");
        return YES;
    }
    
    NSLog(@"Showing %@ Fullscreen: %@", (adType == InterstitialAdTypeDefault ? @"Default" : @"Cross Promo"),
          [self getInterstitialAdsIdForType:adType]);
    
    // 显示当前全屏
    return [[self getInterstitalWrapperForType:adType] showInterstitial];
}

- (void)cancelInterstitialAdForType:(InterstitialAdType)type
{
    InterstitialWrapper* wrapper = [self getInterstitalWrapperForType:type];
    [wrapper cancelShowInterstitial];
}

- (void)dismissInterstitial
{
    UIWindow *window = [[[UIApplication sharedApplication] windows] objectAtIndex:0];
    for (UIView *view in [window subviews]) {
        if ([view isKindOfClass:NSClassFromString(@"CBNativeInterstitialView")]) {
            [view performSelector:@selector(close:) withObject:nil];
        }
    }
}
//
- (BOOL)interstitialIsShowing
{
    __block BOOL flag = YES;
    [_interstitialAdControllers enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
        InterstitialWrapper* wrapper = (InterstitialWrapper *)obj;
        if ( [wrapper interstitialAdIsShowing] ) {
            flag = NO;
            // 跳出循环
            *stop = YES;
        }
    }];
    
    return flag;
}

- (void)showNewsBlast
{
    [self showNewsBlast:InvokeModeLaunch];
}

- (void)showNewsBlastOnResume
{
    [self showNewsBlast:InvokeModeResume];
}

- (void)showNewsBlast:(InvokeMode)mode
{
    // 取消全屏显示
    [_interstitialAdControllers enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
        InterstitialWrapper* wrapper = (InterstitialWrapper *)obj;
        [wrapper cancelShowInterstitial];
    }];
    
    // 显示NewsBlast
    NSLog(@"Loading news blast");
    
    [[NewsBlast shareNews] setInvokeMode:mode];
    [[NewsBlast shareNews] setDelegate:self];
    [[NewsBlast shareNews] sendNews];
}

///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - newsblast delegate
///////////////////////////////////////////////////////////////////////////////////////////////
- (BOOL)shouldDisplayNewsBlast
{
    return ![self interstitialIsShowing];
}

- (void)viewDidShow:(NewsBlast *)newsBlast
{
    _newsBlastIsShowing = YES;
    if ([self.delegate respondsToSelector:@selector(newsblastDidShow)]) {
        [self.delegate newsblastDidShow];
    }
}

- (void)viewDidNotShow:(NewsBlast *)newsBlast
{
    _newsBlastIsShowing = NO;
    if ([self.delegate respondsToSelector:@selector(newsblastDidNotShow)]) {
        [self.delegate newsblastDidNotShow];
    }
}

- (void)viewDidClickCancel:(NewsBlast *)newsBlast
{
    _newsBlastIsShowing = NO;
    if ([self.delegate respondsToSelector:@selector(newsblastDidClickCancel)]) {
        [self.delegate newsblastDidClickCancel];
    }
}

- (void)viewDidClickOK:(NewsBlast *)newsBlast
{
    _newsBlastIsShowing = NO;
    if ([self.delegate respondsToSelector:@selector(newsblastDidClickOK)]) {
        [self.delegate newsblastDidClickOK];
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - Banner delegate
///////////////////////////////////////////////////////////////////////////////////////////////
- (UIViewController *)viewControllerForPresentingModalView
{
    return self.viewController;
}

- (void)adViewDidLoadAd:(MPAdView *)view
{
    NSLog(@"%s",__func__);
    _container.userInteractionEnabled = YES;
    _bannerHasLoaded = YES;
    if (view == self.adView) {
        if ([self.delegate respondsToSelector:@selector(bannerAdDidLoad)]) {
            [self.delegate bannerAdDidLoad];
        }
    } else if (view == self.rectADView) {
        if ([self.delegate respondsToSelector:@selector(mediumRectAdDidLoad)]) {
            [self.delegate mediumRectAdDidLoad];
        }
    }
    
}

- (void)adViewDidFailToLoadAd:(MPAdView *)view
{
    NSLog(@"%s",__func__);
    
    if (view == self.adView) {
        if ([self.delegate respondsToSelector:@selector(bannerAdDidFailToLoad)]) {
            [self.delegate bannerAdDidFailToLoad];
        }
    } else if (view == self.rectADView) {
        if ([self.delegate respondsToSelector:@selector(mediumRectAdDidFailToLoad)]) {
            [self.delegate mediumRectAdDidFailToLoad];
        }
    }
    
    _bannerIsShowing = NO;
}

- (void)willPresentModalViewForAd:(MPAdView *)view
{
    if (view == self.adView) {
        if ([self.delegate respondsToSelector:@selector(willPresentModalViewForBanner)]) {
            [self.delegate willPresentModalViewForBanner];
        }
    } else if (view == self.rectADView) {
        if ([self.delegate respondsToSelector:@selector(willPresentModalViewForMediumRectAd)]) {
            [self.delegate willPresentModalViewForMediumRectAd];
        }
    }
}

- (void)didDismissModalViewForAd:(MPAdView *)view
{
    //    _bannerIsShowing = NO;
    
    if (view == self.adView) {
        if ([self.delegate respondsToSelector:@selector(didDismissModalViewForBanner)]) {
            [self.delegate didDismissModalViewForBanner];
        }
    } else if (view == self.rectADView) {
        if ([self.delegate respondsToSelector:@selector(didDismissModalViewForMediumRectAd)]) {
            [self.delegate didDismissModalViewForMediumRectAd];
        }
    }
}

- (void)willLeaveApplicationFromAd:(MPAdView *)view
{
    
    if (view == self.adView) {
        if ([self.delegate respondsToSelector:@selector(willLeaveApplicationFromBanner)]) {
            [self.delegate willLeaveApplicationFromBanner];
        }
    } else if (view == self.rectADView) {
        if ([self.delegate respondsToSelector:@selector(willLeaveApplicationFromMediumRectAd)]) {
            [self.delegate willLeaveApplicationFromMediumRectAd];
        }
    }
}

@end
