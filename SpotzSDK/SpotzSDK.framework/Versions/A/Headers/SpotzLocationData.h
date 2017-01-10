//
//  SpotzLocationData.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 26/10/16.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

@import CoreLocation;
#import <Foundation/Foundation.h>

@interface SpotzLocationData : NSObject
@property (nonatomic,strong) CLLocation *location;
@property (nonatomic,strong) NSDate *updateDate;
- (instancetype) initWithLocation:(CLLocation *)location date:(NSDate *)date;
@end
