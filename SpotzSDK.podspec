Pod::Spec.new do |s|
	s.name	= 'SpotzSDK'
	s.platform = :ios,'9.0'
	s.ios.deployment_target = '9.0'
	s.license = {
		:type => 'Commercial',
		:text => <<-LICENSE
			Copyright 2018 Localz Pty Ltd.
			LICENSE
	}
	s.version = '3.2.10'
	s.summary = 'iOS library for Localz Platform'
	s.homepage = 'http://localz.com'
	s.author = { 'Localz Pty Ltd' => 'info@localz.com' }
	s.xcconfig = { 'FRAMEWORK_SEARCH_PATHS' => '$(inherited)' }
	s.preserve_paths = 'SpotzSDK.framework'
	s.vendored_frameworks = 'SpotzSDK/SpotzSDK.framework'
	s.requires_arc = true
	s.source = { :git => 'https://github.com/localz/Spotz3-iOS-SDK.git' }
    s.resource = 'SpotzSDK/**/*.der'
	s.frameworks = 'CoreLocation','SystemConfiguration','Foundation'
	s.dependency 'YapDatabase/Standard/Core'
    s.dependency 'TrustKit'
end
