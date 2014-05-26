//
//  AdmobUtil.m
//  RunMrBlock
//
//  Created by alkaid on 14-5-27.
//
//

#import "AdmobUtil.h"
#import "AdmobInstance.h"

void AdmobUtil::showAd()
{
    [AdmobInstance showBanner];
}
void AdmobUtil::hideAd()
{
    [AdmobInstance hideBanner];
}