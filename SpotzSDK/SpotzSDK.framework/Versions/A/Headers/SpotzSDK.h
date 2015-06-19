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
#import "SpotzBeaconDetails.h"

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

/**
 * Successfully initialised the SDK
 */
- (void) spotzInitSuccessful;
/**
 * Site initialisation was successful. All related spots have been downloaded and registered.
 */
- (void) spotzSiteInitSuccessful;
/**
 * Site initialisation failed. Check that location servies is authorised and enabled. 
 * You could present user with list of sites to choose from and call changeCurrentSite:completion: to register the site and its spots.
 */
- (void) spotzSiteInitFailed:(NSError *)error;
@optional
/**
 * Spotz initialisation failed
 */
- (void) spotzInitFailed:(NSError *)error;
/**
 * Generic errors can be captured in here
 */
- (void) spotzFailedWithError:(NSError *)error;
/**
 * Location services is not authorised. Prompt user to re-enable location and call startSpotz to retry
 */
- (void) spotzLocationServicesNotAuthorizedError;
/*
 * Location services is not enabled. Prompt user to re-enable location and call startSpotz to retry
 */
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

#pragma mark - Spotz Management

/**
 * Returns all spots retrieved based on the default/selected site. Returns nil if closest site is not known or
 * spots have not yet been retrieved
 */
- (NSArray *) spotsAtCurrentSite;

/**
 * Returns the current registered site
 */
- (SpotzSiteDetails *) currentSite;

/**
 * Returns all available sites
 */
- (NSArray *) availableSites;

/**
 *  Set current site to the given site and monitor all trigger points inside the site.
 */
- (void) changeCurrentSite:(NSString *)siteId completion:(void(^)(NSError *error))completion;

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
