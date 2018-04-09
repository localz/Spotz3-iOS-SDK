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

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>
#import <CoreBluetooth/CoreBluetooth.h>

#import <Foundation/Foundation.h>
#import "SpotzErrorType.h"
#import "SpotzSiteDetails.h"
#import "SpotzData.h"
#import "SpotzBeaconDetails.h"
#import "SpotzGeoDetails.h"
#import "SpotzConstant.h"
#import "SpotzProtocol.h"
#import "SpotzCustomer.h"

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
+ (SpotzSDK * _Nonnull) shared;

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
+ (void) initWithAppId:(NSString * _Nonnull)appId appKey:(NSString * _Nonnull)appKey delegate:(id _Nullable)delegate config:(NSDictionary * _Nullable)config;

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

/**
 *  Returns all spots retrieved based on the default/selected site.
 *  @return Retuns array of SpotzData at the current site. Returns nil if closest site is unknown or spots have not yet been retrieved
 */
- (NSArray * _Nullable) spotsAtCurrentSite;

/**
 *  Returns the current registered site details
 *
 *  @return Returns the site details of the current site
 */
- (SpotzSiteDetails * _Nullable) currentSite;

/**
 *  Retrieves all available sites
 *
 *  @return Returns an array of available SpotzSiteDetails
 */
- (NSArray * _Nullable) availableSites;

/**
 *  Change current site to the given siteId. Upon successful update, it will monitor all Spots inside the site and retrigger the spotzSiteInitSuccessful delegate as well as spotzSiteChangedToSite:error: delegate
 *
 *  @param siteId     siteId to change to
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes one argument: The error object describing the error that occurred, or nil if no errors.
 */
- (void) changeCurrentSiteId:(NSString * _Nonnull)siteId completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Returns true if device is inside the spot
 * @param name Spot's name
 * @return true if inside, false if outside or not yet detected
 */
- (BOOL) isInsideSpotWithName:(NSString * _Nonnull)name;

/**
 * Returns true if device is inside the spot
 * @param spotId Spot's id
 * @return true if inside, false if outside or not yet detected
 */
- (BOOL) isInsideSpotWithId:(NSString * _Nonnull)spotId;

/**
 * Returns true if device is inside a spot with the given site ID
 * @param siteId Site ID
 * @return true if inside, false if outside or not yet detected
 */
- (BOOL) isInsideSpotAtSiteId:(NSString * _Nonnull)siteId;

/**
 * Returns list of SpotzData that are within proximity
 * @return list of SpotzData
 */
- (NSArray * _Nullable) insideSpots;

/**
 * Get current device's location.
 * @return current device's location. Nil if not available.
 */
- (CLLocation * _Nullable) currentLocation;

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
 * Starts spots monitoring. Call this method to startup Spots (geo/beacon) monitoring after stopMonitoring.
 */
- (void) startMonitoring;

/**
 * Stop spotz service. Run startSpotz to restart the service.
 */
- (void) stopSpotz;

/**
 *  Returns the device ID assigned to this device
 *
 *  @return The Spotz's device ID assigned to this device
 */
- (NSString * _Nullable) deviceId;

/**
 *  Records feedback ratings for the project/app. This is a simple rating recording function and takes in a numerical rating value which range is to be defined by the developer
 *
 *  @param rating     numerical rating value
 *  @param message    (optional) additional feedback message
 *  @param attributes (optional) additional information to be passed as part of the feedback, e.g. answers to a set of questionnaires
 *  @param module     (optional) the module name associated with this rating. e.g. Retail Module, Click&Collect, etc
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes two arguments: the error object describing the error that occurred or nil if no errors, and a feedbackId which is returned by Spotz Platform once feedback is successfully recorded.
 */
- (void) sendFeedbackWithRating:(int)rating message:(NSString * _Nullable)message attributes:(NSDictionary * _Nullable)attributes module:(NSString * _Nullable)module completion:(void(^ _Nullable)(NSError * _Nullable error, NSString * _Nullable feedbackId))completion;

/**
 *  Associates the current device with a custom identity. Note that if the app is reinstalled, deviceId will need to be re-associated with the identity.
 *
 *  @param identityId identity to be assigned to this device e.g. customerId/token/email
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes one argument: the error object describing the error that occurred.
 */
- (void) identity:(NSString * _Nonnull)identityId completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

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
- (void) updateExtension:(NSString * _Nonnull)name type:(NSString * _Nonnull)type data:(NSDictionary * _Nonnull)data;

/**
 * Checks status of location services
 * @return enable is true if service is on, false if not.
 */
- (BOOL) checkLocationServicesStatus:(void(^ _Nullable)(BOOL enable,CLAuthorizationStatus state))completion;

/**
 * Returns bluetooth state
 * @return enable is true if it is on, false if not.
 */
