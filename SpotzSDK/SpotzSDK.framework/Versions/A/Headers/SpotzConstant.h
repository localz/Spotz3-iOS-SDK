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

/**
 *  Notification when previously found spotz is no longer detected. SpotzData object of the triggered Spot is available in userInfo["data"].
 */
extern NSString * const SpotzOutsideNotification;

/**
 *  Notification when ranging information available. SpotzData object of the triggered Spot is available in userInfo["data"].
 */
extern NSString * const SpotzRangingNotification;

/**
 *  Notification when ranging information available. This works on top of data collected from SpotzRangingNotification data.
 */
extern NSString * const SpotzClosestBeaconNotification;

/**
 *  Notification when site geofence is enabled, and enter event is detected. SpotzSiteDetails object is available in userInfo["data"].
 */
extern NSString * const SpotzInsideSiteGeoNotification;

/**
 *  Notification when site geofence is enabled, and exit event is detected. SpotzSiteDetails object is available in userInfo["data"].
 */
extern NSString * const SpotzOutsideSiteGeoNotification;

/**
 *  Notification when real time init is successfully and first location has been transmitted
 */
extern NSString * const SpotzRTInitSuccessNotification;

/**
 *  Notification when realtime spotz is found.
 */
extern NSString * const SpotzRTInsideNotification;

/**
 *  Notification when realtime spotz is no longer detected.
 */
extern NSString * const SpotzRTOutsideNotification;

/**
 *  Notification when realtime spotz remains found after a certain x period.
 */
extern NSString * const SpotzRTDwellNotification;

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

/**
 *  Notification when Spotz has been initialised. Error object, if any, is available in userInfo["error"].
 */
extern NSString * const SpotzInitNotification;

/**
 *  Notification when Spotz has completed notification.
 */
extern NSString * const SpotzSetupCompletedNotification;

/**
 *  Notification when Spotz Site initialisation has been completed.
 */
extern NSString * const SpotzSiteInitNotification;

/**
 *  Notification when Spotz reported an error. Error is available in userInfo["error"]
 */
extern NSString * const SpotzErrorNotification;

/**
 *  Notification when Site change occurs. If successful, the new site's SpotzSiteDetails object is available in userInfo["site"].
 *  Error object, if any, is available in the userInfo["error"].
 */
extern NSString * const SpotzSiteChangedNotification;

/**
 *  Notification when bluetooth services changes status.
 *  The new status is available in userInfo["enabled"] with value 1 or 0
 */
extern NSString * const SpotzBluetoothServicesStateChangeNotification;

/**
 *  Notification when network reachability services changes status.
 *  The new status is available in userInfo["enabled"] with value 1 or 0
 */
extern NSString * const SpotzNetworkReachabilityStateChangeNotification;

/**
 *  Notification when location services changes status.
 *  The new status is available in userInfo["enabled"] with value 1 or 0
 *  The location state is available in userInfo["state"] as NSNumber(SpotzLocationServicesState).
 */
extern NSString * const SpotzLocationServicesStateChangeNotification;

/**
 *  Notification of background location connection state
 *  The new status is available in userInfo["state"]
 */
extern NSString * const SpotzBGLocationConnectionStateChangeNotification;
