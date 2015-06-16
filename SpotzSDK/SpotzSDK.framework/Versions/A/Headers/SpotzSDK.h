//
//  SpotzSDK.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 17/04/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//
@import UIKit;
@import CoreLocation;
@import CoreBluetooth;

#import <Foundation/Foundation.h>
#import "SpotzSiteDetails.h"
#import "SpotzData.h"

/**
 *  Notification when client is within the geofenced area of a site. Only when geofence is specified
 */
extern NSString * const SpotzEnterSiteProximityNotification;

/**
 *  Notification when client is outside the geofenced area of a site. Only when geofence is specified
 */
extern NSString * const SpotzExitSiteProximityNotification;

/**
 *  Notification when client is within inside the current site's beacon.
 */
extern NSString * const SpotzEnterSiteNotification;

/**
 *  Notification when client is within outside the current site's beacon.
 */
extern NSString * const SpotzExitSiteNotification;

/**
 *  Notification when spotz is found. Spotz object will be attached to note.object if exists
 */
extern NSString * const SpotzInsideNotification;

/**
 *  Notification when previously found spotz is no longer detected.
 */
extern NSString * const SpotzOutsideNotification;

/**
 *  Notification when ranging information available
 */
extern NSString * const SpotzRangingNotification;

@class SpotzSDK;
@protocol SpotzSDKDelegate <NSObject>

- (void) spotzInitSuccessful;
- (void) spotzSiteInitSuccessful;
- (void) spotzSiteInitFailed:(NSError *)error;
@optional
- (void) spotzInitFailed:(NSError *)error;
- (void) spotzFailedWithError:(NSError *)error;
- (void) spotzLocationServicesNotAuthorizedError;
- (void) spotzLocationServicesNotEnabledError;
@end

@interface SpotzSDK : NSObject

@property (nonatomic,assign) id<SpotzSDKDelegate> delegate;

/**
 * Returns a singleton instance of SpotzPush
 */
+ (SpotzSDK *) shared;

/**
 *  Initialise service and register device with the given API Key and client Key. Must be run to initialise SpotzSDK.
 *
 *  @param appId appId provided by Localz
 *  @param appKey appKey provided by Localz
 *  @param options options for advance settings/debugging
 */
+ (void) initWithAppId:(NSString *)appId appKey:(NSString *)appKey delegate:(id)delegate config:(NSDictionary *)config;

/**
 *  Initialise location services and spots. This should be run at the point where user is to be prompted to enable location services
 *  This will also download the closest site's data
 */
- (void) startSpotz;

///**
// *  Stop spotz from notifying the app of any Spotz's beacons/geolocation events
// */
//- (void) pauseSpotz;

#pragma mark - Spotz Management

/**
 * Returns all spots retrieved based on the default/selected site. Returns nil if closest site is not known or
 * spots have not yet been retrieved
 */
- (NSArray *) spotsAtCurrentSite;

/**
 * Returns the current closest site detected
 */
- (SpotzSiteDetails *) currentSite;

/**
 *  Manually download spots registered at a particular site
 */
- (void) retrieveSpotsAtSite:(NSString *)siteId completion:(void(^)(NSError *error,NSArray *spots))completion;

/**
 * Reset spots detected. This will re-trigger all the notifications if the device is within a particular spot.
 */
- (void) resetSpots;

/**
 * Stop spots from all monitoring
 */
- (void) stopSpotz;

/**
 * Unique device ID assigned to this device
 */
- (NSString *)deviceId;

#pragma mark - Utility Helpers

+ (BOOL) isBackgroundRefreshEnabled;

@end
