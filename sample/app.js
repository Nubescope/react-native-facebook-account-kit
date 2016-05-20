import React, { Component, StyleSheet, Text, View, TouchableHighlight } from 'react-native'
import AccountKit, { LoginButton } from 'react-native-facebook-account-kit'

class AccountKitSample extends Component {
  state = {
    authToken: null,
    loggedAccount: null
  }

  componentWillMount() {
    AccountKit.getCurrentAccessToken()
      .then((token) => {
        if (token) {
          AccountKit.getCurrentAccount()
            .then((account) => {
              this.setState({
                authToken: token,
                loggedAccount: account
              })
            })
        } else {
          console.log('No user account logged')
        }
      })
      .catch((e) => console.log('Failed to get current access token', e))
  }

  onLogin(token) {
    AccountKit.getCurrentAccount()
      .then((account) => {
        this.setState({
          authToken: token,
          loggedAccount: account
        })
      })
  }

  onLoginError(e) {
    console.log('Failed to login', e)
  }

  onEmailLoginPressed() {
    AccountKit.loginWithEmail()
      .then((token) => { this.onLogin(token) })
      .catch((e) => this.onLoginError(e))
  }

  onLogoutPressed() {
    AccountKit.logout()
      .then(() => {
        this.setState({
          authToken: null,
          loggedAccount: null
        })
      })
      .catch((e) => console.log('Failed to logout'))
  }

  renderUserLogged() {
    const { id, email, phoneNumber } = this.state.loggedAccount;
    
    return (
      <View>
        <TouchableHighlight style={styles.button} onPress={() => this.onLogoutPressed()}>
          <Text style={styles.buttonText}>Logout</Text>
        </TouchableHighlight>

        <Text style={styles.label}>Account Kit Id</Text>
        <Text style={styles.text}>{id}</Text>
        <Text style={styles.label}>Email</Text>
        <Text style={styles.text}>{email}</Text>
        <Text style={styles.label}>Phone Number</Text>
        <Text style={styles.text}>{phoneNumber ? `${phoneNumber.countryCode} ${phoneNumber.number}` : ''}</Text>
      </View>
    )
  }

  renderLogin() {
    return (
      <View>
        <LoginButton style={styles.button} type="phone"
          onLogin={(token) => this.onLogin(token)} onError={(e) => this.onLogin(e)}>
          <Text style={styles.buttonText}>SMS</Text>
        </LoginButton>

        <TouchableHighlight style={styles.button} onPress={() => this.onEmailLoginPressed()}>
          <Text style={styles.buttonText}>Email</Text>
        </TouchableHighlight>
      </View>
    )
  }

  render() {
    return (
      <View style={styles.container}>
        { this.state.loggedAccount ? this.renderUserLogged() : this.renderLogin() }
      </View>
    )
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  button: {
    height: 50,
    width: 300,
    backgroundColor: 'aqua',
    marginBottom: 10
  },
  buttonText: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  label: {
    fontSize: 20,
    textAlign: 'center',
    fontWeight: 'bold',
    marginTop: 20
  },
  text: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  }
})

export default AccountKitSample