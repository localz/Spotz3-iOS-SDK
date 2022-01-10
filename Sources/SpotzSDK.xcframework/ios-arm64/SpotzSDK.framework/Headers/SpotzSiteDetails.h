//
//  SpotzSiteDetails.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 21/05/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//
@import CoreLocation;
#import <Foundation/Foundation.h>

@interface SpotzSiteDetails : NSObject <NSCopying,NSSecureCoding>
@property (nonatomic,copy,readwrite) NSString * _Nonnull siteId;
@property (nonatomic,copy,readwrite) NSString * _Nonnull name;
@property (nonatomic,copy,readwrite) NSString * _Nullable address1;
@property (nonatomic,copy,readwrite) NSString * _Nullable address2;
@property (nonatomic,copy,readwrite) NSString * _Nullable tz;
@property (nonatomic,copy,readwrite) NSDictionary * _Nullable attributes;
@property (nonatomic,copy,readwrite) CLLocation * _Nullable location;

- (void) setAttributes:(NSDictionary * _Nonnull)attributes;
- (id _Nullable) attributeWithKey:(NSString * _Nonnull)key;
@end
