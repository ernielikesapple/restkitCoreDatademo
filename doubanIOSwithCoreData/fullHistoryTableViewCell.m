//
//  fullHistoryTableViewCell.m
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 12/1/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import "fullHistoryTableViewCell.h"
#import "UIImageView+CONetwork.h"

@interface fullHistoryTableViewCell()

//@property (strong, nonatomic) IBOutlet UIImageView *image;
//@property (strong, nonatomic) IBOutlet UILabel *title;
//
//@property (strong, nonatomic) IBOutlet UILabel *publisher;
//@property (strong, nonatomic) IBOutlet UILabel *lbISBN;
//@property (strong, nonatomic) IBOutlet UILabel *pages;

@property (strong, nonatomic) IBOutlet UIImageView *image;
@property (strong, nonatomic) IBOutlet UILabel *title;
@property (strong, nonatomic) IBOutlet UILabel *publisher;
@property (strong, nonatomic) IBOutlet UILabel *lbISBN;
@property (strong, nonatomic) IBOutlet UILabel *pages;


@end

@implementation fullHistoryTableViewCell



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
