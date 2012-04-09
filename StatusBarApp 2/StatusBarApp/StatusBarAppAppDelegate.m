//
//  StatusBarAppAppDelegate.m
//  StatusBarApp
//
//  Created by CCoding on 18.09.11.
//  Copyright 2011 CCoding. All rights reserved.
//

#import "StatusBarAppAppDelegate.h"

@implementation StatusBarAppAppDelegate

@synthesize window;

- (void)awakeFromNib {
    
    statusItem = [[[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength] retain];
    
    NSBundle *bundle = [NSBundle mainBundle];
    
    
    statusHighlightImage = [[NSImage alloc] initWithContentsOfFile:[bundle pathForResource:@"Icon2" ofType:@"png"]]; 
    
    //[statusItem setImage:statusImage];
    //[statusItem setAlternateImage:statusHighlightImage];
    //Use a title instead of images
    //[statusItem setTitle:@"This text will appear instead of images"];
    [statusItem setMenu:statusMenu];
    [statusItem setToolTip:@"Restroom is..."];
    [statusItem setHighlightMode:YES];
    [self requestStatus];
    
}



- (IBAction)doSomething:(id)sender {
    
    NSLog(@"Is doing something");
}

-(void)requestStatus
{
    NSURL* aURL = [NSURL URLWithString:@"http://192.168.1.222"];
   

  

    if(aXMLData != nil)
    {
        [aXMLData release];
    }
    aXMLData = [[NSMutableData alloc] init];

    //   NSString *url = [NSString stringWithFormat:@"http://greengoose.com/loginAjax?username=%@&password=%@&apntoken=%@", userName, password, apnToken];
    
    //    UIAlertView *alert = [[[UIAlertView alloc] initWithTitle:@"Debug APNToken" message:apnToken delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:nil] autorelease];
    //   [alert show];
    
    //med
    
  
    NSURLRequest *aRequest = [[NSURLRequest alloc]initWithURL:aURL];
    NSURLConnection* temp = [[NSURLConnection alloc]initWithRequest:aRequest delegate:self];
    
    [aRequest release];
    [temp release];
    [self performSelector:@selector(requestStatus) withObject:nil afterDelay:10];
}
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [aXMLData appendData:data];
}
-(void)connection:(NSURLConnection*)connection didFailWithError:(NSError *)error
{
    NSLog([[NSString alloc]initWithData:aXMLData encoding:NSUTF8StringEncoding]);
}
-(void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    NSString* data = [[NSString alloc]initWithData:aXMLData encoding:NSUTF8StringEncoding];
    NSLog(data);
    
    if ([data rangeOfString:@"Available"].location == NSNotFound) {
        statusImage = [[NSImage alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Icon1" ofType:@"png"]];
        [statusItem setImage:statusImage];
    } else {
        statusImage = [[NSImage alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"icon3" ofType:@"png"]];
        [statusItem setImage:statusImage];
    }
}
-(void)dealloc
{
    [aXMLData release];
    [aConnection release];
    [statusImage release];
    [statusHighlightImage release];
    [super dealloc];
}
@end
