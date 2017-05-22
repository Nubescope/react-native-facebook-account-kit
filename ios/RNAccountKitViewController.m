#import "RNAccountKitViewController.h"

#import <AccountKit/AccountKit.h>
#import <React/RCTUtils.h>
#import <React/RCTLog.h>

@implementation RNAccountKitViewController
{
    RNAccountKitViewController *instance;

    AKFAccountKit *_accountKit;
    UIViewController<AKFViewController> *_pendingLoginViewController;
    NSString *_authorizationCode;
    BOOL *isUserLoggedIn;

    RCTPromiseResolveBlock _resolve;
    RCTPromiseRejectBlock _reject;
}

- (instancetype)initWithAccountKit:(AKFAccountKit *)accountKit
{
    self = [super init];
    _accountKit = accountKit;

    _pendingLoginViewController = [_accountKit viewControllerForLoginResume];
    instance = self;

    return self;
}

- (void)_prepareLoginViewController:(UIViewController<AKFViewController> *)viewController
{
    viewController.delegate = self;
    if(self.theme != nil) {
        viewController.theme = self.theme;
    }
    if (self.countryWhitelist != nil) {
        viewController.whitelistedCountryCodes = self.countryWhitelist;
    }
    if (self.countryBlacklist != nil) {
        viewController.blacklistedCountryCodes = self.countryBlacklist;
    }
    viewController.defaultCountryCode = self.defaultCountry;

}

- (void)loginWithPhone: (RCTPromiseResolveBlock)resolve
              rejecter: (RCTPromiseRejectBlock)reject;
{
    _resolve = resolve;
    _reject = reject;
    NSString *prefillPhone = self.initialPhone;
    NSString *prefillCountryCode = self.initialCountryCode;
    NSString *inputState = [[NSUUID UUID] UUIDString];
    AKFPhoneNumber * prefillPhoneNumber = [[AKFPhoneNumber alloc] initWithCountryCode: self.prefillCountryCode phoneNumber:self.prefillPhone];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController<AKFViewController> *viewController = [_accountKit viewControllerForPhoneLoginWithPhoneNumber:prefillPhoneNumber state:inputState];
        [self _prepareLoginViewController:viewController];
        UIViewController *rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
        [rootViewController presentViewController:viewController animated:YES completion:NULL];
    });
}

- (void)loginWithEmail: (RCTPromiseResolveBlock)resolve
              rejecter: (RCTPromiseRejectBlock)reject;
{
    _resolve = resolve;
    _reject = reject;
    NSString *prefillEmail = self.initialEmail;
    NSString *inputState = [[NSUUID UUID] UUIDString];

    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController<AKFViewController> *viewController = [_accountKit viewControllerForEmailLoginWithEmail:prefillEmail state:inputState];
        [self _prepareLoginViewController:viewController];
        UIViewController *rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
        [rootViewController presentViewController:viewController animated:YES completion:NULL];
    });
}

- (void)viewController:(UIViewController<AKFViewController> *)viewController
  didCompleteLoginWithAccessToken:(id<AKFAccessToken>)accessToken
                            state:(NSString *)state
{
    if (_resolve) {
        NSMutableDictionary *accessTokenData =[[NSMutableDictionary alloc] init];
        accessTokenData[@"accountId"] = [accessToken accountID];
        accessTokenData[@"appId"] = [accessToken applicationID];
        accessTokenData[@"token"] = [accessToken tokenString];
        accessTokenData[@"lastRefresh"] = [NSNumber numberWithDouble: ([[accessToken lastRefresh] timeIntervalSince1970] * 1000)];
        accessTokenData[@"refreshIntervalSeconds"] = [NSNumber numberWithDouble: [accessToken tokenRefreshInterval]];

        _resolve(accessTokenData);
    }
}

- (void)viewController:(UIViewController<AKFViewController> *)viewController
  didCompleteLoginWithAuthorizationCode:(NSString *)code
                                  state:(NSString *)state
{
    if (_resolve) {
        NSMutableDictionary *authorizationCodeData =[[NSMutableDictionary alloc] init];
        authorizationCodeData[@"code"] = code;
        authorizationCodeData[@"state"] = state;

        _resolve(authorizationCodeData);
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    // TODO: analyse if this needs to be implemented here or could be handled in React side
}

- (void)viewController:(UIViewController<AKFViewController> *)viewController didFailWithError:(NSError *)error
{
    // TODO: should display the error message somewhere
}

- (void)viewControllerDidCancel:(UIViewController<AKFViewController> *)viewController
{
    if (_resolve) {
        _resolve(nil);
    }
}

@end
