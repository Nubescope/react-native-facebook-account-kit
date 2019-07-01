//
//  RNAccountKit.m
//

#import "RNAccountKitAdvancedUIManager.h"
#import "RNAccountKit.h"
#import <React/RCTBridge.h>
#import "RNAccountKitViewController.h"
#import <React/RCTRootView.h>
#import <React/RCTLog.h>

@implementation RNAccountKit
{
    AKFAccountKit *_accountKit;
}

RCT_EXPORT_MODULE();


RCT_EXPORT_METHOD(login:(NSString *)type
                  resolver: (RCTPromiseResolveBlock)resolve
                  rejecter: (RCTPromiseRejectBlock)reject)
{
    @try {
        RNAccountKitViewController* a = [[RNAccountKitViewController alloc] initWithAccountKit: [self getAccountKit]];
        a.advancedUIManager = [self getAdvancedUIManager];
        a.countryWhitelist = [self.options valueForKey:@"countryWhitelist"];
        a.countryBlacklist = [self.options valueForKey:@"countryBlacklist"];
        a.defaultCountry = [self.options valueForKey:@"defaultCountry"];
        a.initialEmail = [self.options valueForKey:@"initialEmail"];
        a.initialPhoneCountryPrefix = [self.options valueForKey:@"initialPhoneCountryPrefix"];
        a.initialPhoneNumber = [self.options valueForKey:@"initialPhoneNumber"];

        if ([self.options valueForKey:@"viewControllerMode"]) {
          a.viewControllerMode = [self.options valueForKey:@"viewControllerMode"];
        } else {
          a.viewControllerMode = @"present";
        }
        
        if ([[self.options valueForKey:@"facebookNotificationsEnabled"] boolValue] == YES) {
            a.facebookNotificationsEnabled = YES;
        } else {
            a.facebookNotificationsEnabled = NO;
        }
        
        if ([[self.options valueForKey:@"getACallEnabled"] boolValue] == YES) {
            a.getACallEnabled = YES;
        } else {
            a.getACallEnabled = NO;
        }
        
        if ([[self.options valueForKey:@"setEnableInitialSmsButton"] boolValue] == YES) {
            a.setEnableInitialSmsButton = YES;
        } else {
            a.setEnableInitialSmsButton = NO;
        }

        if ([type isEqual: @"phone"]) {
            [a loginWithPhone: resolve rejecter: reject];
        } else {
            [a loginWithEmail: resolve rejecter: reject];
        }
    }
    @catch (NSException * e) {
        reject(@"login_failed", @"Could not login", [self errorFromException:e]);
    }

}

RCT_EXPORT_METHOD(logout: (RCTPromiseResolveBlock)resolve
                  rejecter: (RCTPromiseRejectBlock)reject)
{
    @try {
        [_accountKit logOut];
        resolve(nil);
    }
    @catch (NSException * e) {
        reject(@"logout_error", @"Could not logout", [self errorFromException:e]);
    }
}


RCT_EXPORT_METHOD(configure:(NSDictionary *)options
                  resolver: (RCTPromiseResolveBlock)resolve
                  rejecter: (RCTPromiseRejectBlock)reject)
{
    self.options = options;
}


