//
//  SpotzProtocol.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 9/08/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//
#import "SpotzConstant.h"
#import "SpotzLocationData.h"

#ifndef SpotzProtocol_h
#define SpotzProtocol_h

@protocol SpotzSDKDelegate <NSObject>

/**
 * Called when SDK has been initialised. Do not forget to call @link startSpotz @/link after this is called.
 * @param error error object if there were issues with the initialisation. Nil if successful.
 */
- (void) spotzInit:(NSError * _Nullable)error;

/**
 *  This is called when site initialisation completed. If successful, all related Spots have been downloaded and registered.
 *  Error may occur if SDK was unable to locate closest site based on user's location, or network error.
 *  Subsequently you could present the user with a list of sites to choose from and call changeCurrentSite:completion: to register the site.
 *
 *  @param error Error object if site was not initialised successfully. Error is nil if successful.
 */
- (void) spotzSiteInit:(NSError * _Nullable)error;

@optional

/**
 *  This is called when site has changed. Will not be called for the initial site setup and when site is the same as the current site. Listen in @link spotzSiteInit@/link instead.
 *
 *  @param newSite The new site's details
 *  @param error   Contains the error object if failed, or nil if successful
 */
- (void) spotzSiteChangedToSite:(SpotzSiteDetails * _Nullable)newSite error:(NSError * _Nullable)error;

/**
 *  This is called when site has changed or when closest site was requested by the SDK. Will not be called for the initial site setup. Listen in @link spotzSiteInit@/link instead.
 *
 *  @param site The site's details
 *  @param existing True if the same site was previously detected
 *  @param error   Contains the error object if failed, or nil if successful
 */
- (void) spotzSiteChangedToSite:(SpotzSiteDetails * _Nullable)site existing:(BOOL)existing error:(NSError * _Nullable)error;

/**
 * Generic errors can be captured in here
 */
- (void) spotzFailedWithError:(NSError * _Nullable)error;

/**
 * This is called when spotz's app, beacons and geofence have been downloaded and services started. This may not indicate a successful registration however, e.g if location services is not available. Check spotzFailedWithError for any errors.
 */
- (void) spotzSetupCompleted;

/**
 * This is called when bluetooth state changes. Prompt user to enable bluetooth for beacon detection if necessary.
 */
- (void) spotzBluetoothStateDidChange:(BOOL)enabled;

/**
 * This is called when location services state changes. Prompt user to enable location services when necessary.
 * @param authorized SpotzLocationServicesState with the status detected
 * @param enabled is true if location services is enabled by user
 */
- (void) spotzLocationServicesStateDidChange:(SpotzLocationServicesState)authorized enabled:(BOOL)enabled;

/**
 * Real time location data will be posted here when enabled
 * @param location SpotzLocationData object with the current location data information
 */
- (void) spotzLatestLocationUpdate:(SpotzLocationData * _Nonnull)location;

#ifdef DEBUG
- (void) debugMessage:(NSString * _Nonnull)message;
#endif

@end


#endif /* SpotzProtocol_h */
