//
//  STInAppBilling.h
//  MysteryGuardians
//
//  Created by Steven.Xc.Tian on 13-7-15.
//
//

#ifndef __MysteryGuardians__STInAppBilling__
#define __MysteryGuardians__STInAppBilling__

#include "STIABDelegate.h"

class STInAppBilling {
    
public:
    STInAppBilling();
    ~STInAppBilling();
    
    void setIABDelegate(STIABDelegate* pDelegate);
    
public:
    // in Android OS, the below methods need communicate with jni,
    // so the relative source file is placed in jni directory under
    // the proj.androd
    
    /**
	 * 通过商品id购买商品,商品默认为托管类型的
	 *
	 * @param sku
	 *            商品的SKU
	 */
	virtual void purchase(const char* sku);
    
	/**
	 * 购买非托管类型的商品，即消费品
	 *
	 * @param sku
	 *            商品的SKU
	 */
	virtual void purchaseUnmanaged(const char* sku);
    
	/**
	 * 恢复已经购买的产品
     *
     * @param isLocal is just only for Android platform. this param not effect IOS platform.
     *        see this in Android method.
     *
	 */
	virtual void restore();
    
    /**
     * 查询购买过的物品，默认先查询本地，如果有直接返回，如果不存在，则转向服务器查询，类似于 retore 功能，不过有查询本地的过程
     * Only for Android platform.
     */
    virtual void query();
    
};

#endif /* defined(__MysteryGuardians__STInAppBilling__) */