RCT_EXPORT_METHOD(getCurrentAccessToken: (RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
    @try {
        id<AKFAccessToken> accessToken = [[self getAccountKit] currentAccessToken];

        if (![accessToken accountID]) {
            return resolve(nil);
        }

        NSMutableDictionary *accessTokenData =[[NSMutableDictionary alloc] init];
        accessTokenData[@"accountId"] = [accessToken accountID];
        accessTokenData[@"appId"] = [accessToken applicationID];
        accessTokenData[@"token"] = [accessToken tokenString];
        accessTokenData[@"lastRefresh"] = [NSNumber numberWithDouble: ([[accessToken lastRefresh] timeIntervalSince1970] * 1000)];
        accessTokenData[@"refreshIntervalSeconds"] = [NSNumber numberWithDouble: [accessToken tokenRefreshInterval]];

        resolve(accessTokenData);
    }
    @catch (NSException * e) {
        reject(@"access_token_error", @"Could not get access token", [self errorFromException:e]);
    }
}

RCT_EXPORT_METHOD(getCurrentAccount: (RCTPromiseResolveBlock)resolve
                  rejecter: (RCTPromiseRejectBlock)reject)
{
    __block bool callbackCalled = false;
    [_accountKit requestAccount:^(id<AKFAccount> account, NSError *error) {
        if (callbackCalled) {
            return;
        }
        callbackCalled = true;

        if (error) {
            reject(@"request_account", @"Could not get account data", error);
        } else {
            resolve([self formatAccountData:account]);
        }
    }];
}

- (AKFTheme *)getTheme {
    NSDictionary *themeOptions = [self.options objectForKey:@"theme"];
    if(themeOptions == nil) {
      return nil;
    }
    AKFTheme *theme = [AKFTheme defaultTheme];
    NSArray *colorOptions = @[@"backgroundColor",
                              @"headerBackgroundColor",@"headerTextColor",@"headerButtonTextColor",
                              @"buttonBackgroundColor",@"buttonBorderColor",@"buttonTextColor",
                              @"buttonDisabledBackgroundColor",@"buttonDisabledBorderColor",
                              @"buttonDisabledTextColor",@"iconColor",@"inputBackgroundColor",
                              @"inputBorderColor",@"inputTextColor",@"textColor",@"titleColor"];
    for(NSString *key in themeOptions) {
        UIColor *color;
        if([colorOptions containsObject:key]) {
            NSDictionary *value = [themeOptions valueForKey:key];
            color = [UIColor colorWithRed:[[value valueForKey:@"r"] floatValue]
                                    green:[[value valueForKey:@"g"] floatValue]
                                     blue:[[value valueForKey:@"b"] floatValue]
                                    alpha:[[value valueForKey:@"a"] floatValue]];
            [theme setValue:color forKey:key];
        } else if([key isEqualToString:@"backgroundImage"]) {
            theme.backgroundImage = [UIImage imageNamed:[themeOptions objectForKey:key]];
        } else if([key isEqualToString:@"statusBarStyle"]) {
            int statusBarStyle = ((NSNumber*)[themeOptions valueForKey:key]).intValue;
            if (UIStatusBarStyleDefault == statusBarStyle) {
                theme.statusBarStyle = UIStatusBarStyleDefault;
            }
            if (UIStatusBarStyleLightContent == statusBarStyle) {
                theme.statusBarStyle = UIStatusBarStyleLightContent;
            }
        }
    }
    return theme;
}

- (RNAccountKitAdvancedUIManager*) getAdvancedUIManager {
    AKFTheme *theme = [self getTheme];
    if (theme == nil) {
        return nil;
    }
    return [[RNAccountKitAdvancedUIManager alloc] initWithTheme:theme];
}

- (AKFAccountKit*) getAccountKit
{
    if (_accountKit == nil) {
        // may also specify AKFResponseTypeAccessToken
        BOOL useAccessToken = [[self.options valueForKey:@"responseType"] isEqualToString:@"token"];
        AKFResponseType responseType = useAccessToken ? AKFResponseTypeAccessToken : AKFResponseTypeAuthorizationCode;
        _accountKit = [[AKFAccountKit alloc] initWithResponseType:responseType];
    }

    return _accountKit;
}

- (NSMutableDictionary*) formatAccountData: (id<AKFAccount>) account
{
    NSMutableDictionary *result =[[NSMutableDictionary alloc] init];
    result[@"id"] = account.accountID;
    result[@"email"] = account.emailAddress;

    if (account.phoneNumber && account.phoneNumber.phoneNumber) {
        result[@"phoneNumber"] = @{
            @"number": account.phoneNumber.phoneNumber,
            @"countryCode": account.phoneNumber.countryCode
        };
    }

    return result;
}

- (NSError *) errorFromException: (NSException *) exception
{
    NSDictionary *exceptionInfo = @{
        @"name": exception.name,
        @"reason": exception.reason,
        @"callStackReturnAddresses": exception.callStackReturnAddresses,
        @"callStackSymbols": exception.callStackSymbols,
        @"userInfo": exception.userInfo
    };

    return [[NSError alloc] initWithDomain: @"RNAccountKit"
                                      code: 0
                                  userInfo: exceptionInfo];
}

@end
