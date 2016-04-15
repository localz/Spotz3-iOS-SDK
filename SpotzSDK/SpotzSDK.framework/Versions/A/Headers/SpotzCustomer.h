//
//  SpotzCustomer.h
//  SpotzSDK
//
//  Created by Paul Wong on 14/04/2016.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzCustomer : NSObject<NSCoding>
@property (nonatomic,strong) NSString *internalId;
@property (nonatomic,strong) NSString *customerId;

@property (nonatomic,strong) NSDictionary *attributes;

@end
