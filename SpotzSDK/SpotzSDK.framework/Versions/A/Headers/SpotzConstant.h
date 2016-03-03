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

@interface SpotzConstant : NSObject

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
 *  Notification when site geofence is enabled, and enter event is detected. SpotzSiteDetails object is available in userInfo["data"].
 */
extern NSString * const SpotzInsideSiteGeoNotification;

/**
 *  Notification when site geofence is enabled, and exit event is detected. SpotzSiteDetails object is available in userInfo["data"].
 */
extern NSString * const SpotzOutsideSiteGeoNotification;

/**
 *  Notification when a returned data exists during enter/exit Spot events. 
 *  When available and enabled, the response from the extension call is available in userInfo["response"].
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

@end
