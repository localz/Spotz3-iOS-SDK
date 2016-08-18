//
//  SpotzData.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 4/05/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SpotzBeaconDetails.h"
#import "SpotzGeoDetails.h"

@interface SpotzData : NSObject<NSCoding>
@property (nonatomic,strong) NSString * _Nonnull name;
@property (nonatomic,strong) NSDictionary * _Nullable attributes;
@property (nonatomic,strong) NSString * _Nullable spotId;
@property (nonatomic,strong) NSString * _Nonnull siteId;
@property (nonatomic,strong) NSArray * _Nullable beacons;
@property (nonatomic,strong) SpotzGeoDetails * _Nullable geo;
@property (nonatomic) BOOL isRanging;

/**
 *  Approximate distance between beacon and the device. This should only be used as a reference
 *  as different source of beacon may transmit different signal strength.
 *  @return approximate distance in meters. Returns -1 if not found.
 */
- (float) distance;
- (NSDictionary * _Nonnull) metadata;
- (SpotzBeaconDetails * _Nullable) closestBeacon;
@end
