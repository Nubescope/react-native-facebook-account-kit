import React, { Component } from 'react';
import { NativeModules, DeviceEventEmitter, TouchableHighlight, Text, Platform } from 'react-native'

const RNAccountKitNative = NativeModules.RNAccountKit

class RNAccountKit {
  static configDefaults = {
    responseType: 'token',
    titleType: 'login',
    initialAuthState: '',
    facebookNotificationsEnabled: true,
    readPhoneStateEnabled: true,
    receiveSMS: true,
    SMSBlacklist: [],
    SMSWhitelist: []
  };

  constructor() {
    this.configure()
  }

  configure(options) {
    const configOptions = {
      ...RNAccountKit.configDefaults,
      ...options,
    }

    return RNAccountKitNative.configure(configOptions)
  }

  loginWithPhone() {
    return RNAccountKitNative.login('phone')
  }

  loginWithEmail() {
    return RNAccountKitNative.login('email')
  }

  getCurrentAccount() {
    return RNAccountKitNative.getCurrentAccount()
  }

  getCurrentAccessToken() {
    return RNAccountKitNative.getCurrentAccessToken()
  }

  logout() {
    return RNAccountKitNative.logout()
  }
}

const AccountKit = new RNAccountKit()

export class LoginButton extends Component {
  static propTypes = {
    type: React.PropTypes.string,
    onLogin: React.PropTypes.func.isRequired,
    onError: React.PropTypes.func.isRequired,
    onCancel: React.PropTypes.func
  };

  static defaultProps = {
    type: 'phone'
  };

  onPress() {
    const login = this.props.type.toLowerCase() == 'email' ?
      AccountKit.loginWithEmail : AccountKit.loginWithPhone

    login()
      .then((data) => {
        this.props.onLogin(data)
      })
      .catch((err) => {
        if (err.code == 'cancel') {
          this.props.onCancel && this.props.onCancel(err)
        } else {
          this.props.onError(err)
        }
      })
  }

  constructor(props) {
    super(props)
  }

  render() {
    return (
      <TouchableHighlight style={this.props.style} onPress={() => { this.onPress() }}>
        {this.props.children}
      </TouchableHighlight>
    )
  }
}

export default AccountKit
