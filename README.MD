# React Native Facebook Account Kit

A Facebook Account Kit SDK wrapper for react-native.

[![version](https://img.shields.io/npm/v/react-native-facebook-account-kit.svg)](https://www.npmjs.com/package/react-native-facebook-account-kit)
[![downloads](https://img.shields.io/npm/dt/react-native-facebook-account-kit.svg)](https://www.npmjs.com/package/react-native-facebook-account-kit)


## Supported versions - React Native / Facebook Account Kit

The table below shows the supported versions of React Native and the different versions of `react-native-facebook-account-kit`.

| RN Facebook Account Kit | 0.4.x | 0.6.x | 0.10.x  |  1.x.x   |  2.x.x   |
| ----------------------- | :---: | :---: | :-----: | :------: | :------: |
| React Native            | 0.24  | <0.48 | 0.48-56 | >=0.57.x | >=0.60.x |


## Installation  

> For RN < **0.40.0** Check the [Troubleshooting Guide](#troubleshooting)

> For RN < **0.60.x** Follow the installation steps described [in this document](docs/Legacy-Instalation-Steps.md)

```shell
yarn add react-native-facebook-account-kit
cd ios && pod install && cd ..
```

## Linking

Not necessary 🎉 [Check out the RN 0.60 release blog post](https://facebook.github.io/react-native/blog/2019/07/03/version-60)


## Configuration

### Obtaining secret and token to configure the library

First of all you must obtain an **Account App Id** and an **Account Kit Client Token**. To obtain them you must create a Facebook application using [facebook developer's website](https://developers.facebook.com/apps/). 

In the [part 1]((https://medium.com/react-native-training/passwordless-authentication-in-react-native-using-facebook-account-kit-part-1-8d83e92077e9)) of the following blog post series you will find detailed steps about how to create and configura a **Facebook Account Kit** application:

- [Passwordless Authentication in React Native Using Facebook Account Kit (Part 1)](https://medium.com/react-native-training/passwordless-authentication-in-react-native-using-facebook-account-kit-part-1-8d83e92077e9)
- [Passwordless Authentication in React Native Using Facebook Account Kit (Part 2)](https://medium.com/react-native-training/passwordless-authentication-in-react-native-using-facebook-account-kit-part-2-367a820f269c)
- [Passwordless Authentication in React Native Using Facebook Account Kit (Part 3)](https://medium.com/react-native-training/passwordless-authentication-in-react-native-using-facebook-account-kit-part-3-ddf44d81beb5)


### IOS Configuration

Add your **Account App Id** and an **Account Kit Client Token** to your project's `Info.plist` file

```xml
<plist version="1.0">
  <dict>
    ...
    <key>FacebookAppID</key>
    <string>{YOUR_FACEBOOK_APP_ID}</string>
    <key>AccountKitClientToken</key>
    <string>{YOUR_ACCOUNT_KIT_CLIENT_TOKEN}</string>
    <key>CFBundleURLTypes</key>
    <array>
      <dict>
        <key>CFBundleURLSchemes</key>
        <array>
          <string>ak{YOUR_FACEBOOK_APP_ID}</string>
        </array>
      </dict>
    </array>
    ...
  </dict>
</plist>
```

### Android Configuration

Add your **Account App Id** and the **Account Kit Client Token** to the `android/app/src/main/res/values/strings.xml`:

```xml
...
<string name="fb_app_id">YOUR_FACEBOOK_APP_ID</string>
<string name="ak_client_token">YOUR_ACCOUNT_KIT_CLIENT_TOKEN</string>
```

Then update set your app metadata by editing the `android/app/src/main/AndroidManifest.xml` file:

```xml
...
<application>
    ...
    <meta-data
        android:name="com.facebook.sdk.ApplicationId"
        android:value="@string/fb_app_id" />
    <meta-data
        android:name="com.facebook.accountkit.ApplicationName"
        android:value="@string/app_name" />
    <meta-data
        android:name="com.facebook.accountkit.ClientToken"
        android:value="@string/ak_client_token" />
    ...
</application>
...
```

3. If you want AccountKit to prefill your phone number add the `READ_PHONE_STATE` permission to the `android/app/src/main/AndroidManifest.xml` file:

```xml
...
<manifest ...>
  ...
  <uses-permission android:name="android.permission.READ_PHONE_STATE" />
  ...
</manifest>  
```

4. *(Optional)* Exclude backup for Access Tokens on Android >= 6.0

    As per this [documentation](https://developers.facebook.com/docs/accountkit/accesstokens), Account Kit does not support automated backup (introduced in Android 6.0). The following steps will exclude automated backup

    1.  Create a file `android/app/src/main/res/xml/backup_config.xml` that contains the follwoing:

    ```java
    <?xml version="1.0" encoding="utf-8"?>
    <full-backup-content>
      <exclude domain="sharedpref" path="com.facebook.accountkit.AccessTokenManager.SharedPreferences.xml"/>
    </full-backup-content>
    ```

    2.  In your `AndroidManifest.xml` add the following to exclude backup of Account Kit's Access Token.

    ```java
    <application
      //other configurations here
      android:fullBackupContent="@xml/backup_config" // add this line
    >
    ```

## Usage

> If you have issues with the method signatures you may be using an older version. Check the [Releases Notes](https://github.com/underscopeio/react-native-facebook-account-kit/releases) for breaking changes

```javascript
import RNAccountKit from 'react-native-facebook-account-kit'

// Configures the SDK with some options
RNAccountKit.configure({
  responseType: 'token'|'code', // 'token' by default,
  titleType: 'login',
  initialAuthState: '',
  initialEmail: 'some.initial@email.com',
  initialPhoneCountryPrefix: '+1', // autodetected if none is provided
  initialPhoneNumber: '123-456-7890',
  facebookNotificationsEnabled: true|false, // true by default
  readPhoneStateEnabled: true|false, // true by default,
  countryWhitelist: ['AR'], // [] by default
  countryBlacklist: ['US'], // [] by default
  defaultCountry: 'AR',
  theme: {
    // for iOS only, see the Theme section
  },
  viewControllerMode: 'show'|'present', // for iOS only, 'present' by default
  getACallEnabled: true|false,
  setEnableInitialSmsButton: true|false, // true by default
})

// Shows the Facebook Account Kit view for login via SMS
RNAccountKit.loginWithPhone()
  .then((token) => {
    if (!token) {
      console.log('Login cancelled')
    } else {
      console.log(`Logged with phone. Token: ${token}`)
    }
  })

// Shows the Facebook Account Kit view for login via email
RNAccountKit.loginWithEmail()
  .then((token) => {
    if (!token) {
      console.log('Login cancelled')
    } else {
      console.log(`Logged with email. Token: ${token}`)
    }
  })

// Logouts the user, so getCurrentAccessToken() will retrieve null
RNAccountKit.logout()
  .then(() => {
    console.log('Logged out')
  })

// Retrieves the logged user access token, if any user is logged
RNAccountKit.getCurrentAccessToken()
  .then((token) => {
    console.log(`Current access token: ${token}`)
  })

// Retrieves the logged user account info, if any user is logged
RNAccountKit.getCurrentAccount()
  .then((account) => {
    console.log(`Current account: ${account}`)
  })
```

[@MahbbRah](https://github.com/MahbbRah) put together a [video tutorial](https://youtu.be/R-HSmuVHkIM) of how to integrate the library you might find useful.

## Examples

Try the [examples](https://github.com/underscopeio/react-native-facebook-account-kit/tree/master/examples).
They are related to different React Native versions.

```bash
git clone https://github.com/underscopeio/react-native-facebook-account-kit
cd react-native-facebook-account-kit/examples/RN0XX
yarn
react-native run-ios
react-native run-android
```

## Themes

### iOS

```javascript
import RNAccountKit, {
  Color,
  StatusBarStyle,
} from 'react-native-facebook-account-kit'

RNAccountKit.configure({
  ...,
  theme: {
    // Background
    backgroundColor: Color.rgba(0, 120, 0, 0.1),
    backgroundImage: 'background.png',
    // Button
    buttonBackgroundColor: Color.rgba(0, 153, 0, 1.0),
    buttonBorderColor: Color.rgba(0, 255, 0, 1),
    buttonTextColor: Color.rgba(0, 255, 0, 1),
    // Button disabled
    buttonDisabledBackgroundColor: Color.rgba(100, 153, 0, 0.5),
    buttonDisabledBorderColor: Color.rgba(100, 153, 0, 0.5),
    buttonDisabledTextColor: Color.rgba(100, 153, 0, 0.5),
    // Header
    headerBackgroundColor: Color.rgba(0, 153, 0, 1.0),
    headerButtonTextColor: Color.rgba(0, 153, 0, 0.5),
    headerTextColor: Color.rgba(0, 255, 0, 1),
    // Input
    inputBackgroundColor: Color.rgba(0, 255, 0, 1),
    inputBorderColor: Color.hex('#ccc'),
    inputTextColor: Color.hex('#0f0'),
    // Others
    iconColor: Color.rgba(0, 255, 0, 1),
    textColor: Color.hex('#0f0'),
    titleColor: Color.hex('#0f0'),
    // Header
    statusBarStyle: StatusBarStyle.LightContent, // or StatusBarStyle.Default
  }
})
```

> To see the statusBarStyle reflected you must set the **UIViewControllerBasedStatusBarAppearance** property to **true** on your app's _Info.plist_ file.
> You can do it from XCode <img width="507" alt="screen shot 2016-08-02 at 11 44 07 am" src="https://cloud.githubusercontent.com/assets/1652196/17332979/0fa632b2-58a7-11e6-9aa3-a669ae44f2e6.png">

### Android

> Check [this commit](https://github.com/underscopeio/react-native-facebook-account-kit/commit/77df35ae20f251e7c29285e8820da2ff498d9400) to see how it's done in our sample app

1.  In your application _styles.xml_ file (usually located in _android/app/src/main/res/values_ folder) create a **Theme** with the following schema

```xml
<style name="LoginThemeYellow" parent="Theme.AccountKit">
    <item name="com_accountkit_primary_color">#f4bf56</item>
    <item name="com_accountkit_primary_text_color">@android:color/white</item>
    <item name="com_accountkit_secondary_text_color">#44566b</item>
    <item name="com_accountkit_status_bar_color">#ed9d00</item>

    <item name="com_accountkit_input_accent_color">?attr/com_accountkit_primary_color</item>
    <item name="com_accountkit_input_border_color">?attr/com_accountkit_primary_color</item>
</style>
```

> See the full set of customizable fields [here](https://developers.facebook.com/docs/accountkit/android/customizing)

2.  In your app _AndroidManifest.xml_ file (usually under _android/app/src/main_ folder) set that **Theme** to the **AccountKitActivity**

```xml
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools" <-- Add this line
    ...>

    <!-- Set the AccountKitActivity theme -->
    <activity
      tools:replace="android:theme"
      android:name="com.facebook.accountkit.ui.AccountKitActivity"
      android:theme="@style/LoginThemeYellow" />

</manifest>
```

## Troubleshooting

### Missing android.support.v4.content

```bash
error: package android.support.v4.content does not exist
import android.support.v4.content.ContextCompat;
```

This is because of the breaking change introduced in react-native **0.60.0** and therefore in our **2.0.0**.

In order to fix the issue you should either upgrade to react-native **0.60.0** of use the **1.2.0** of this library

Issue: [#196](https://github.com/underscopeio/react-native-facebook-account-kit/issues/167)


### I have problems running the example</summary>

If you have trouble running any example try the following:

1.  Move the example out of the repo
2.  Remove this package local dependency from `package.json`
    ```diff
    -    "react-native-facebook-account-kit": "file:../.."
    ```
3.  Run <code>yarn add react-native-facebook-account-kit</code>

4.  Re-run <code>react-native run-android</code> or <code>react-native run-ios</code>

### A system issue occured, Please try again" when sending SMS

1. Check your `FacebookAppID` and `AccountKitClientToken` on iOS `Info.plist` and Android `strings.xml` are correct

2. If you have enabled the **client access token flow in fb account kit dashboard**, then `responseType` should be set to `code` when calling `configure`

```javascript
// Configures the SDK with some options
RNAccountKit.configure({
    responseType: 'code'
    ...
})
```

Issue: [#68](https://github.com/underscopeio/react-native-facebook-account-kit/issues/68)

### iOS only: Login screen doesn't show up

In some cases, if you implement the Login button in a presented Modal screen, you need to add `viewControllerMode: 'show'` into the configuration.

```javascript
// Configures the SDK with some options
RNAccountKit.configure({
    viewControllerMode: 'show'
    ...
})
```

Issue: [#167](https://github.com/underscopeio/react-native-facebook-account-kit/issues/167)

### I cannot integrate the library with RN versions < 0.40.0

Modify the `android/build.gradle` file to override the `com.facebook.android:account-kit-sdk` library with `com.facebook.android:account-kit-sdk:4.15.0` and the `compileSdkVersion` and `buildToolsVersion` as depicted below

```java
subprojects { subproject ->
    afterEvaluate{
        dependencies {
            compile ('com.facebook.android:account-kit-sdk:4.15.0'){
                force = true
                exclude group: 'com.parse.bolts', module: 'bolts-android';
                exclude group: 'com.parse.bolts', module: 'bolts-applinks';
                exclude group: 'com.parse.bolts', module: 'bolts-tasks';
            }
        }

        if(subproject.name == 'react-native-facebook-account-kit') {
            android {
                compileSdkVersion 23
                buildToolsVersion "23.0.3"
            }
        }
    }
}
```

## License

License is MIT
