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

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract The AccountKit error domain for server errors (underlying errors).
 */
extern NSString *const AKFServerErrorDomain;

/*!
 @typedef AKFServerErrorCode

 @abstract Detail error codes for server errors.
 */
typedef NS_ENUM(NSInteger, AKFServerErrorCode)
{
  /*!
   @abstract An invalid parameter value was found.

   @discussion The SDK does not know how to handle this parameter value from the server.
   */
  AKFInvalidServerParameterValueError = 201,
};

/*!
 @typedef AKFLoginRequestInvalidatedErrorCode

 @abstract Detail error codes for login request invalidated errors.
 */
typedef NS_ENUM(NSInteger, AKFLoginRequestInvalidatedErrorCode)
{
  /*!
   @abstract The request has expired without completing.
   */
  AKFLoginRequestExpiredError = 301,
};

/*!
 @typedef AKFInvalidParameterValueErrorCode

 @abstract Detail error codes for invalid parameter errors.
 */
typedef NS_ENUM(NSInteger, AKFInvalidParameterValueErrorCode)
{
  /*!
   @abstract The email address value is invalid.
   */
  AKFInvalidEmailAddressError = 401,

  /*!
   @abstract The phone number value is invalid.
   */
  AKFInvalidPhoneNumberError = 402,

  /*!
   @abstract The value is not of the appropriate type for NSCoding.
   */
  AKFInvalidCodingValueError = 403,

  /*!
   @abstract No valid access token is available.
   */
  AKFInvalidAccessTokenError = 404,

  /*!
   @abstract The key for account preferences is invalid.
   */
  AKFInvalidAccountPreferenceKeyError = 405,

  /*!
   @abstract The value for account preferences is invalid.
   */
  AKFInvalidAccountPreferenceValueError = 406,

  /*!
   @abstract The operation was not successful.
   */
  AKFOperationNotSuccessful = 407,
};

/*!
 @typedef AKFServerResponseErrorCode

 @abstract Detail error codes for server response errors.
 */
typedef NS_ENUM(NSInteger, AKFServerResponseErrorCode)
{
  AKFServerResponseErrorCodeInvalidConfirmationCode = 15003,
};

NS_ASSUME_NONNULL_END
