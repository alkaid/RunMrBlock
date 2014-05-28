#import <UIKit/UIKit.h>
#import "GADBannerViewDelegate.h"

@class GADBannerView;
@class GADRequest;
@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,GADBannerViewDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

@property(nonatomic, strong) GADBannerView *adBanner;

- (GADRequest *)request;
@end

