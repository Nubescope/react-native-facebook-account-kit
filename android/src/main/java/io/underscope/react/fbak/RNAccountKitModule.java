package io.underscope.react.fbak;

import android.app.Activity;
import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import androidx.core.content.ContextCompat;
import android.util.Log;

import com.facebook.accountkit.AccessToken;
import com.facebook.accountkit.Account;
import com.facebook.accountkit.AccountKit;
import com.facebook.accountkit.AccountKitCallback;
import com.facebook.accountkit.AccountKitError;
import com.facebook.accountkit.AccountKitLoginResult;
import com.facebook.accountkit.PhoneNumber;
import com.facebook.accountkit.ui.AccountKitActivity;
import com.facebook.accountkit.ui.AccountKitConfiguration;
import com.facebook.accountkit.ui.LoginType;
import com.facebook.react.bridge.ActivityEventListener;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.WritableMap;

import java.util.ArrayList;
import java.util.List;

public class RNAccountKitModule extends ReactContextBaseJavaModule implements ActivityEventListener {

    private ReactApplicationContext reactContext;
    private Promise pendingPromise;
    private ReadableMap options;

    public static int APP_REQUEST_CODE = 99;
    public static String REACT_CLASS = "RNAccountKit";

    public RNAccountKitModule(ReactApplicationContext reactContext) {
        super(reactContext);

        this.reactContext = reactContext;
        this.reactContext.addActivityEventListener(this);


        AccountKit.initialize(reactContext.getApplicationContext());
    }

    @Override
    public String getName() {
        return REACT_CLASS;
    }


    /**
     * Activity event listeners
     */

    @Override
    public void onActivityResult(Activity activity, int requestCode, int resultCode, Intent data) {
        if (requestCode == APP_REQUEST_CODE) {
            if (data == null) {
                rejectPromise("error", new Error("Login failed"));
                return;
            }
            AccountKitLoginResult loginResult = data.getParcelableExtra(AccountKitLoginResult.RESULT_KEY);

            if (loginResult.getError() != null) {
                rejectPromise("error", new Error(loginResult.getError().getErrorType().getMessage()));
            } else if (loginResult.wasCancelled()) {
                rejectPromise("cancel", new Error("Login cancelled"));
            } else {
                if (loginResult.getAccessToken() != null) {
                    resolvePromise(mapToken(loginResult.getAccessToken()));
                } else {
                    WritableMap map = Arguments.createMap();
                    map.putString("code", loginResult.getAuthorizationCode());
                    map.putString("state", loginResult.getFinalAuthorizationState());

                    resolvePromise(map);
                }
            }
        }
    }



    /**
     * Exposed React's methods
     */

    @ReactMethod
    public void login(final String type, final Promise promise) {
        if (!AccountKit.isInitialized()) {
            Log.w(REACT_CLASS, "AccountKit not initialized yet. `login` call discarded");
            return;
        }

        if (this.options == null) {
            Log.e(REACT_CLASS, "You must call `configure` method providing configure options first");
            return;
        }

        this.pendingPromise = promise;

        final LoginType loginType = LoginType.valueOf(safeString(type.toUpperCase()));
        final Intent intent = new Intent(this.reactContext.getApplicationContext(), AccountKitActivity.class);
        final AccountKitConfiguration.AccountKitConfigurationBuilder configurationBuilder =
                createAccountKitConfiguration(loginType);
        intent.putExtra(AccountKitActivity.ACCOUNT_KIT_ACTIVITY_CONFIGURATION, configurationBuilder.build());
        try {
            this.reactContext.startActivityForResult(intent, APP_REQUEST_CODE, new Bundle());
        } catch (Error e) {
            rejectPromise("error", new Error("Login aborted"));
        }
    }

    @ReactMethod
    public void logout(final Promise promise) {
        if (!AccountKit.isInitialized()) {
            Log.w(REACT_CLASS, "AccountKit not initialized yet. `logout` call discarded");
            return;
        }

        AccountKit.logOut();
        promise.resolve(null);
    }

    @ReactMethod
    public void getCurrentAccessToken(final Promise promise) {
        if (!AccountKit.isInitialized()) {
            Log.w(REACT_CLASS, "AccountKit not initialized yet. `getCurrentAccessToken` call discarded");
            return;
        }

        AccessToken token = AccountKit.getCurrentAccessToken();
        promise.resolve(token != null ? mapToken(token) : null);
    }

    @ReactMethod
    public void getCurrentAccount(final Promise promise) {
        if (!AccountKit.isInitialized()) {
            Log.w(REACT_CLASS, "AccountKit not initialized yet. `getCurrentAccount` call discarded");
            return;
        }

        AccountKit.getCurrentAccount(new AccountKitCallback<Account>() {
            @Override
            public void onSuccess(Account account) {
                WritableMap map = Arguments.createMap();

                map.putString("id", account.getId());
                map.putString("email", account.getEmail());

                WritableMap phoneNumber = null;
                if (account.getPhoneNumber() != null) {
                    phoneNumber = Arguments.createMap();
                    phoneNumber.putString("number", account.getPhoneNumber().getPhoneNumber());
                    phoneNumber.putString("countryCode", account.getPhoneNumber().getCountryCode());
                }
                map.putMap("phoneNumber", phoneNumber);

                promise.resolve(map);
            }

            @Override
            public void onError(AccountKitError error) {
                promise.reject("error", new Error(error.getErrorType().getMessage()));
            }
        });

    }

