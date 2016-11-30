//
//  UIImageView+CONetwork.m
//

#import "UIImageView+CONetwork.h"
#import "COCache.h"
#import <objc/runtime.h>

static char URL_KEY;

@implementation UIImageView (CONetwork)

@dynamic imageURL;

- (void)loadImageFromURL:(NSURL *)url placeholderImage:(UIImage *)placeholder cachingKey:(NSString *)key {
    
    // first check for cache
    NSData *cachedData = [COCache objectForKey:key];
    if (cachedData) {
        self.imageURL   = nil;
        self.image      = [UIImage imageWithData:cachedData];
        return;
    }
    
    self.imageURL = url;
    self.image = placeholder;
    
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0ul);
    dispatch_async(queue, ^{
        NSData *data = [NSData dataWithContentsOfURL:url];
        
        UIImage *imageFromData = [UIImage imageWithData:data];
        
        [COCache setObject:data forKey:key];
        
        if (imageFromData) {
            if ([self.imageURL.absoluteString isEqualToString:url.absoluteString]) {
                dispatch_sync(dispatch_get_main_queue(), ^{
                    self.image = imageFromData;
                });
            } else {
                // NSLog(@"urls are not the same, bailing out!");
            }
        }
        self.imageURL = nil;
    });
}

- (void) setImageURL:(NSURL *)newImageURL {
    objc_setAssociatedObject(self, &URL_KEY, newImageURL, OBJC_ASSOCIATION_COPY);
}

- (NSURL *) imageURL {
    return objc_getAssociatedObject(self, &URL_KEY);
}

@end
