
//
//  COUtils.h
//

#import <Foundation/Foundation.h>

#pragma mark - boxing and unboxing primitive types
NSNumber *INT_TO_NUM(NSInteger x);

NSString *INT_TO_STR(NSInteger x);
NSInteger STR_TO_INT(NSString *s);

#pragma mark - UDID
NSString *generateUDID();

