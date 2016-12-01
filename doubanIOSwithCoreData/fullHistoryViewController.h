//
//  fullHistoryViewController.h
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 12/1/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RestKit/RestKit.h>

@interface fullHistoryViewController : UIViewController <UITableViewDataSource, UITableViewDelegate,NSFetchedResultsControllerDelegate>

@property (nonatomic, strong) NSFetchedResultsController *fetchedResultsController;
//@property (nonatomic, strong) NSString *query;
@end
