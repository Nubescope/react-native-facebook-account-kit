// Copyright (c) 2014-present, Facebook, Inc. All rights reserved.
//
// You are hereby granted a non-exclusive, worldwide, royalty-free license to use,
// copy, modify, and distribute this software in source code or binary form for use
// in connection with the web services and APIs provided by Facebook.
//
// As with any software that integrates with the Facebook platform, your use of
// this software is subject to the Facebook Developer Principles and Policies
// [http://developers.facebook.com/policy/]. This copyright notice shall be
// included in all copies or substantial portions of the software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#import <Foundation/Foundation.h>

#import <AccountKit/AKFAccessToken.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AKFAccountPreferencesDelegate;

/*!
 @abstract Accesses Account preferences that are stored on the Account Kit servers for the associated app and account.

 @discussion Get an instance of this class through AKFAccountKit `accountPreferences`
 */
@interface AKFAccountPreferences : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
 @abstract A delegate for the AKFAccountPreferences object.
 */
@property (nonatomic, weak) id<AKFAccountPreferencesDelegate> delegate;

/*!
 @abstract Deletes a single preference.

 @param key The key for the preference.
 */
- (void)deletePreferenceForKey:(NSString *)key;

/*!
 @abstract Loads a single preference.

 @param key The key for the preference.

 @discussion The loaded preference is sent to the delegate after it has loaded.
 */
- (void)loadPreferenceForKey:(NSString *)key;

/*!
 @abstract Loads all preferences.

 @discussion The loaded preferences are sent to the delegate after they are loaded.
 */
- (void)loadPreferences;

/*!
 @abstract Writes a single preference.

 @param key The key for the preference.
 @param value The value for the preference.

 @discussion Setting a value of null will instead invoke `deletePreferenceForKey:`.  Any existing value will be
 overwritten.
 Keys must be ASCII letters, digits or the underscore character and be 1-100 characters in length.
 Values must be 1-1000 characters in length.
 */
- (void)setPreferenceForKey:(NSString *)key value:(nullable NSString *)value;

@end

/*!
 @protocol

 @abstract The delegate the receives messages from `AKFAccountPreferences`.
 */
@protocol AKFAccountPreferencesDelegate <NSObject>

@optional

/*!
 @abstract Notifies the delegate that a single preference was deleted.

 @param accountPreferences The AKFAccountPreferences instance that deleted the preference.
 @param key The key for the deleted preference.
 @param error The error if the preference could not be deleted.
 */
- (void)accountPreferences:(AKFAccountPreferences *)accountPreferences
 didDeletePreferenceForKey:(NSString *)key
                     error:(nullable NSError *)error;

/*!
 @abstract Notifies the delegate that preferences were loaded.

 @param accountPreferences The AKFAccountPreferences instance that loaded the preferences.
 @param preferences The dictionary of preferences.
 @param error The error if the preferences could not be loaded.
 */
- (void)accountPreferences:(AKFAccountPreferences *)accountPreferences
        didLoadPreferences:(nullable NSDictionary<NSString *, NSString *> *)preferences
                     error:(nullable NSError *)error;

/*!
 @abstract Notifies the delegate that a single preference was loaded.

 @param accountPreferences The AKFAccountPreferences instance that loaded the preference.
 @param key The key for the loaded preference.
 @param value The value for the loaded preference.
 @param error The error if the preference could not be loaded.
 */
- (void)accountPreferences:(AKFAccountPreferences *)accountPreferences
   didLoadPreferenceForKey:(NSString *)key
                     value:(nullable NSString *)value
                     error:(nullable NSError *)error;

/*!
 @abstract Notifies the delegate that a single preference was set.

 @param accountPreferences The AKFAccountPreferences instance that set the preference.
 @param key The key for the set preference.
 @param value The value for the set preference.
 @param error The error if the preference could not be set.
 */
- (void)accountPreferences:(AKFAccountPreferences *)accountPreferences
    didSetPreferenceForKey:(NSString *)key
                     value:(NSString *)value
                     error:(nullable NSError *)error;

@end

NS_ASSUME_NONNULL_END
