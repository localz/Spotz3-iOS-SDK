//
//  SpotzConstant.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 9/08/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef enum {
    SLNotDetermined = 0, // User has not authorized this application
    SLAuthorized = 1, // Authorization granted
    SLDenied = 2 // Authorization denied
} SpotzLocationServicesState;

@interface SpotzConstant : NSObject

/**
 *  Notification when spotz is found. Spotz object will be attached to note.object if exists
 */
extern NSString * const SpotzInsideNotification;

/**
 *  Notification when previously found spotz is no longer detected.
 */
extern NSString * const SpotzOutsideNotification;

/**
 *  Notification when ranging information available
 */
extern NSString * const SpotzRangingNotification;

extern NSString * const SpotzInitNotification;
extern NSString * const SpotzErrorNotification;
extern NSString * const SpotzSiteChangedNotification;

extern NSString * const SpotzBluetoothServicesStateChangeNotification;
extern NSString * const SpotzLocationServicesStateChangeNotification;

@end
