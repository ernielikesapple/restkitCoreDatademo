//
//  UIImageView+CONetwork.h
//

#import <UIKit/UIKit.h>

@interface UIImageView (CONetwork)

- (void)loadImageFromURL:(NSURL *)url placeholderImage:(UIImage *)placeholder cachingKey:(NSString *)key;

@property (nonatomic, copy) NSURL *imageURL;

@end
