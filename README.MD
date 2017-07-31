# react-native-facebook-account-kit

A Facebook Account Kit SDK wrapper for react-native.
> We will support the latest version of React Native on each release. For older RN versions you may use an older version of this module compatible with that RN version.

## Installation

```bash
npm install --save react-native-facebook-account-kit
react-native link react-native-facebook-account-kit
```

## Configuration

### For iOS

1. First, link the AccountKit SDK to your project following these steps
  - Open with XCode your project
  - Open with Finder the `node_modules/react-native-facebook-account-kit/ios` folder
  - Drag and drop `AccountKit.framework` and `AccountKitStrings.bundle` from Finder to your project in XCode (**IMPORTANT**: select the **"Copy items if needed"** option)

2. Add your Facebook credentials to your project's `Info.plist` file
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
3. Done! Now run your project from XCode or with `react-native run-ios` from your terminal

This is the minimal required configuration. Take a look to the [Account Kit documentation for iOS](https://developers.facebook.com/docs/accountkit/ios) for a more detailed guide.

### For Android

1. In `android/app/src/main/res/values/strings.xml`
   ```xml
   ...
   <string name="fb_app_id">YOUR_FACEBOOK_APP_ID</string>
   <string name="ak_client_token">YOUR_CLIENT_TOKEN</string>
   ```

2. In `android/app/src/main/AndroidManifest.xml`
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
   </application>
   ...
   ```

3. Check the `RNAccountKitPackage` is registered in your `MainApplication.java` file. This should be done by `react-native link` but sometimes it doesn't. You should see something like the following
  ```java
  @Override
  protected List<ReactPackage> getPackages() {
      return Arrays.<ReactPackage>asList(
          new MainReactPackage(),
          new RNAccountKitPackage() // <-- the package is registered
      );
  }
  ```

This is the minimal required configuration. Take a look to the [Account Kit documentation for Android](https://developers.facebook.com/docs/accountkit/android) for a more detailed guide.

## Themes
Regarding the theming, Account Kit way to customize styles differs between platforms.
### iOS
For iOS you must use the field `theme` on the configure payload and set the properties you want to overwrite.
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
For Android you need to follow this steps:
> Check [this commit](https://github.com/underscopeio/react-native-facebook-account-kit/commit/77df35ae20f251e7c29285e8820da2ff498d9400) to see how it's done in our sample app

1. In your application _styles.xml_ file (usually located in _android/app/src/main/res/values_ folder) create a **Theme** with the following schema
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

2. In your app _AndroidManifest.xml_ file (usually under _android/app/src/main_ folder) set that **Theme** to the **AccountKitActivity**
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

## Usage
> If you have issues with the method signatures you may be using an older version. Check the [Releases Notes]( https://github.com/underscopeio/react-native-facebook-account-kit/releases) for breaking changes

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
  initialPhoneCountryPrefix: '+1',
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
npm install
react-native run-ios # or react-native run-android
```

## License

License is MIT
