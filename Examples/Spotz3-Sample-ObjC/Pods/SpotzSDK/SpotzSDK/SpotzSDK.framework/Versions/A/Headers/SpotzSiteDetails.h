//
//  SpotzSiteDetails.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 21/05/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//
@import CoreLocation;
#import <Foundation/Foundation.h>

@interface SpotzSiteDetails : NSObject<NSCopying,NSCoding>
@property (nonatomic,copy,readwrite) NSString *siteId;
@property (nonatomic,copy,readwrite) NSString *name;
@property (nonatomic,copy,readwrite) NSString *address1;
@property (nonatomic,copy,readwrite) NSString *address2;
@property (nonatomic,copy,readwrite) NSString *tz;
@property (nonatomic,copy,readwrite) NSArray *attributes;
@property (nonatomic,copy,readwrite) CLLocation *location;

- (void) setAttributes:(NSArray *)attributes;
- (NSDictionary *) attributesDict;
- (id) attributeWithKey:(NSString *)key;
@end
