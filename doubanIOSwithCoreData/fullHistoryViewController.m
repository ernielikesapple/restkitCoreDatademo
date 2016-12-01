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

static NSString * BASE_URL = @"https://api.douban.com/v2/book/";
static NSString * SEARCH_URL = @"search";


@interface fullHistoryViewController()
@property (nonatomic, strong) NSArray *books;

@property (strong, nonatomic) IBOutlet UITableView *tableView;


@end

@implementation fullHistoryViewController


-(void)viewDidLoad{
    [super viewDidLoad];
    
}


-(void)viewWillAppear:(BOOL)animated{

    [super viewWillAppear:animated];
   [self loadData];

}

-(void)fetchDatafromDataBase{
    // Set debug logging level. Set to 'RKLogLevelTrace' to see JSON payload
    RKLogConfigureByName("RestKit/Network", RKLogLevelDebug);
    
    NSFetchRequest *fetchRequest = [NSFetchRequest fetchRequestWithEntityName:@"BookEntity"];
    //取出的排序
    NSSortDescriptor *descriptor = [NSSortDescriptor sortDescriptorWithKey:@"title" ascending:NO];
    fetchRequest.sortDescriptors = @[descriptor];
    NSError *error = nil;
    
    //取出的结果
    self.fetchedResultsController =[[NSFetchedResultsController alloc] initWithFetchRequest:fetchRequest
                                                                       managedObjectContext:[RKManagedObjectStore defaultStore].mainQueueManagedObjectContext
                                                                         sectionNameKeyPath:nil
                                                                                  cacheName:nil];
    
    [self.fetchedResultsController setDelegate:self];
    BOOL fetchSuccessful = [self.fetchedResultsController performFetch:&error];
    NSAssert([[self.fetchedResultsController fetchedObjects] count], @"seeding didn't work....");
    if(!fetchSuccessful){
        NSLog(@"%@",error);
    }

}


-(void)loadData{

    //self.books = [Book MR_findAll]; //IN CONTEXT????要写入参数吗这个取是从default context里取所有详见training中ptusercourse.m中为什么要标明context？？？
    [self fetchDatafromDataBase];
    [self.tableView reloadData];
}


#pragma mark - tableView
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    id<NSFetchedResultsSectionInfo>sectionInfo = [self.fetchedResultsController.sections objectAtIndex:section];
    return [sectionInfo numberOfObjects];
    // return 1;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 100;
}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    //Book *book = self.books[indexPath.row];
  
    
    
    fullHistoryTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"fullHistoryTableViewCell"];
     Book *book = [self.fetchedResultsController objectAtIndexPath:indexPath];
    [cell configWithBook:book];

    return cell;
}
//
//
//-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
//    return self.books.count;
//}





@end
