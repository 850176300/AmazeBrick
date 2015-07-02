#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *_viewController;
}
@property (nonatomic, retain)RootViewController    *viewController;
@property (nonatomic, retain)UIWindow *window;
+(AppController*)sharedAppController;
@end

