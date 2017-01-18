//
//  RNAccountKit.h
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <React/RCTBridgeModule.h>
#import <React/RCTBridge.h>
#import <React/RCTEventDispatcher.h>

@interface RNAccountKit : NSObject <RCTBridgeModule>

@property NSDictionary *options;

@end
