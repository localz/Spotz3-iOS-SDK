//
//  SpotzConstant.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 9/08/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef enum {
    SLNotDetermined = 0, // User has not authorized this application
    SLAuthorized = 1, // Authorization granted
    SLDenied = 2 // Authorization denied
} SpotzLocationServicesState;

/**
 *  Notification when spotz is found. SpotzData object of the triggered Spot is available in userInfo["data"].
 */
extern NSString * const SpotzInsideNotification;
extern NSString * const SPOTZ_INSIDE_NOTIFICATION;

/**
 *  Notification when previously found spotz is no longer detected. SpotzData object of the triggered Spot is available in userInfo["data"].
 */
extern NSString * const SpotzOutsideNotification;
extern NSString * const SPOTZ_OUTSIDE_NOTIFICATION;

/**
 *  Notification when ranging information available. SpotzData object of the triggered Spot is available in userInfo["data"].
 */
extern NSString * const SpotzRangingNotification;
extern NSString * const SPOTZ_RANGING_NOTIFICATION;

/**
 *  Notification when ranging information available. This works on top of data collected from SpotzRangingNotification data.
 */
extern NSString * const SpotzClosestBeaconNotification;
extern NSString * const SPOTZ_CLOSEST_BEACON_NOTIFICATION;

/**
 *  Notification when site geofence is enabled, and enter event is detected. SpotzSiteDetails object is available in userInfo["data"].
 */
extern NSString * const SpotzInsideSiteGeoNotification;
extern NSString * const SPOTZ_INSIDE_SITE_GEO_NOTIFICATION;

/**
 *  Notification when site geofence is enabled, and exit event is detected. SpotzSiteDetails object is available in userInfo["data"].
 */
extern NSString * const SpotzOutsideSiteGeoNotification;
extern NSString * const SPOTZ_OUTSIDE_SITE_GEO_NOTIFICATION;

/**
 *  Notification when a returned data exists during enter/exit Spot events.
 *  When available and enabled, the response from the extension call is available in userInfo["response"].
 *  response is nil if there was any error and empty NSDictionary object if there was no response/event is not enabled
 *  You will need to link the extension to the spot in order to receive a response. See Spotz's console.
 *
 *  The format of the response is @{@"extResp":@"<spotId>":@"<response>"}
 *
 *  NOTE:
 *  If multiple events occur for the same spot when offline, when device is back online, 
 *  Spotz only returns the last response from the third party even when there were multiple events during offline.
 */
extern NSString * const SpotzExtensionNotification;
extern NSString * const SPOTZ_EXTENSION_NOTIFICATION;
/**
 *  Notification when Spotz has been initialised. Error object, if any, is available in userInfo["error"].
 */
extern NSString * const SpotzInitNotification;
extern NSString * const SPOTZ_INIT_NOTIFICATION;
/**
 *  Notification when Spotz has completed notification.
 */
extern NSString * const SpotzSetupCompletedNotification;
extern NSString * const SPOTZ_SETUP_COMPLETED_NOTIFICATION;

/**
 *  Notification when Spotz reported an error. Error is available in userInfo["error"]
 */
extern NSString * const SpotzErrorNotification;
extern NSString * const SPOTZ_ERROR_NOTIFICATION;

/**
 *  Notification when monitored sites change occurs. An array of SpotzSiteDetails are available in userInfo["sites"].
 */
extern NSString * const SpotzClosestSitesUpdateNotification;
extern NSString * const SPOTZ_CLOSEST_SITES_UPDATE_NOTIFICATION;
/**
 *  Notification when bluetooth services changes status.
 *  The new status is available in userInfo["enabled"] with value 1 or 0
 */
extern NSString * const SpotzBluetoothServicesStateChangeNotification;
extern NSString * const SPOTZ_BLUETOOTH_SERVICES_STATE_CHANGE_NOTIFICATION;

/**
 *  Notification when network reachability services changes status.
 *  The new status is available in userInfo["enabled"] with value 1 or 0
 */
extern NSString * const SpotzNetworkReachabilityStateChangeNotification;
extern NSString * const SPOTZ_NETWORK_REACHABILITY_STATE_CHANGE_NOTIFICATION;

/**
 *  Notification when location services changes status.
 *  The new status is available in userInfo["enabled"] with value 1 or 0
 *  The location state is available in userInfo["state"] as NSNumber(SpotzLocationServicesState).
 */
extern NSString * const SpotzLocationServicesStateChangeNotification;
extern NSString * const SPOTZ_LOCATION_SERVICES_STATE_CHANGE_NOTIFICATION;

// Available Config Vars

// Static site limit - default 5
extern NSString * const CONFIG_STATIC_SITES_LIMIT;

// Enable static site monitoring -  default 0/'false'. Set  to  1 or  'true' to enable
extern NSString * const CONFIG_ENABLE_STATIC_SITES_MONITORING;

// Environment for the SDK to point to - default to production environment
extern NSString * const CONFIG_ENV;

// Enable background processing - default 1/true. Set to 0 or 'false' to disable
extern NSString * const CONFIG_ENABLE_BACKGROUND_PROCESSING;

// Enable debug logging - default to false
extern NSString * const CONFIG_ENABLE_DEBUG_LOG;

// Number of seconds before registering beacon as exit in foreground
extern NSString * const CONFIG_BEACON_EXIT_DELAY_IN_FOREGROUND;

// Number of seconds before registering beacon as exit in background
extern NSString * const CONFIG_BEACON_EXIT_DELAY_IN_BACKGROUND;

// Disable bluetooth manager
extern NSString * const CONFIG_ENABLE_IBEACON;

// Enable beacon ranging smoothing to detect closest beacon more accurately
extern NSString * const CONFIG_ENABLE_BEACON_RANGING_SMOOTHING;
