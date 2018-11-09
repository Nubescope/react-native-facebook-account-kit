#import "RNAccountKitAdvancedUIManager.h"

#import <React/RCTBridge.h>
#import <React/RCTRootView.h>

@implementation RNAccountKitAdvancedUIManager
{
    id<AKFAdvancedUIActionController> _actionController;
}

- (void)setActionController:(id<AKFAdvancedUIActionController>)actionController
{
    _actionController = actionController;
}

- (instancetype) initWithTheme:(AKFTheme *__nonnull)theme 
{
    self = [super init];
    self.theme = theme;
    return self;
}

@end
