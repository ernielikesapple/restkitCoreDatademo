//
//  IIBookCellTableViewCell.m
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 11/30/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import "IIBookCellTableViewCell.h"
#import "UIImageView+CONetwork.h"


@interface IIBookCellTableViewCell()

@property (strong, nonatomic) IBOutlet UIImageView *image;

@property (strong, nonatomic) IBOutlet UILabel *title;
@property (strong, nonatomic) IBOutlet UILabel *publisher;
@property (strong, nonatomic) IBOutlet UILabel *lbISBN;
@property (strong, nonatomic) IBOutlet UILabel *pages;



@end

@implementation IIBookCellTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}


- (void)configWithBook:(Book *)book {
    [self.image loadImageFromURL:book.imageURL placeholderImage:nil cachingKey:book.imageKey];
    self.title.text = book.title;
    self.publisher.text = book.publisher;
    self.pages.text = [NSString stringWithFormat:@"%ld", book.pages.integerValue];
    self.lbISBN.text = book.isbn13;
}
@end
