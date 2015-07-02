//
//  IAPurchase.m
//  IAPurchaseDemo
//
//  Created by anonymous on 10/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "IAPurchase.h"

@interface IAPurchase ()

@property (nonatomic, retain) SKProductsRequest *productRequest;

@end

@implementation IAPurchase

@synthesize curProductID = _curProductID;
@synthesize delegate = _delegate;
@synthesize productRequest;

static IAPurchase *instance = nil;

- (id)init {
    
    self = [super init];
    if (self) {
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];    //观察是否往队列里添加了产品
    }
    return self;
}

- (void)dealloc {
    
    [_curProductID release];
    [[SKPaymentQueue defaultQueue] removeTransactionObserver:self];
    [super dealloc];
}

+ (IAPurchase *)sharedPurchase {
    
    if (instance == nil) {
        instance = [[self alloc] init];
    }
    return instance;
}

//  进入付费处理
- (void)startRequestWithProductIdentifier:(NSString *)identifier {
    
    //  ui处理
    if (_delegate && [_delegate respondsToSelector:@selector(productRequestBegin:)]) {
        [_delegate productRequestBegin:self];
    }
    
    self.curProductID = identifier;
    self.productRequest=[[[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:_curProductID]] autorelease];
    self.productRequest.delegate=self;
    [self.productRequest start];
}

//  恢复产品信息
- (void)restorePurchase {
    
    //  ui处理
    if (_delegate && [_delegate respondsToSelector:@selector(productRequestBegin:)]) {
        [_delegate productRequestBegin:self];
    }
    
	[[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

#pragma mark - SKProductsRequestDelegate

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    
    self.productRequest = nil;
    // 最后一个产品
    SKProduct *curProduct=[[response products] lastObject];
    // 产品不存在
    if(curProduct==nil) {
        
        //  products not ready
        if (_delegate && [_delegate respondsToSelector:@selector(productsNotReady:)]) {
            [_delegate productsNotReady:self];
        }
        
        //  request end
        if (_delegate && [_delegate respondsToSelector:@selector(productRequestEnd:)]) {
            [_delegate productRequestEnd:self];
        }
        
        return;
    }
    
    SKPayment *payment = [SKPayment paymentWithProduct:curProduct];             //得到当前需付费产品信息，包括产品数量,价格
    [[SKPaymentQueue defaultQueue] addPayment:payment];                         //将产品加入支付队列，其观察者self将处理更新产品
}

// 付费申请失败
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    
    self.productRequest = nil;
    //  user canceled
    if (error.code == SKErrorPaymentCancelled) {
        if (_delegate && [_delegate respondsToSelector:@selector(purchaseCanceled:)]) {
            [_delegate purchaseCanceled:self];
        }
    }else {
        // request failed
        if (_delegate && [_delegate respondsToSelector:@selector(purchaseFailed:)]) {
            [_delegate purchaseFailed:self];
        }
    }
    
    //  request end
    if (_delegate && [_delegate respondsToSelector:@selector(productRequestEnd:)]) {
        [_delegate productRequestEnd:self];
    }
}

#pragma mark - SKPaymentTransactionObserver

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    
    NSLog(@"transaction count:%d",[transactions count]);
    for(SKPaymentTransaction *transaction in transactions) {
        
        self.curProductID = transaction.payment.productIdentifier;
        switch(transaction.transactionState) {
                
            case SKPaymentTransactionStatePurchased: {
                
                NSLog(@"transaction purchased");
                
                if (_delegate && [_delegate respondsToSelector:@selector(purchaseSuccess:)]) {
                    [_delegate purchaseSuccess:self];
                }
                if (_delegate && [_delegate respondsToSelector:@selector(productRequestEnd:)]) {
                    [_delegate productRequestEnd:self];
                }
                
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                break;
            }
            case SKPaymentTransactionStateRestored: {
                
                NSLog(@"transaction restored");
                
                // 单个restore成功的回调
//                if ([self.delegate respondsToSelector:@selector(restoreSuccess:)]) {
//                    [self.delegate restoreSuccess:[NSString stringWithString:transaction.payment.productIdentifier]];
//                }
                
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
                
                break;
            }
            case SKPaymentTransactionStateFailed: {
                
                NSLog(@"fail transaction %@",[transaction.error localizedDescription]);
                
                //  user canceled
                if (transaction.error.code == SKErrorPaymentCancelled) {
                    if (_delegate && [_delegate respondsToSelector:@selector(purchaseCanceled:)]) {
                        [_delegate purchaseCanceled:self];
                    }
                }else {
                    if (_delegate && [_delegate respondsToSelector:@selector(purchaseFailed:)]) {
                        [_delegate purchaseFailed:self];
                    }
                }
                //  ui refresh
                if (_delegate && [_delegate respondsToSelector:@selector(productRequestEnd:)]) {
                    [_delegate productRequestEnd:self];
                }
                
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
                break;
            }
        }
    }
}

- (void) paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error {
    
    if (error.code == SKErrorPaymentCancelled) {
        if (_delegate && [_delegate respondsToSelector:@selector(restoreCanceled:)]) {
            [_delegate restoreCanceled:self];
        }
    }else {
        //  restore failed
        if (_delegate && [_delegate respondsToSelector:@selector(restoreFailed:)]) {
            [_delegate restoreFailed:self];
        }
    }
    
    //  request end
    if (_delegate && [_delegate respondsToSelector:@selector(productRequestEnd:)]) {
        [_delegate productRequestEnd:self];
    }
}

- (void) paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    NSArray *array = queue.transactions;
    NSMutableArray *identifiers = [NSMutableArray arrayWithCapacity:[array count]];
    for (SKPaymentTransaction *trans in array) {
        if (trans.payment.productIdentifier) {
            [identifiers addObject:trans.payment.productIdentifier];
        }
    }
    
    if ([self.delegate respondsToSelector:@selector(restoreCompletedWithProductIdentifiers:)]) {
        [self.delegate restoreCompletedWithProductIdentifiers:identifiers];
    }
    
    if (_delegate && [_delegate respondsToSelector:@selector(productRequestEnd:)]) {
        [_delegate productRequestEnd:self];
    }
}

@end
