Pod::Spec.new do |s|
  s.name             = "react-native-facebook-account-kit"
  s.version          = "0.0.1"
  s.summary          = "React Native library for Facebook Account Kit"
  s.author       = { 'Gonzalo Aguirre' => 'aguirre.gonzalo@gmail.com' }
  s.license      = 'MIT'
  s.homepage     = 'https://github.com/underscopeio/react-native-facebook-account-kit'
  s.source       = { :git => "https://github.com/underscopeio/react-native-facebook-account-kit.git" }
  s.platform     = :ios, "7.0"
  s.dependency 'React'
  s.source_files     = "*.{h,m}"
  s.preserve_paths   = "*.js"
end