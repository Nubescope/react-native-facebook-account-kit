# react-native-facebook-account-kit

A Facebook Account Kit SDK wrapper for react-native (*>= 0.19.0*)

## Add it to your project

We strongly recommend you to use [`rnpm`](https://github.com/rnpm/rnpm) that automatically installs the module from npm and links their native dependencies (for Android and/or iOS) with just one command:

`rnpm link react-native-facebook-account-kit`

Anyway, you can do it manually following the steps described below:

First, install the module from npm

`npm install react-native-facebook-account-kit --save`

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
   import io.underscope.react.RNAccountKit; // <--- This!
   //...
   @Override
   protected List<ReactPackage> getPackages() {
     return Arrays.<ReactPackage>asList(
       new MainReactPackage(),
       new RNAccountKit() // <---- and This!
     );
}
   ```

### Usage

```javascript
import RNAccountKit from 'react-native-facebook-account-kit'

// Shows the Facebook Account Kit view for login via SMS
RNAccountKit.loginWithPhone()
  .then((token) => {
    console.log(`Logged with phone. Token: ${token}`)
  })

// Shows the Facebook Account Kit view for login via email
RNAccountKit.loginWithEmail()
  .then((token) => {
    console.log(`Logged with email. Token: ${token}`)
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
  SMSBlacklist: ['US'], // [] by default
  SMSWhitelist: ['AR'] // [] by default
})
```

### Examples

See the [sample](https://github.com/underscopeio/react-native-facebook-account-kit/tree/master/sample)

### License

License is MIT
