//
//  fullHistoryViewController.m
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 12/1/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import "fullHistoryViewController.h"

#import "IISvcUtil.h"
#import "Book.h"
#import "fullHistoryTableViewCell.h"
#import <MagicalRecord/MagicalRecord.h>

@interface fullHistoryViewController() <UITableViewDataSource, UITableViewDelegate> 
@property (nonatomic, strong) NSArray *books;
@property (strong, nonatomic) IBOutlet UITableView *tableView;

@end

@implementation fullHistoryViewController


-(void)viewDidLoad{
    [super viewDidLoad];
    
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    
    [self loadData];
}

-(void)loadData{

    self.books = [Book MR_findAll]; //IN CONTEXT????要加入吗？
    
  
    
    [self.tableView reloadData];
}


#pragma mark - tableView

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 100;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    Book *book = self.books[indexPath.row];
    
    fullHistoryTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"BookCell"];
    [cell configWithBook:book];
    
    return cell;
}


-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.books.count;
}



@end