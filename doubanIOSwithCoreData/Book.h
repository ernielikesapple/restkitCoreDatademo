//
//  Book.h
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 11/30/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
@class RKObjectMapping;

NS_ASSUME_NONNULL_BEGIN

@interface Book : NSManagedObject

// Insert code here to declare functionality of your managed object subclass



+ (RKObjectMapping*)objectMapping;

- (NSURL *)imageURL;
- (NSString *)imageKey;


@end

NS_ASSUME_NONNULL_END

#import "Book+CoreDataProperties.h"
