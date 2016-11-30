//
//  IISvcUtil.h
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 11/30/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RestKit/RestKit.h>
#import <CoreData/CoreData.h>


typedef void (^II_CALLBACK_BLOCK)(RKObjectRequestOperation *operation, RKMappingResult *mappingResult, NSError *error);

typedef void (^II_CALLBACK_BLOCK_SUCCESS)(RKObjectRequestOperation *operation, RKMappingResult *mappingResult);
typedef void (^II_CALLBACK_BLOCK_FAILURE)(RKObjectRequestOperation *operation, NSError * error);
typedef void (^II_CALLBACK_BLOCK_I)(RKObjectRequestOperation *operation, id mappingResult, NSError * error);
typedef void (^II_CALLBACK_OPERATION_BLOCK)(void);

@interface IISvcUtil : NSObject

+ (void)searchForBooks:(NSString *)query callback:(II_CALLBACK_BLOCK)callback;
@end
