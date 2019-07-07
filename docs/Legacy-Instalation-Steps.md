# Legacy Installation Steps 

The following document describes the installation steps for **React Native** versions prior to **0.60.x**

## Installation

```shell
yarn add react-native-facebook-account-kit
```

## Linking

```shell
react-native link react-native-facebook-account-kit
```

### Android manual steps

Check the `RNAccountKitPackage` is registered in your `MainApplication.java` file. This should be done by `react-native link` but sometimes it doesn't. You should see something like the following

```java
@Override
protected List<ReactPackage> getPackages() {
    return Arrays.<ReactPackage>asList(
        new MainReactPackage(),
        new RNAccountKitPackage() // <-- the package is registered
    );
}
```

### IOS manual steps using Cocoapods (Recomended)

1.  Undo changes in `ios` folder (which were made by `react-native-link`) in order to avoid duplicate compilations

        git checkout -- ios

2.  Add `RNAccountKit` Pod to your Podfile (if you don't have a podfile follow [these](http://facebook.github.io/react-native/docs/0.51/integration-with-existing-apps.html#configuring-cocoapods-dependencies) instructions)

    ```diff
    target 'MyApp' do
      ...
    +  pod 'RNAccountKit', :path => '../node_modules/react-native-facebook-account-kit/ios'
      ...
    end
    ```

3.  Run `pod install` in your `ios` folder

### IOS manual steps without Cocoapods (Not recomended)

1. Open your project with XCode

2. Open with Finder the `node_modules/react-native-facebook-account-kit/ios` folder

3. Drag and drop `AccountKit.framework` and `AccountKitStrings.bundle` from Finder to your project in XCode (**IMPORTANT**: **unselect** the **"Copy items if needed"** option)
4. Select you app target on XCode and click the `Build Settings` tab. Go to the `Framework Search Paths` section and add this new entry
   ```bash
     $(SRCROOT)/../node_modules/react-native-facebook-account-kit/ios
   ```

> NOTE: We strongly recomend using **cocoapods** that's why on version **1.2.0** we removed the `AccountKit.framework` / `AccountKitStrings.bundle` files from the project. If you don't want to use **cocoapods** you can still download the framework and the bundle [from here](https://github.com/facebook/facebook-objc-sdk/releases/download/v5.0.1/AccountKit.zip) and add it to your project by yourself.
