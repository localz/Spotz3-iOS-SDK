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
#import "SpotzConfiguration.h"

@protocol SpotzSDKDelegate <NSObject>
@optional
- (void) spotzInitSuccessfull;
- (void) spotzInitFailed:(NSError *)error;
- (void) spotzLocationServicesNotAuthorizedError;
- (void) spotzLocationServicesNotEnabledError;
//- (void) spotzPushNotificationRegistrationSuccess;
//- (void) spotzPushNotificationRegistrationFailed:(NSError *)error;
@end

@interface SpotzSDK : NSObject

@property (nonatomic,assign) id<SpotzSDKDelegate> delegate;

/**
 * Returns the singleton instance of SpotzPush
 */
+ (SpotzSDK *) shared;

/**
 *  Initialise service and register device with the given API Key and client Key. Must be run to initialise SpotzSDK.
 *
 *  @param appId appId provided by Localz
 *  @param appKey appKey provided by Localz
 *  @param options options for advance settings/debugging
 */
+ (void) initWithProjectId:(NSString *)projectId projectKey:(NSString *)projectKey config:(NSDictionary *)config;

/**
 *  Enables location services. If user has not yet enabled location services, this will prompt the permission dialog.
 *  This is required to be called prior to detecting user's location via geolocation or iBeacon.
 */
- (void) locationServicesEnabled:(BOOL)enable;

#pragma mark - Utility Helpers

+ (BOOL) isBackgroundRefreshEnabled;

@end
