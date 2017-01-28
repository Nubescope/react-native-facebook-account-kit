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

#import <UIKit/UIKit.h>

#import <AccountKit/AKFButtonType.h>
#import <AccountKit/AKFLoginFlowState.h>
#import <AccountKit/AKFTextPosition.h>

/*!
 @protocol

 @abstract A controller that exposes actions to the AKFAdvancedUIManager
 */
@protocol AKFAdvancedUIActionController <NSObject>

/*!
 @abstract Triggers a pop of the current state.
 */
- (void)back;

/*!
 @abstract Triggers the login flow to cancel.
 */
- (void)cancel;

@end

/*!
 @protocol

 @abstract Manager for advanced UI configuration.
 */
@protocol AKFAdvancedUIManager <NSObject>

@optional

/*!
 @abstract Returns a custom view to use above the scrollable content.

 @param state the current state of the login flow

 @return a View or null for the default view
 */
- (nullable UIView *)actionBarViewForState:(AKFLoginFlowState)state;

/*!
 @abstract Returns a custom view for the body in the middle of the scrollable container.

 @param state the current state of the login flow

 @return a View or null for the default view
 */
- (nullable UIView *)bodyViewForState:(AKFLoginFlowState)state;

/*!
 @abstract Returns the button type for the given login state.

 @discussion This method is only called for PhoneLogin, EmailLogin and ConfirmationCode states.

 @param state the current state of the login flow

 @return the button type for the state
 */
- (AKFButtonType)buttonTypeForState:(AKFLoginFlowState)state;

/*!
 @abstract Returns a custom view for the bottom of the content in the scrollable container.

 @param state the current state of the login flow

 @return a View or null for the default view
 */
- (nullable UIView *)footerViewForState:(AKFLoginFlowState)state;

/*!
 @abstract Returns a custom view for the top of the content in the scrollable container.

 @param state the current state of the login flow

 @return a View or null for the default view
 */
- (nullable UIView *)headerViewForState:(AKFLoginFlowState)state;

/*!
 @abstract Provides a controller for the receiver that can send messages back to the current controller.

 @discussion This method will be called before any views are retrieved.

 @param actionController the action controller
 */
- (void)setActionController:(nonnull id<AKFAdvancedUIActionController>)actionController;

/*!
 @abstract Called when an error is encountered and should be displayed in the UI.

 @discussion This method will be called before the views are retrieved.

 @param error the error
 */
- (void)setError:(nonnull NSError *)error;

/*!
 @abstract Returns the position of the text relative to the content body view.

 @param state the current state of the login flow

 @return a text position
 */
- (AKFTextPosition)textPositionForState:(AKFLoginFlowState)state;

@end
