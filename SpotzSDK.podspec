Pod::Spec.new do |s|
	s.name	= 'SpotzSDK'
	s.platform = :ios,'10.0'
	s.ios.deployment_target = '10.0'
	s.license = {
		:type => 'Commercial',
		:text => <<-LICENSE
			Copyright 2020 Localz Pty Ltd.
			LICENSE
	}
	s.version = '4.0.2'
	s.summary = 'iOS library for Localz Platform'
	s.homepage = 'http://localz.com'
	s.author = { 'Localz Pty Ltd' => 'info@localz.com' }
	s.xcconfig = { 'FRAMEWORK_SEARCH_PATHS' => '$(inherited)'}
	s.preserve_paths = 'SpotzSDK.framework'
	s.vendored_frameworks = 'SpotzSDK/SpotzSDK.framework'
	s.requires_arc = true
	s.source = { :git => 'https://github.com/localz/Spotz3-iOS-SDK.git' }
	s.frameworks = 'CoreLocation','SystemConfiguration','Foundation'
	s.dependency 'YapDatabase/Standard/Core', '4.0.1'
end
