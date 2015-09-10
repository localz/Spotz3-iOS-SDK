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
#import "SpotzErrorType.h"
#import "SpotzSiteDetails.h"
#import "SpotzData.h"
#import "SpotzBeaconDetails.h"
#import "SpotzConstant.h"
#import "SpotzProtocol.h"

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
+ (SpotzSDK *) shared;

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
+ (void) initWithAppId:(NSString *)appId appKey:(NSString *)appKey delegate:(id)delegate config:(NSDictionary *)config;

/**
 *  Initialises location services and Spots. This must be run to register all Spots. We recommend this to be called at the point where you are ready to prompt user to enable location services (if not yet enabled previously). This will also download the closest site's data
 */
- (void) startSpotz;

/**
 *  Re-Initialises location services and Spots. This must be run to register all Spots. We recommend this to be called at the point where you are ready to prompt user to enable location services (if not yet enabled previously). This will also download the closest site's data
 */
- (void) restartSpotz;

#pragma mark - Spotz Management

/**
 *  Returns all spots retrieved based on the default/selected site.
 *  @return Retuns array of SpotzData at the current site. Returns nil if closest site is unknown or spots have not yet been retrieved
 */
- (NSArray *) spotsAtCurrentSite;

/**
 *  Returns the current registered site details
 *
 *  @return Returns the site details of the current site
 */
- (SpotzSiteDetails *) currentSite;

/**
 *  Retrieves all available sites
 *
 *  @return Returns an array of available SpotzSiteDetails
 */
- (NSArray *) availableSites;

/**
 *  Change current site to the given siteId. Upon successful update, it will monitor all Spots inside the site and retrigger the spotzSiteInitSuccessful delegate as well as spotzSiteChangedToSite:error: delegate
 *
 *  @param siteId     siteId to change to
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes one argument: The error object describing the error that occurred, or nil if no errors.
 */
- (void) changeCurrentSiteId:(NSString *)siteId completion:(void(^)(NSError *error))completion;

/**
 * Reset Spots detected. This will re-trigger all the notifications if the device is within a particular spot.
 */
- (void) resetSpots;

/**
 * Recheck status of registered Spots. This will re-trigger all notifications if the device is within a particular spot.
 */
- (void) recheckSpots;

/**
 * Clears all spots monitoring.
 */
- (void) clearSpotsMonitoring;

/**
 * Stop spotz service. Run startSpotz to restart the service.
 */
- (void) stopSpotz;

/**
 *  Returns the device ID assigned to this device
 *
 *  @return The Spotz's device ID assigned to this device
 */
- (NSString *)deviceId;

/**
 *  Records feedback ratings for the project/app. This is a simple rating recording function and takes in a numerical rating value which range is to be defined by the developer
 *
 *  @param rating     numerical rating value
 *  @param message    (optional) additional feedback message
 *  @param attributes (optional) additional information to be passed as part of the feedback, e.g. answers to a set of questionnaires
 *  @param module     (optional) the module name associated with this rating. e.g. Retail Module, Click&Collect, etc
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes two arguments: the error object describing the error that occurred or nil if no errors, and a feedbackId which is returned by Spotz Platform once feedback is successfully recorded.
 */
- (void) sendFeedbackWithRating:(int)rating message:(NSString *)message attributes:(NSArray *)attributes module:(NSString *)module completion:(void(^)(NSError *error,NSString *feedbackId))completion;

/**
 *  Associates the current device with a custom identity. Note that if the app is reinstalled, deviceId will need to be re-associated with the identity.
 *
 *  @param identityId identity to be assigned to this device e.g. customerId/token/email
 *  @param attributes additional information to be associated with this device. Useful when passing additional info to third party extensions.
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes one argument: the error object describing the error that occurred.
 */
- (void) identity:(NSString *)identityId completion:(void(^)(NSError *error))completion;

/**
 *  Removes identity that is mapped to this device
 *
 *  @param completion A block object to be executed when the task finishes successfully. This block has no return value and takes one argument: the error object describing the error that occurred.
 */
- (void) removeIdentityWithCompletion:(void(^)(NSError *error))completion;

/**
 *  Updates additional data for the given extension
 *  @param name Extension name in spotz console
 *  @param type Extension type in spotz console
 *  @param data Extension data (key/value) to be attached to this device
 */
- (void) updateExtension:(NSString *)name type:(NSString *)type data:(NSDictionary *)data;
@end
