require 'json'

package = JSON.parse(File.read(File.join(__dir__, 'package.json')))

Pod::Spec.new do |s|
  s.name         = "RNAccountKit"
  s.version      = package['version']
  s.summary      = package['description']

  s.authors      = "Underscope"
  s.homepage     = 'https://github.com/underscopeio/'
  s.license      = package['license']
  s.platform     = :ios, "9.0"

  s.module_name  = 'RNAccountKit'

  s.source       = { :git => "https://github.com/underscopeio/react-native-facebook-account-kit", :tag => "v#{s.version}" }
  s.source_files  = "ios/**/*.{h,m}"
  s.exclude_files  = "ios/AccountKit.framework/**/*.*"
  s.header_mappings_dir = 'ios'
  s.public_header_files = "ios/*.h"

  s.dependency 'React'
  s.dependency 'AccountKit'
end
