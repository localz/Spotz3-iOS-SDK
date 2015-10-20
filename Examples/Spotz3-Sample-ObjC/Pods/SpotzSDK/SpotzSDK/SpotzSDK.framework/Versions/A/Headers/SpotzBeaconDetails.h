//
//  SpotzBeaconData.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 3/06/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzBeaconDetails : NSObject<NSCoding,NSCopying>
@property (nonatomic,copy) NSString *spotId;
@property (nonatomic,copy) NSString *beaconId;
@property (nonatomic,copy) NSString *serial;
@property (nonatomic) int txPower;
@property (nonatomic,copy) NSUUID *uuid;
@property (nonatomic) int major;
@property (nonatomic) int minor;
@property (nonatomic) float rawRssi;
@property (nonatomic) float rawDistance;
@property (nonatomic) float distance;
@end