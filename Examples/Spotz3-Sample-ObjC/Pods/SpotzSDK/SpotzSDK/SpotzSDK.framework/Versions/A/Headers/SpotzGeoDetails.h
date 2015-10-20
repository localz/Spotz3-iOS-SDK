//
//  SpotzGeoDetails.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 5/08/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//

@import CoreLocation;
#import <Foundation/Foundation.h>

@interface SpotzGeoDetails : NSObject<NSCopying,NSCoding>
@property (nonatomic,copy,readwrite) NSString *spotId;
@property (nonatomic,copy,readwrite) NSString *siteId;
@property (nonatomic,copy,readwrite) NSString *geofenceId;
@property (nonatomic,copy,readwrite) NSString *name;
@property (nonatomic,readwrite) float latitude;
@property (nonatomic,readwrite) float longitude;
@property (nonatomic,readwrite) float radius;

- (CLLocationCoordinate2D)coordinate;
- (CLLocation *) location;
@end
