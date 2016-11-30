//
//  COUtils.m
//

#import "COUtils.h"

#pragma mark - boxing and unboxing primitive types

NSNumber *INT_TO_NUM(NSInteger x) {
    return [NSNumber numberWithInteger:x];
}

NSString *INT_TO_STR(NSInteger x) {
    return [NSString stringWithFormat:@"%li", (long)x];
}

NSInteger STR_TO_INT(NSString *s) {
    return [s integerValue];
}

#pragma mark - UDID

// This UDID generator make use of the current datetime plus 4 digit random number
NSString *generateUDID() {
    NSDate *date = [NSDate date];
    NSDateFormatter *dateformat = [[NSDateFormatter alloc] init];
    [dateformat setDateFormat:@"yyyyMMddHHmmss"];
    NSString *dateString = [dateformat stringFromDate:date];
    
    int randomNumber = (arc4random()%(99999-1))+1;
    return [NSString stringWithFormat:@"%@%d",dateString,randomNumber];
}

