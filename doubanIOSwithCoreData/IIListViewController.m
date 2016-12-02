//
//  IIListViewController.m
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 11/30/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import "IIListViewController.h"

#import "IISvcUtil.h"
#import "Book.h"
#import "IIBookCellTableViewCell.h"

@interface IIListViewController ()<UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) NSArray *books;
@property (strong, nonatomic) IBOutlet UITableView *tableView;


@end

@implementation IIListViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
  //NSLog(@"2");
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
  //  NSLog(@"3");
    [IISvcUtil searchForBooks:self.query callback:^(RKObjectRequestOperation *operation, RKMappingResult *mappingResult, NSError *error) {
        if (!error) {
            self.books = mappingResult.array;
            [self.tableView reloadData];
        }
    }];
    
}

//-(void)viewWillAppear:(BOOL)animated{
//    NSLog(@"4");
//}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

#pragma mark - tableView

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
   // NSLog(@"1");
    return 100;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    Book *book = self.books[indexPath.row];
    
    IIBookCellTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"BookCell"];
    [cell configWithBook:book];
    
    return cell;
}


-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.books.count;
}
@end
