import React, { Fragment } from 'react'
import { StyleSheet, Text, TouchableOpacity } from 'react-native'

export default function({ onLoginWithPhonePress, onLoginWithEmailPress }) {
  return (
    <Fragment>
      <TouchableOpacity style={styles.button} onPress={onLoginWithPhonePress}>
        <Text style={styles.buttonText}>Login with SMS</Text>
      </TouchableOpacity>

      <TouchableOpacity style={styles.button} onPress={onLoginWithEmailPress}>
        <Text style={styles.buttonText}>Login with Email</Text>
      </TouchableOpacity>
    </Fragment>
  )
}

const styles = StyleSheet.create({
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
})
