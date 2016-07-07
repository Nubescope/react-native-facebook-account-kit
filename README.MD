# react-native-facebook-account-kit

A Facebook Account Kit SDK wrapper for react-native (*>= 0.19.0*)

## Installation

If you already didn't install `rnpm`
```bash
npm install -g rnpm
```
Then install `react-native-facebook-account-kit` using `rnpm`
```bash
rnpm install react-native-facebook-account-kit
```

> We **strongly** recommend you to use [`rnpm`](https://github.com/rnpm/rnpm) that automatically installs the module from npm and links their native dependencies (for Android and/or iOS) with just one command:

If you prefer you can do it manually following [these steps](#manual-installation)

## Configuration

### For iOS

1. First, link the AccountKit SDK to your project following these steps
  - Open with XCode your project  
  - Open with Finder the `node_modules/react-native-facebook-account-kit/ios` folder  
  - Drag and drop `AccountKit.framework` and `AccountKitStrings.bundle` from Finder to your project in XCode (**IMPORTANT**: select the **"Copy items if needed"** option)  

2. Add your Facebook credentials to your project's `Info.plist` file
  ```
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
   ```
   ...
   <string name="fb_app_id">YOUR_FACEBOOK_APP_ID</string>
   <string name="ak_client_token">YOUR_CLIENT_TOKEN</string>
   ```

2. In `android/app/src/main/AndroidManifest.xml`
  ```
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

This is the minimal required configuration. Take a look to the [Account Kit documentation for Android](https://developers.facebook.com/docs/accountkit/android) for a more detailed guide.

## Themes
Regarding the theming, Account Kit way to customize styles differs between platforms.
### iOS
For iOS you must use the field `theme` on the configure payload and set the properties you want to overwrite.
```javascript
import RNAccountKit, {
  Color
} from 'react-native-facebook-account-kit'

RNAccountKit.configure({
  ...,
  theme: {
    backgroundColor: Color.rgba(0,120,0,0.1),
    buttonBackgroundColor: Color.rgba(0, 153, 0, 1.00),
    buttonBorderColor: Color.rgba(0,255,0,1),
    buttonTextColor: Color.rgba(0,255,0,1),
    buttonDisabledBackgroundColor: Color.rgba(100, 153, 0, 0.5),
    buttonDisabledBorderColor: Color.rgba(100, 153, 0, 0.5),
    buttonDisabledTextColor: Color.rgba(100, 153, 0, 0.5),
    headerBackgroundColor: Color.rgba(0, 153, 0, 1.00),
    headerTextColor: Color.rgba(0,255,0,1),
    iconColor: Color.rgba(0,255,0,1),
    inputBackgroundColor: Color.rgba(0,255,0,1),
    inputBorderColor: Color.hex('#ccc'),
    inputTextColor: Color.hex('#0f0'),
    textColor: Color.hex('#0f0'),
    titleColor: Color.hex('#0f0'),
    backgroundImage: 'background.png',
  }
})
```
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

Try the [sample](https://github.com/underscopeio/react-native-facebook-account-kit/tree/master/sample)

```bash
git clone https://github.com/underscopeio/react-native-facebook-account-kit
cd react-native-facebook-account-kit/sample
npm install
react-native run-ios # or react-native run-android
```

## License

License is MIT


## Manual Installation
First, install the module from npm

```
npm install react-native-facebook-account-kit --save
```

### For iOS

If you are using Cocoapods add the following line to your Podfile
```
pod 'RNAccountKit', :path => '../node_modules/react-native-facebook-account-kit'
```

If you are **not** using Cocoapods:  
1. Open your project in XCode, right click on `Libraries` and click `Add Files to "Your Project Name"` Look under `node_modules/react-native-facebook-account-kit` and add `RNAccountKit.xcodeproj`.  
2. Add `libRNAccountKit.a` to `Build Phases -> Link Binary With Libraries`.

### For Android

1. In `android/settings.gradle`
   ```
   ...
   include ':react-native-facebook-account-kit'
   project(':react-native-facebook-account-kit').projectDir = new File(rootProject.projectDir, '../node_modules/react-native-facebook-account-kit/android')
   ```

2. In `android/app/build.gradle` add:
   ```
   dependencies {
       ...
       compile project(':react-native-facebook-account-kit')
   }
   ```

3. And finally, in `android/src/main/java/com/{YOUR_APP_NAME}/MainActivity.java` add:
   ```java
   //...
   import io.underscope.react.fbak.RNAccountKitPackage; // <--- This!
   //...
   @Override
   protected List<ReactPackage> getPackages() {
     return Arrays.<ReactPackage>asList(
       new MainReactPackage(),
       new RNAccountKit() // <---- and This!
     );
  }
   ```
