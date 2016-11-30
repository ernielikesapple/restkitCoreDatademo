//
//  IIBookCellTableViewCell.h
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 11/30/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Book.h"

@interface IIBookCellTableViewCell : UITableViewCell
- (void)configWithBook:(Book *)book;

@end
