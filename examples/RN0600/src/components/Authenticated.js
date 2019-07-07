import React, { Fragment } from 'react'
import { StyleSheet, Text, TouchableOpacity } from 'react-native'

export default function({ token, user, onLogoutPress }) {
  const { id, email, phoneNumber } = user

  return (
    <Fragment>
      <Text style={styles.label}>Account Kit Id</Text>
      <Text style={styles.text}>{id}</Text>
      <Text style={styles.label}>Email</Text>
      <Text style={styles.text}>{email || 'N/A'}</Text>
      <Text style={styles.label}>Phone Number</Text>
      <Text style={styles.text}>{phoneNumber ? `${phoneNumber.countryCode} ${phoneNumber.number}` : 'N/A'}</Text>
      <Text style={styles.label}>Token</Text>
      <Text style={styles.text}>{JSON.stringify(token)}</Text>

      <TouchableOpacity style={styles.button} onPress={onLogoutPress}>
        <Text style={styles.buttonText}>Logout</Text>
      </TouchableOpacity>
    </Fragment>
  )
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },

  button: {
    height: 50,
    width: 300,
    backgroundColor: '#3581D8',
    marginBottom: 10,
  },

  buttonText: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
    color: '#EFEFEF',
    fontWeight: 'bold',
  },

  label: {
    fontSize: 20,
    textAlign: 'center',
    fontWeight: 'bold',
    marginTop: 20,
  },

  text: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
})
