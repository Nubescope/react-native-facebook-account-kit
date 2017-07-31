#import <UIKit/UIKit.h>
#import <AccountKit/AccountKit.h>

#import <React/RCTBridge.h>

@interface RNAccountKitViewController : UIViewController<AKFViewControllerDelegate>

@property(nonatomic, strong) RNAccountKitViewController *instance;
@property(nonatomic, strong) AKFTheme *theme;
@property(nonatomic, strong) NSArray<NSString *> *countryWhitelist;
@property(nonatomic, strong) NSArray<NSString *> *countryBlacklist;
@property(nonatomic, strong) NSString *defaultCountry;
@property(nonatomic, strong) NSString *initialEmail;
@property(nonatomic, strong) NSString *initialPhoneNumber;
@property(nonatomic, strong) NSString *initialPhoneCountryPrefix;

- (instancetype) initWithAccountKit: (AKFAccountKit *)accountKit;

- (IBAction)loginWithPhone: (RCTPromiseResolveBlock)resolve
                  rejecter: (RCTPromiseRejectBlock)reject;

- (IBAction)loginWithEmail: (RCTPromiseResolveBlock)resolve
                  rejecter: (RCTPromiseRejectBlock)reject;

@end
