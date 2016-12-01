//
//  ViewController.m
//  doubanIOSwithCoreData
//
//  Created by ernie.cheng on 11/30/16.
//  Copyright © 2016 ernie.cheng. All rights reserved.
//

#import "ViewController.h"
#import "IIListViewController.h"

@interface ViewController ()
@property (strong, nonatomic) IBOutlet UITextField *searchField;
@property (strong, nonatomic) IBOutlet UIButton *btSearch;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
      self.btSearch.backgroundColor = [UIColor redColor];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    IIListViewController *dest = segue.destinationViewController;
    dest.query = self.searchField.text;
}

- (BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(id)sender {
    return self.searchField.text.length >0;
}

@end
