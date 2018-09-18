# react-native-facebook-account-kit

A Facebook Account Kit SDK wrapper for react-native.

## Supported versions - React Native / Facebook Account Kit

> The table below shows the supported versions of React Native and the different versions of `react-native-facebook-account-kit`.

| React Native Facebook Account Kit | 0.4.x | 0.6.x | 0.10.x  | 1.0.x |
| --------------------------------- | :---: | :---: | :-----: | ----- |
| React Native                      | 0.24  | <0.48 | 0.48-56 | 0.57  |

> For RN <0.40.0 Check the Troubleshooting Guide

## Installation

```shell
yarn add react-native-facebook-account-kit
```

## Linking

### Semi-automatic (suggested)

```shell
react-native link react-native-facebook-account-kit
```

<details>
    <summary>Android</summary>

- _Done!_

</details>

<details>
    <summary>iOS (via Cocoapods)</summary>

1.  Undo changes in iOS folder (which were made by `react-native-link`) in order to avoid duplicate compilations

        git checkout ios

2.  Add `RNAccountKit` Pod to your Podfile (if you don't have a podfile follow [these](http://facebook.github.io/react-native/docs/0.51/integration-with-existing-apps.html#configuring-cocoapods-dependencies) instructions)

    ```diff
    target 'MyApp' do
      ...
    +  pod 'RNAccountKit', :path => '../node_modules/react-native-facebook-account-kit/ios'
      ...
    end
    ```

3.  Run `pod install` in your `ios` folder

</details>

<details>
    <summary>iOS (without Cocoapods)</summary>

1.  Open your project with XCode

2.  Open with Finder the `node_modules/react-native-facebook-account-kit/ios` folder

3.  Drag and drop `AccountKit.framework` and `AccountKitStrings.bundle` from Finder to your project in XCode (**IMPORTANT**: select the **"Copy items if needed"** option)

</details>

<br/>

## Configuration

<details>
    <summary>iOS</summary>
    <br/>

Add your Facebook credentials to your project's `Info.plist` file

```xml
  <plist version="1.0">
    <dict>
      ...
      <key>FacebookAppID</key>
      <string>{your-app-id}</string>
      <key>AccountKitClientToken</key>
      <string>{your-account-kit-client-token}</string>
      <key>CFBundleURLTypes</key>
      <array>
        <dict>
          <key>CFBundleURLSchemes</key>
          <array>
            <string>ak{your-app-id}</string>
          </array>
        </dict>
      </array>
      ...
    </dict>
  </plist>
```

_This is the minimal required configuration. Take a look to the [Account Kit documentation for iOS](https://developers.facebook.com/docs/accountkit/ios) for a more detailed guide._

</details>

<details>
    <summary>Android</summary>
    <br/>

1.  In `android/app/src/main/res/values/strings.xml`

```xml
...
<string name="fb_app_id">YOUR_FACEBOOK_APP_ID</string>
<string name="ak_client_token">YOUR_CLIENT_TOKEN</string>
```

2.  In `android/app/src/main/AndroidManifest.xml`

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

3.  Check the `RNAccountKitPackage` is registered in your `MainApplication.java` file. This should be done by `react-native link` but sometimes it doesn't. You should see something like the following

```java
@Override
protected List<ReactPackage> getPackages() {
    return Arrays.<ReactPackage>asList(
        new MainReactPackage(),
        new RNAccountKitPackage() // <-- the package is registered
    );
}
```

_This is the minimal required configuration. Take a look to the [Account Kit documentation for Android](https://developers.facebook.com/docs/accountkit/android) for a more detailed guide._

#### (Optional) Exclude backup for Access Tokens on Android >= 6.0

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

</details>

## Themes

<details>
    <summary>iOS</summary>

<br/>

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

</details>

<details>
    <summary>Android</summary>

<br/>

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

</details>

## Usage

> If you have issues with the method signatures you may be using an older version. Check the [Releases Notes](https://github.com/underscopeio/react-native-facebook-account-kit/releases) for breaking changes

```javascript
import RNAccountKit from 'react-native-facebook-account-kit'

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

// Configures the SDK with some options
RNAccountKit.configure({
  responseType: 'token'|'code' // 'token' by default,
  titleType: 'login',
  initialAuthState: '',
  initialEmail: 'some.initial@email.com',
  initialPhoneCountryPrefix: '+1', // autodetected if none is provided
  initialPhoneNumber: '123-456-7890',
  facebookNotificationsEnabled: true|false, // true by default
  readPhoneStateEnabled: true|false, // true by default,
  receiveSMS: true|false, // true by default,
  countryWhitelist: ['AR'], // [] by default
  countryBlacklist: ['US'], // [] by default
  defaultCountry: 'AR',
  theme: {...} // for iOS only, see the Theme section
})
```

## Examples

Try the [examples](https://github.com/underscopeio/react-native-facebook-account-kit/tree/master/examples).
They are related to different React Native versions.

```bash
git clone https://github.com/underscopeio/react-native-facebook-account-kit
cd react-native-facebook-account-kit/examples/RN033 # or /RN024
yarn
react-native run-ios # or react-native run-android
```

## Troubleshooting

<details>
    <summary>I have problems running the example</summary>
<br/>

If you have trouble running any example try the following:

1.  Move the example out of the repo
2.  Remove this package local dependency from `package.json`
    ```diff
    -    "react-native-facebook-account-kit": "file:../.."
    ```
3.  Run <code>yarn react-native-facebook-account-kit</code>

4.  Re-run <code>react-native run-android</code> or <code>react-native run-ios</code>

</details>

<details>
    <summary>"A system issue occured, Please try again" when sending SMS</summary>  
<br/>

A. Check your `FacebookAppID` and `AccountKitClientToken` on iOS `Info.plist` and Android `strings.xml` are correct

B. If you have enabled the **client access token flow in fb account kit dashboard**, then `responseType` should be set to `code` when calling `configure`

```javascript
// Configures the SDK with some options
RNAccountKit.configure({
    responseType: 'code'
    ...
})
```

Issue: [#68](https://github.com/underscopeio/react-native-facebook-account-kit/issues/68)

</details>

<details>
    <summary>I cannot integrate the library with RN versions < 0.40.0</summary>
<br/>

A. Modify the `android/build.gradle` file to override the `com.facebook.android:account-kit-sdk` library with `com.facebook.android:account-kit-sdk:4.15.0` and the `compileSdkVersion` and `buildToolsVersion` as depicted below

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

</details>

## License

License is MIT
