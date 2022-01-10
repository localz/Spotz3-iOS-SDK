/*
 * (C) 2015 Localz Pty Ltd
 *
 * [All rights reserved]. This product and related documentation are protected
 * by copyright restricting its use, copying, distribution, and decompilation.
 * No part of this product or related documentation may be reproduced in any
 * form by any means without prior written authorization of Localz.
 * Unless otherwise arranged, third parties may not
 * have access to this product or related documents.
 */

@import UIKit;
@import CoreLocation;
@import CoreBluetooth;

#import <Foundation/Foundation.h>
#import "SpotzErrorType.h"
#import "SpotzSiteDetails.h"
#import "SpotzData.h"
#import "SpotzBeaconDetails.h"
#import "SpotzGeoDetails.h"
#import "SpotzConstant.h"
#import "SpotzProtocol.h"
#import "SpotzCustomer.h"
#import "SpotzCommon.h"

@class SpotzSDK;

/**
 *  SpotzSDK is the main class that handles the integration between client and Localz's Spotz Platform
 */
@interface SpotzSDK : NSObject

/**
 *  Returns a singleton instance of Spotz
 *
 *  @return Returns a singleton instance of SpotzSDK
 */
+ (nonnull SpotzSDK *) shared;

/**
 *  Initialises the service and registers the device with the given API Key and client Key. Must be run to initialise SpotzSDK.
 *
 *  @param appId appId provided by Localz
 *  @param appKey appKey provided by Localz
 *  @param delegate the delegate class that adopts SpotzSDKDelegate protocol
 *  @param config options for additional setup
 *
 *  @warning You will need to call @link startSpotz @/link in order to start monitoring for Spots. The startSpotz should be run inside or after spotzInitSuccessful delegate is called.
 */
+ (void) initWithAppId:(nonnull NSString *)appId appKey:(nonnull NSString *)appKey delegate:(nullable id)delegate config:(nullable NSDictionary *)config;

/**
 *  Initialises location services and Spots. This must be run to register all Spots. We recommend this to be called at the point where you are ready to prompt user to enable location services (if not yet enabled previously). This will also download the closest site's data
 */
- (void) startSpotz;

/**
 *  Re-Initialises location services and Spots. This must be run to register all Spots. We recommend this to be called at the point where you are ready to prompt user to enable location services (if not yet enabled previously). This will also download the closest site's data
 */
- (void) restartSpotz;

/**
 *  Returns Spotz started status.
 *  @return true if spotz is started, false if not.
 */
- (BOOL) isSpotzStarted;

#pragma mark - Spotz Management

///**
// *  Returns all spots retrieved based on the default/selected site.
// *  @return Retuns array of SpotzData at the current site. Returns nil if closest site is unknown or spots have not yet been retrieved
// */
//- (nullable NSArray *) spotsAtCurrentSite;

/**
 * Returns the closest sites
 * @return Returns the site details of the closest sites
 */
- (nullable NSArray<SpotzSiteDetails *>*) closestSites;

/**
 * Returns last checked user location
 */
- (nullable CLLocation *) lastUserLocation;

#ifdef DEBUG
/**
 * Returns the closest registered site regions. This may be more than one regions.
 * @return Returns the closest registered sites
 */
- (nullable NSArray *) monitoredSiteRegions;

/**
 * Returns the currently registered spots regions
 * @return Returns CLRegion of the registered geo spotzs
 */
- (nullable NSArray *) monitoredSpotGeoRegions;

/**
 * Returns the currently registered beacons
 * @return Returns array of monitored Beacon Identifiers
 */
- (nullable NSArray *) monitoredBeaconIdentifiers;
#endif

/**
 *  Retrieves all available sites
 *
 *  @return Returns an array of available SpotzSiteDetails
 */
- (nullable NSArray *) availableSites;

/**
 * Returns true if device is inside the spot
 * @param name Spot's name
 * @return true if inside, false if outside or not yet detected
 */
- (BOOL) isInsideSpotWithName:(nonnull NSString *)name;

/**
 * Returns true if device is inside the spot
 * @param spotId Spot's id
 * @return true if inside, false if outside or not yet detected
 */
