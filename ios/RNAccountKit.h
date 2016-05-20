//
//  RNAccountKit.h
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "RCTBridgeModule.h"
#import "RCTBridge.h"
#import "RCTEventDispatcher.h"

@interface RNAccountKit : NSObject <RCTBridgeModule>

@property NSDictionary *options;

@end