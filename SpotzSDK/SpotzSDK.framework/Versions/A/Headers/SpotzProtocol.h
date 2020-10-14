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
- (void) spotzInit:(NSError * _Nullable)error;

@optional
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
@end


#endif /* SpotzProtocol_h */
