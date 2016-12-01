//
//  IISvcUtil.m
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 11/30/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import "IISvcUtil.h"
#import <CoreData/CoreData.h>
#import <RestKit/RestKit.h>
#import <RestKit/CoreData.h>
#import "Book.h"
#import <MagicalRecord/MagicalRecord.h>
#import "AppDelegate.h"

NSString *const BASE_URL = @"https://api.douban.com/v2/book/";
NSString *const SEARCH_URL = @"search";

@implementation IISvcUtil

//
//
//+(void) initBasicInternetServiceUtility{
//
//}



+(void)searchForBooks:(NSString *)query callback:(II_CALLBACK_BLOCK)callback {
    
//    RKObjectManager *manager = [RKObjectManager managerWithBaseURL: [NSURL URLWithString:BASE_URL]];
//    
//    [manager addResponseDescriptor:
//     [RKResponseDescriptor responseDescriptorWithMapping:[Book objectMapping] method:RKRequestMethodGET pathPattern:SEARCH_URL keyPath:@"books" statusCodes:RKStatusCodeIndexSetForClass(RKStatusCodeClassSuccessful)]];
//    
 
    RKObjectManager *manager = [RKObjectManager sharedManager];
    
    [manager getObject:nil path:SEARCH_URL parameters:@{@"q":query, @"count":@(5)} success:^(RKObjectRequestOperation *operation, RKMappingResult *mappingResult) {
        callback(operation, mappingResult, nil);
        
        
        
    } failure:^(RKObjectRequestOperation *operation, NSError *error) {
        callback(operation, nil, error);
        
    }];
    
}
@end
