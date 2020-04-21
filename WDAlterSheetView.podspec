
Pod::Spec.new do |s|
s.name             = "WDAlterSheetView"
s.version          = "1.0.0"
s.summary          = "底部弹窗"
s.description      = "iOS Objective-C 底部弹窗"
s.homepage         = "https://github.com/wuvdan/WDAlterSheetView"
s.license          = 'MIT'
s.author           = { "wudan" => "wuvdan@163.com" }
s.source           = { :git => "https://github.com/wuvdan/WDAlterSheetView.git", :tag => "#{s.version}"}
s.platform         = :ios, '9.0'
s.requires_arc     = true
s.source_files     = "WDAlterSheetView", "*.{h,m}"
s.frameworks       = 'UIKit'
end
