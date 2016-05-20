#import <UIKit/UIKit.h>
#import <AccountKit/AccountKit.h>

#import "RCTBridge.h"

@interface RNAccountKitViewController : UIViewController<AKFViewControllerDelegate>

@property(nonatomic, strong) RNAccountKitViewController *instance;

- (instancetype) initWithAccountKit: (AKFAccountKit *)accountKit;

- (IBAction)loginWithPhone: (RCTPromiseResolveBlock)resolve
                  rejecter: (RCTPromiseRejectBlock)reject;

- (IBAction)loginWithEmail: (RCTPromiseResolveBlock)resolve
                  rejecter: (RCTPromiseRejectBlock)reject;

@end
