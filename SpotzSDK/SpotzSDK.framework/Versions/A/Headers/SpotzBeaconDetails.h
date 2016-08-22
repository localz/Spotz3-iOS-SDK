//
//  SpotzBeaconData.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 3/06/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzBeaconDetails : NSObject<NSCoding,NSCopying>
@property (nonatomic,copy) NSString * _Nonnull spotId;
@property (nonatomic,copy) NSString * _Nonnull beaconId;
@property (nonatomic,copy) NSString * _Nonnull serial;
@property (nonatomic) int txPower;
@property (nonatomic,copy) NSUUID * _Nonnull uuid;
@property (nonatomic) int major;
@property (nonatomic) int minor;
@property (nonatomic) float rawRssi;
@property (nonatomic) float rawDistance;
@property (nonatomic) float distance;
@end