- (BOOL) checkBluetoothEnabled:(void(^ _Nullable)(BOOL enable,CBCentralManagerState state))completion;

/**
 * Prompt user to enable location. It will only prompts user when location status is not yet determined.
 */
- (void) requestLocationServicesPrompt;

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

/**
 * Enable background location update.
 * You will need to enable Capability->Background Mode->Location Updates to use this feature, and provide GPS warning when submitting to AppStore
 * Enabling this will also allow the app to detect geo-border crossing more accurately.
 *
 * WARNING: Please beware that when this is enabled, battery usage may be higher than normal.
 */
- (void) enableBackgroundLocation;

/**
 * Stops background location update.
 */
- (void) disableBackgroundLocation;

/**
 * Start background location tracking. SpotzSDK.enableBackgroundLocation must already be called.
 */
- (void) startBackgroundLocation;

/**
 * Starts background location however pauses location update when app is not in the foreground.
 */
- (void) startBackgroundLocationForegroundOnly;

/**
 * Call this method for a minimum background location call.
 */
- (void) pauseBackgroundLocation;

/**
 * Resumes backgroundLocation to normal resolution and frequency updates.
 */
- (void) resumeBackgroundLocation;

/**
 * Check if background location is on pause. Call resume to start normal background location update.
 * return true if paused, false if not.
 */
- (BOOL) isBackgroundLocationPaused;

/**
 * Stop background location tracking
 */
- (void) stopBackgroundLocation;

/**
 * Checks if background location is started
 */
- (BOOL) isBackgroundLocationStarted;

/**
 * Checks if background location is enabled
 */
- (BOOL) isBackgroundLocationEnabled;

/**
 * Returns true if background location is ready
 */
- (BOOL) isBackgroundLocationReady;

/**
 * If background location is enabled, you can adjust the minimum interval of how often location data is recorded, if changed.
 * @param interval in seconds. If 0 then recording is disabled. Defaults to 0 seconds.
 */
- (void) backgroundLocationRecordInterval:(int)interval;

#pragma mark - App hooks
- (void) appPerformFetchWithCompletionHandler:(void (^ _Nonnull)(UIBackgroundFetchResult))completionHandler;

#pragma mark - Customer
/**
 *  Returns the current logged in customer
 *
 *  @return Returns the details of the current logged in customer
 */
- (SpotzCustomer * _Nullable)currentCustomer;


- (void) registerCustomer:(NSString * _Nonnull)username password:(NSString * _Nonnull) password otherDetails:(NSDictionary * _Nullable) otherDetails completion:(void(^ _Nullable)(NSError * _Nullable error,SpotzCustomer * _Nullable customer))completion;

- (void) authenticateCustomer:(NSString * _Nonnull)username password:(NSString * _Nonnull)password completion:(void(^ _Nullable)(NSError * _Nullable error, SpotzCustomer * _Nullable customer))completion;

- (void) retrieveMyCustomerDetailsWithCompletion:(void(^ _Nullable)(NSError * _Nullable error, SpotzCustomer * _Nullable customer))completion;

- (void) logoutCustomer:(NSString * _Nonnull)customerId completion:(void(^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Registers custom userId to be used as the tracking identifier
 * UserId must be registered in Spotz
 */
- (void) registerCustomUserId:(NSString * _Nonnull)customUserId;

#pragma mark - Device Login

- (void) loginDeviceWithJWTToken:(NSString * _Nonnull)token;

- (void) logoutDevice;

#pragma mark - Real Time Tracking

/**
 * Track ETA based on trackId and location. Result will be returned completion callback of shape (error, data), where data should look like: {trackId, etaSeconds, etaMinutes, etaFrom, etaTo}
 * @param trackId to get ETA for
 * @param destLatLng coordinate array to track to @[lat,lng]
 */
- (void) getEtaTrackId:(NSString * _Nonnull)trackId destination:(NSArray * _Nonnull)destLatLng completion:(void(^ _Nullable)(NSError * _Nullable error,NSDictionary * _Nullable data))completion;

/**
 * Retrieves ETA based on track ID and the given location array of (lat,lng). Result will be returned completion callback of shape (error, data), where data should look like: {trackId, etaSeconds, etaMinutes, etaFrom, etaTo}
 * @param trackId to get ETA for
 * @param destLatLng coordinate array to track to @[lat,lng]
 * @param latlng coordinate array to track from @[lat,lng]
 */
- (void) getEtaTrackId:(NSString * _Nonnull)trackId destination:(NSArray * _Nonnull)destLatLng location:(NSArray * _Nonnull)latlng completion:(void(^_Nullable)(NSError * _Nullable error,NSDictionary * _Nullable data))completion;

#ifdef DEBUG
- (NSArray * _Nonnull)monitoredGeofences;
#endif

@end
