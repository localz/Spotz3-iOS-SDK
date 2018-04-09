//
//  SpotzGeoDetails.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 5/08/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

@interface SpotzGeoDetails : NSObject<NSCopying,NSCoding>
@property (nonatomic,copy,readwrite) NSString * _Nonnull spotId;
@property (nonatomic,copy,readwrite) NSString * _Nonnull siteId;
@property (nonatomic,copy,readwrite) NSString * _Nonnull geofenceId;
@property (nonatomic,copy,readwrite) NSString * _Nonnull name;
@property (nonatomic,readwrite) float latitude;
@property (nonatomic,readwrite) float longitude;
@property (nonatomic,readwrite) float radius;

- (CLLocationCoordinate2D)coordinate;
- (CLLocation * _Nullable) location;
@end
