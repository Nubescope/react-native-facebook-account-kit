#import <AccountKit/AccountKit.h>
#import <React/RCTBridge.h>

@interface RNAccountKitAdvancedUIManager : NSObject <AKFAdvancedUIManager>

@property (nonatomic, copy) AKFTheme *theme;

- (instancetype) initWithTheme: (AKFTheme *__nonnull)theme;

@end
