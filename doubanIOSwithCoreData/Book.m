//
//  Book.m
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 11/30/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import "Book.h"
#import <RestKit.h>

@implementation Book

// Insert code here to add functionality to your managed object subclass
+(RKObjectMapping *)objectMapping {
    
    RKObjectMapping *mapping = [RKObjectMapping mappingForClass:[self class]];
    
    [mapping addAttributeMappingsFromArray:@[@"isbn13", @"pages", @"title", @"publisher"]];
    [mapping addAttributeMappingsFromDictionary:@{@"images.medium":@"image"}];
    
    return mapping;
}

-(NSURL *)imageURL {
    return [NSURL URLWithString:self.image];
}

-(NSString *)imageKey {
    return [NSString stringWithFormat:@"%@", self.imageURL.lastPathComponent];
}
@end
