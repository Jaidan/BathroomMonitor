//
//  ViewController.m
//  CREOBathroomStatus
//
//  Created by Tom Dolan on 4/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController
@synthesize webView;

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self reloadView];
}

- (void)viewDidUnload
{
    [self setWebView:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    [NSObject cancelPreviousPerformRequestsWithTarget:self];
}

-(void)reloadView;
{
    // Do any additional setup after loading the view, typically from a nib.
    NSString *urlAddress = @"http://192.168.1.222";
    
    //Create a URL object.
    NSURL *url = [NSURL URLWithString:urlAddress];
    
    //URL Requst Object
    NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
    
    //Load the request in the UIWebView.
    [webView loadRequest:requestObj];
    [self performSelector:@selector(reloadView)  withObject:nil afterDelay:1];
}
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

- (void)dealloc {
    [webView release];
    [super dealloc];
}
@end