- (BOOL) isInsideSpotWithId:(nonnull NSString *)spotId;

/**
 * Returns true if device is inside a spot with the given site ID
 * @param siteId Site ID
 * @return true if inside, false if outside or not yet detected
 */
- (BOOL) isInsideSpotAtSiteId:(nonnull NSString *)siteId;

/**
 * Returns list of SpotzData that are within proximity
 * @return list of SpotzData
 */
- (NSArray * _Nullable)insideSpots;

/**
 * Reset Spots detected. This will re-trigger all the notifications if the device is within a particular spot. Ensure this is not called inside SpotzInsideNotification notification.
 * This method and recheckSpot can only be called once every 2 seconds. If less then 2 seconds will abort.
 */
- (void) resetSpots;

/**
 * Recheck status of registered Spots. This will re-trigger all notifications if the device is within a particular spot. 
 * Ensure this is not called inside SpotzInsideNotification notification.
 *
 * Please note: This will also reset and call any spots state, thus you may get multiple entry events without any exists, 
 * and potentially call the server extensions if they are set.
 *
 * To check if you are inside a spot, please call retriggerInsideSpots instead or check the spots in the insideSpots array.
 * This method and recheckSpot can only be called once every 2 seconds. If less then 2 seconds will abort.
 */
- (void) recheckSpots;

/**
 * Retrigger SpotzInsideNotification notifications based on spots that are inside. This is a passive
 * trigger and will only trigger spots that are currently in proximity of the device.
 */
- (void) retriggerInsideSpots;

/**
 * Stops all spots monitoring. This will stop Spots (geo/beacon) monitoring only.
 */
- (void) stopMonitoring;

/**
 * Stop spotz service. Run startSpotz to restart the service.
 * Please note - this will stop and clear everything from the cache. If static monitoring was defined, you will need to set them again via registerSitesForMonitoringWithSiteIds prior to starting Spotz
 */
- (void) stopSpotz;

/**
 * Monitor a whitelist of site IDs. This will replace any existing site IDs being monitored.
 * This is only available when the SDK is started in static monitoring mode.
 * To start the SDK in static monitoring mode use the initalisation config `@{ @"staticMonitoring":true }`
 *
 * @param siteIds   An array of all siteIds to be monitored.
 * @param completion returns error if there are issues with registering the site.
 */
- (void) registerSitesForMonitoringWithSiteIds:(nonnull NSArray<NSString *>*)siteIds completion:(void(^_Nullable)(NSError * _Nullable error))completion;

/**
 *  Returns the device ID assigned to this device
 *
 *  @return The Spotz's device ID assigned to this device
 */
- (nullable NSString *)deviceId;

/**
 *  Records feedback ratings for the project/app. This is a simple rating recording function and takes in a numerical rating value which range is to be defined by the developer
 *
 *  @param rating     numerical rating value
 *  @param message    (optional) additional feedback message
 *  @param attributes (optional) additional information to be passed as part of the feedback, e.g. answers to a set of questionnaires
 *  @param module     (optional) the module name associated with this rating. e.g. Retail Module, Click&Collect, etc
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes two arguments: the error object describing the error that occurred or nil if no errors, and a feedbackId which is returned by Spotz Platform once feedback is successfully recorded.
 */
- (void) sendFeedbackWithRating:(int)rating message:(nullable NSString *)message attributes:(nullable NSDictionary *)attributes module:(nullable NSString *)module completion:(void(^ _Nullable)(NSError * _Nullable error, NSString * _Nullable feedbackId))completion;

/**
 *  Associates the current device with a custom identity. Note that if the app is reinstalled, deviceId will need to be re-associated with the identity.
 *
 *  @param identityId identity to be assigned to this device e.g. customerId/token/email
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes one argument: the error object describing the error that occurred.
 */
- (void) identity:(nonnull NSString *)identityId completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 *  Removes identity that is mapped to this device
 *
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes one argument: the error object describing the error that occurred.
 */
