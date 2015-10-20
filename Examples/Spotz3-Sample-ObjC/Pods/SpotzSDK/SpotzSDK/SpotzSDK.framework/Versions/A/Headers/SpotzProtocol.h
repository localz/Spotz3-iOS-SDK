//
//  SpotzProtocol.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 9/08/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//
#import "SpotzConstant.h"

#ifndef SpotzProtocol_h
#define SpotzProtocol_h

@protocol SpotzSDKDelegate <NSObject>

/**
 * Called when SDK has been initialised. Do not forget to call @link startSpotz @/link after this is called.
 * @param error error object if there were issues with the initialisation. Nil if successful.
 */
- (void) spotzInit:(NSError *)error;

/**
 *  This is called when site initialisation completed. If successful, all related Spots have been downloaded and registered.
 *  Error may occur if SDK was unable to locate closest site based on user's location, or network error.
 *  Subsequently you could present the user with a list of sites to choose from and call changeCurrentSite:completion: to register the site.
 *
 *  @param error Error object if site was not initialised successfully. Error is nil if successful.
 */
- (void) spotzSiteInit:(NSError *)error;

/**
 *  This is called when site has changed. Will not be called for the initial site setup. Listen in @link spotzSiteInitSuccessful @/link instead.
 *
 *  @param newSite The new site's details
 *  @param error   Contains the error object if failed, or nil if successful
 */
- (void) spotzSiteChangedToSite:(SpotzSiteDetails *)newSite error:(NSError *)error;

@optional

/**
 * Generic errors can be captured in here
 */
- (void) spotzFailedWithError:(NSError *)error;

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
@end


#endif /* SpotzProtocol_h */
