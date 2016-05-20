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

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, AKFHeaderTextType)
{
  AKFHeaderTextTypeLogin,
  AKFHeaderTextTypeAppName,
};

extern const NSUInteger AKFHeaderTextTypeCount;

@interface AKFTheme : NSObject <NSCopying>

+ (instancetype)defaultTheme;
+ (instancetype)outlineTheme;
+ (instancetype)outlineThemeWithPrimaryColor:(UIColor *)primaryColor
                            primaryTextColor:(UIColor *)primaryTextColor
                          secondaryTextColor:(UIColor *)secondaryTextColor
                              statusBarStyle:(UIStatusBarStyle)statusBarStyle;
+ (instancetype)themeWithPrimaryColor:(UIColor *)primaryColor
                     primaryTextColor:(UIColor *)primaryTextColor
                       secondaryColor:(UIColor *)secondaryColor
                   secondaryTextColor:(UIColor *)secondaryTextColor
                       statusBarStyle:(UIStatusBarStyle)statusBarStyle;

@property (nonatomic, copy) UIColor *backgroundColor;
@property (nullable, nonatomic, copy) UIImage *backgroundImage;
@property (nonatomic, copy) UIColor *buttonBackgroundColor;
@property (nonatomic, copy) UIColor *buttonBorderColor;
@property (nonatomic, copy) UIColor *buttonDisabledBackgroundColor;
@property (nonatomic, copy) UIColor *buttonDisabledBorderColor;
@property (nonatomic, copy) UIColor *buttonDisabledTextColor;
@property (nonatomic, copy) UIColor *buttonHighlightedBackgroundColor;
@property (nonatomic, copy) UIColor *buttonHighlightedBorderColor;
@property (nonatomic, copy) UIColor *buttonHighlightedTextColor;
@property (nonatomic, copy) UIColor *buttonTextColor;
@property (nonatomic, copy) UIColor *headerBackgroundColor;
@property (nonatomic, copy) UIColor *headerTextColor;
@property (nonatomic, assign) AKFHeaderTextType headerTextType;
@property (nonatomic, copy) UIColor *iconColor;
@property (nonatomic, copy) UIColor *inputBackgroundColor;
@property (nonatomic, copy) UIColor *inputBorderColor;
@property (nonatomic, copy) UIColor *inputTextColor;
@property (nonatomic, assign) UIStatusBarStyle statusBarStyle;
@property (nonatomic, copy) UIColor *textColor;
@property (nonatomic, copy) UIColor *titleColor;

- (BOOL)isEqualToTheme:(AKFTheme *)theme;

@end

NS_ASSUME_NONNULL_END