    /**
     * Set configuration params for Account Kit.
     * Validation and defaults values expected to be done in React side.
     *
     * @param options attrs are:
     *     responseType                 :'CODE|TOKEN'
     *     titleType                    :'APP_NAME|LOGIN'
     *     initialAuthState             :String
     *     facebookNotificationsEnabled :Boolean
     *     readPhoneStateEnabled        :Boolean
     *     countryBlacklist             :String[]
     *     countryWhitelist             :String[]
     *     defaultCountry               :String
     */

    @ReactMethod
    public void configure(final ReadableMap options) {
        this.options = options;
    }


    /**
     * Private methods
     */

    private AccountKitConfiguration.AccountKitConfigurationBuilder createAccountKitConfiguration(
            final LoginType loginType) {
        AccountKitConfiguration.AccountKitConfigurationBuilder configurationBuilder =
                new AccountKitConfiguration.AccountKitConfigurationBuilder(loginType,
                        AccountKitActivity.ResponseType.valueOf(
                                safeString(this.options.getString("responseType").toUpperCase())));

        configurationBuilder.setTitleType(
                AccountKitActivity.TitleType.valueOf(safeString(this.options.getString("titleType").toUpperCase())));

        String initialAuthState = this.options.getString(("initialAuthState"));
        if (!initialAuthState.isEmpty()) {
            configurationBuilder.setInitialAuthState(initialAuthState);
        }

        String initialEmail = this.options.getString("initialEmail");
        if (initialEmail != null && !initialEmail.isEmpty()) {
            configurationBuilder.setInitialEmail(initialEmail);
        }

        String initialPhoneCountryPrefix = this.options.getString("initialPhoneCountryPrefix");
        String initialPhoneNumber = this.options.getString("initialPhoneNumber");

        PhoneNumber phoneNumber = new PhoneNumber(initialPhoneCountryPrefix, initialPhoneNumber, null);
        configurationBuilder.setInitialPhoneNumber(phoneNumber);

        configurationBuilder.setFacebookNotificationsEnabled(
                this.options.getBoolean("facebookNotificationsEnabled"));

        boolean readPhoneStateEnabled = this.options.getBoolean("readPhoneStateEnabled");
        if (readPhoneStateEnabled && PackageManager.PERMISSION_DENIED == ContextCompat.checkSelfPermission(
                        reactContext.getApplicationContext(), Manifest.permission.READ_PHONE_STATE)) {
            Log.w(REACT_CLASS, "To allow reading phone number add READ_PHONE_STATE permission in your app's manifest");
            configurationBuilder.setReadPhoneStateEnabled(false);
        } else {
            configurationBuilder.setReadPhoneStateEnabled(readPhoneStateEnabled);
        }

        boolean setEnableInitialSmsButton = this.options.getBoolean("setEnableInitialSmsButton");
        configurationBuilder.setEnableInitialSmsButton(setEnableInitialSmsButton);

        if (this.options.hasKey("countryBlacklist")) {
            String[] blacklist = formatCountryList(this.options.getArray("countryBlacklist"));
            configurationBuilder.setSMSBlacklist(blacklist);
        }

        if (this.options.hasKey("countryWhitelist")) {
            String[] whitelist = formatCountryList(this.options.getArray("countryWhitelist"));
            configurationBuilder.setSMSWhitelist(whitelist);
        }

        if (this.options.hasKey("defaultCountry")) {
            configurationBuilder.setDefaultCountryCode(this.options.getString("defaultCountry"));
        }

        return configurationBuilder;
    }

    private void rejectPromise(String code, Error err) {
        if (this.pendingPromise != null) {
            this.pendingPromise.reject(code, err);
            this.pendingPromise = null;
        }
    }

    private void resolvePromise(Object data) {
        if (this.pendingPromise != null) {
            this.pendingPromise.resolve(data);
            this.pendingPromise = null;
        }
    }

    private WritableMap mapToken(AccessToken token) {
        WritableMap map = Arguments.createMap();

        map.putString("accountId", token.getAccountId());
        map.putString("appId", token.getApplicationId());
        map.putString("token", token.getToken());
        map.putString("lastRefresh", Long.toString(token.getLastRefresh().getTime()));
        map.putString("refreshIntervalSeconds", Long.toString(token.getTokenRefreshIntervalSeconds()));

        return map;
    }

    private String[] formatCountryList(ReadableArray list) {
        List<String> pre = new ArrayList<>();
        for (int i=0,n=list.size();i<n;i++) {
            pre.add(list.getString(i));
        }

        String[] out = new String[pre.size()];
        return pre.toArray(out);
    }

    public void onNewIntent(Intent intent) {
    }

    //  Replace Turkish İ and ı with their normalized versions (I and i, respectively)
    private String safeString (String str) {
      return str.replace("İ", "I").replace("ı", "i");
    }
}
