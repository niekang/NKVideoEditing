
Pod::Spec.new do |spec|

  spec.name         = "TestLib"
  spec.version      = "0.0.4"
  spec.summary      = "Test Pod"
  spec.description  = "Test Lib Pod"

  spec.homepage     = "https://github.com/niekang/TestLib"
  spec.license      = { :type => "MIT", :file => "LICENSE" }
  spec.author       = {"聂康" => "18501047699@163.com" }
  spec.platform     = :ios, "8.0"

  spec.source       = {
    :git => "https://github.com/niekang/TestLib.git",
    :tag => "#{spec.version}" }
  
  spec.source_files = "TestLib/Classes/**/*"
  spec.vendored_frameworks = "TestLib/Vendor/*.framework"

  #spec.public_header_files = "Classes/**/*.h"
  # spec.resource  = "icon.png"
  # spec.resources = "Resources/*.png"
  # spec.framework  = "SomeFramework"
  # spec.frameworks = "SomeFramework", "AnotherFramework"
  # spec.library   = "iconv"
  # spec.libraries = "iconv", "xml2"

  # spec.dependency "JSONKit", "~> 1.4"

end
