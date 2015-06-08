//
//  SpotzData.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 4/05/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SpotzBeaconDetails.h"

@interface SpotzData : NSObject<NSCoding>
@property (nonatomic,strong) NSString *name;
@property (nonatomic,strong) NSDictionary *metadata;
@property (nonatomic,strong) NSString *spotId;
@property (nonatomic,strong) NSArray *beacons;
@end