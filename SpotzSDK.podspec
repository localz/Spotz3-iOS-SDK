Pod::Spec.new do |s|
	s.name	= 'SpotzSDK'
	s.platform = :ios,'8.0'
	s.ios.deployment_target = '8.0'
	s.license = {
		:type => 'Commercial',
		:text => <<-LICENSE
			Copyright 2015 Localz Pty Ltd.
			LICENSE
	}
	s.version = '3.1.0.5'
	s.summary = 'iOS library for Localz Platform'
	s.homepage = 'http://localz.com'
	s.author = { 'Localz Pty Ltd' => 'info@localz.com' }
	s.xcconfig = { 'FRAMEWORK_SEARCH_PATHS' => '$(inherited)' }
	s.preserve_paths = 'SpotzSDK.framework'
	s.vendored_frameworks = 'SpotzSDK/SpotzSDK.framework'
	s.requires_arc = true
	s.ios.deployment_target = '8.0'
	s.frameworks = 'CoreLocation','SystemConfiguration','Foundation'
	s.dependency 'AFNetworking'
	s.dependency 'CocoaLumberjack'
	s.dependency 'YapDatabase'
end
