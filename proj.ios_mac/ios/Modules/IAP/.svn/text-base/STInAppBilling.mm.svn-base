//
//  STInAppBilling.cpp
//  MysteryGuardians
//
//  Created by Steven.Tian on 13-7-15.
//
//

#include "STInAppBilling.h"
#include "IOSIAPWrapper.h"

STInAppBilling::STInAppBilling()
{
}

STInAppBilling::~STInAppBilling()
{
}

void STInAppBilling::setIABDelegate(STIABDelegate* pDelegate)
{
    [[IOSIAPManager sharedManager] setSTIABDelegate:pDelegate];
}

void STInAppBilling::purchase(const char *pid)
{
    [[IOSIAPManager sharedManager]purchaseIAPWithPID:[NSString stringWithCString:pid encoding:NSUTF8StringEncoding]];
}

void STInAppBilling::purchaseUnmanaged(const char *pid)
{
    // on IOS platform, this method the same as purchase(const char *)
    purchase(pid);
}

void STInAppBilling::restore()
{
    [[IOSIAPManager sharedManager] restoreIAP];
}

void STInAppBilling::query()
{
    /* Only For Android platform */
}