- (void) removeIdentityWithCompletion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 *  Updates additional data for the given extension
 *  @param name Extension name in spotz console
 *  @param type Extension type in spotz console
 *  @param data Extension data (key/value) to be attached to this device
 */
- (void) updateExtension:(nonnull NSString *)name type:(NSString * _Nonnull)type data:(NSDictionary * _Nonnull)data;

/**
 * Checks status of location services
 * @return enable is true if service is on, false if not.
 */
- (BOOL) checkLocationServicesStatus:(void(^ _Nullable)(BOOL enable,CLAuthorizationStatus state))completion;

/**
 * Returns bluetooth state
 * @return enable is true if it is on, false if not.
 */
- (BOOL) checkBluetoothEnabled:(void(^ _Nullable)(BOOL enable,CBManagerState state))completion;

/**
 * Prompt user to enable location. It will only prompts user when location status is not yet determined.
 */
- (void) requestLocationServicesPrompt;

/**
* Prompt user to enable bluetooth. It will only prompts user when the bluetooth status is not yet determined.
*/
- (void) requestBluetoothServicesPrompt;

/*!
 * Request precise location with a purpose key. This is a wrapper to apple's requestTemporaryFullAccuracyAuth with additional checks to handle iOS backward compatibility. Please ensure purpose keys are set in the app prior to using this method.
 * @param purposeKey The purposeKey set in your info plist - see https://developer.apple.com/documentation/corelocation/cllocationmanager/3600217-requesttemporaryfullaccuracyauth for more information
 * @param completion The completion block to call with error if any. Will return error = nil if iOS < 14
 * @return true if already enabled or is iOS < 14, false if request is needed
 */
- (BOOL) requestPreciseLocationWitPurposeKey:(NSString * _Nonnull)purposeKey completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/*!
 * Check if precise location is enabled. Will always return true for < iOS14
 */
- (BOOL) isPreciseLocationEnabled;

/**
 * Set this to false to stop SDK from sending Spotz events. This should be enabled if you have a third party integration.
 * Default is true
 * @param enable set to true to enable the events, false to disable it
 */
- (void) enableSpotzEvents:(BOOL)enable;

/**
 * Returns the spotz events enabled flag
 * @return true if enabled, false if not
 */
- (BOOL) isSpotzEventsEnabled;

/**
 * Check and download updates if available
 */
- (void) checkAndUpdateSpotz;

#pragma mark - Manage location monitoring

/**
 * When static monitoring is enabled, the dynamic sites detection using user's location is disabled automatically.
 * There are limit to the number of static monitored sites and this can be adjusted via the SDK init CONFIG_STATIC_SITES_LIMIT parameter. By default it is set to 10 total sites.
 * @param enable Set to true to enable, false to disable static monitoring. if disabled, it will fall back to using user's location to find the closest sites.
 */
- (void) enableStaticMonitoring:(BOOL)enable;

/**
 * Returns static monitoring settings
 * @returns true if enabled, false if not
 */
- (BOOL) isStaticMonitoringEnabled;

#pragma mark - App hooks
- (void)appPerformFetchWithCompletionHandler:(void (^ _Nonnull)(UIBackgroundFetchResult))completionHandler;

#pragma mark - Customer
/**
 *  Returns the current logged in customer
 *
 *  @return Returns the details of the current logged in customer
 */
- (nullable SpotzCustomer *) currentCustomer;


- (void) registerCustomer:(NSString * _Nonnull) username password:(NSString * _Nonnull) password otherDetails:(NSDictionary * _Nullable) otherDetails completion:(void(^ _Nullable)(NSError * _Nullable error, SpotzCustomer * _Nullable customer))completion;

- (void) authenticateCustomer:(NSString * _Nonnull) username password:(NSString * _Nonnull) password completion:(void(^ _Nullable)(NSError * _Nullable error, SpotzCustomer * _Nullable customer))completion;

- (void) retrieveMyCustomerDetailsWithCompletion:(void(^ _Nullable)(NSError * _Nullable error, SpotzCustomer * _Nullable customer))completion;

- (void) logoutCustomer:(NSString * _Nonnull) customerId completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

@end
