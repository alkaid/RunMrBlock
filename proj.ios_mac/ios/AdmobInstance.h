//
//  AdmobInstance.h
//  RunMrBlock
//
//  Created by alkaid on 14-5-27.
//
//

#import <Foundation/Foundation.h>

@class GADBannerView;

@interface AdmobInstance : NSObject

+(void) setBannerView:(GADBannerView*) bannerView;
+(void) showBanner;
+(void) hideBanner;

@end
