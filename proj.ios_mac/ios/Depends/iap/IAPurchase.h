//
//  IAPurchase.h
//  IAPurchaseDemo
//
//  Created by anonymous on 10/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
//  Version: 1.0.5
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@protocol IAPurchaseDelegate;

@interface IAPurchase : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver> {
    NSString    *_curProductID;
    id<IAPurchaseDelegate> _delegate;
}

@property (nonatomic, copy) NSString *curProductID;
@property (nonatomic, assign) id<IAPurchaseDelegate> delegate;

+ (IAPurchase *)sharedPurchase;
- (void)startRequestWithProductIdentifier:(NSString *)identifier;
- (void)restorePurchase;

@end


@protocol IAPurchaseDelegate <NSObject>
@required
- (void)purchaseSuccess:(IAPurchase *)purchase;
- (void)purchaseFailed:(IAPurchase *)purchase;

@optional
- (void)restoreFailed:(IAPurchase *)purchase;

// 所有购买过的产品全部restore成功的回调
// productIdentifiers数组里面存放的是每个产品的标识字符串。
// 如果没有购买过产品，那么productIdentifiers数组的长度为0，可以提示用户还未购买过产品；
// 否则处理restore逻辑
- (void)restoreCompletedWithProductIdentifiers:(NSArray *)productIdentifiers;

- (void)purchaseCanceled:(IAPurchase *)purchase;
- (void)restoreCanceled:(IAPurchase *)purchase;

- (void)productRequestBegin:(IAPurchase *)purchase;
- (void)productRequestEnd:(IAPurchase *)purchase;

- (void)productsNotReady:(IAPurchase *)purchase;

@end
