//
//  SpotzData.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 4/05/2015.
//  Copyright (c) 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzData : NSObject
@property (nonatomic,strong) NSString *name;
@property (nonatomic,strong) NSDictionary *metadata;
@property (nonatomic,strong) NSString *spotId;
@property (nonatomic) float rawRSSI;
@property (nonatomic) float rawDistance;
@property (nonatomic) float distance;
@end
