const path = require('path')
const defaultConfig = require('react-native/local-cli/default.config.js')
const blacklist = require('react-native/packager/blacklist')

module.exports = {
  // NOTE: this allows the sample project import the library as external,
  // using import * from 'react-native-facebook-account-kit'
  getProjectRoots() {
    const roots = defaultConfig.getProjectRoots()
    roots.unshift(path.resolve(__dirname, `../`))
    return roots
  },
  
  // NOTE: this prevents the collision between the library and sample's react-native module
  getBlacklistRE(platform) {
    return blacklist(platform, [
      /react-native-facebook-account-kit\/node_modules\/react-native\/.*/
    ])
  }
}
