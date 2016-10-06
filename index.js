import React, {
  Component
} from 'react'

import {
  NativeModules,
  DeviceEventEmitter,
  TouchableOpacity,
  Text,
  Platform
} from 'react-native'

const RNAccountKitNative = NativeModules.RNAccountKit

class RNAccountKit {
  static configDefaults = {
    responseType: 'token',
    titleType: 'login',
    initialAuthState: '',
    initialEmail: '',
    facebookNotificationsEnabled: true,
    readPhoneStateEnabled: true,
    receiveSMS: true,
    theme: {}
  }

  constructor() {
    RNAccountKitNative && this.configure()
  }

  configure(options = {}) {
    for(key of Object.keys(options)) {
      options[key] || delete options[key]
    }

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
      <TouchableOpacity style={this.props.style} onPress={() => { this.onPress() }}>
        {this.props.children}
      </TouchableOpacity>
    )
  }
}

export class Color {
  static rgba(r,g,b,a) {
    return {r:r/255,g:g/255,b:b/255,a}
  }
  static rgb(r,g,b) {
    return this.rgba(r,g,b,1);
  }
  static hex(hex) {
    hex = hex.replace(/^#/, '');
    if (hex.length === 3) {
      hex = hex[0] + hex[0] + hex[1] + hex[1] + hex[2] + hex[2];
    }
    var num = parseInt(hex, 16);
    return this.rgba(num >> 16, num >> 8 & 255, num & 255,1);
  }
}

export const StatusBarStyle = {
  Default: 0,
  LightContent: 1,
}

export default AccountKit
