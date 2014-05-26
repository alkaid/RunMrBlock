//
//  AdmobInstance.m
//  RunMrBlock
//
//  Created by alkaid on 14-5-27.
//
//

#import "AdmobInstance.h"
#import "GADBannerView.h"

static GADBannerView* curBannerView;
@implementation AdmobInstance
+(void)setBannerView:(GADBannerView *)bannerView
{
    curBannerView = bannerView;
}
+(void) showBanner
{
    if (!curBannerView)
        return;
    curBannerView.hidden=false;
}
+(void) hideBanner
{
    if (!curBannerView)
        return;
    curBannerView.hidden=true;
}
@end
