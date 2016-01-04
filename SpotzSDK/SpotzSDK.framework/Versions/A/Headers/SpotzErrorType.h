//
//  SpotzErrorTypes.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 8/08/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//

#ifndef SpotzErrorType_h
#define SpotzErrorType_h

typedef enum {
    EInvalidParameter  = 1, /* Invalid parameter */
    EInvalidResponseFromServer, /* Response received from server is invalid */
    EUnknownError, /* Unknown error */
    ENotFound, /* 404 error */
    ENotAuthorised, /* Not authorised error */
    EUserCancelled, /* User cancelled action */
    EFacebookError, /* Facebook related errors */
    EBeaconError, /* Beacon related errors */
    EBluetoothNotEnabled, /* Bluetooth not enabled */
    ELocationNotAuthorized, /* Location services not authorized */
    ELocationDenied, /* Location services denied */
    ELocationNotEnabled, /* Location services not authorized */
    ENoProjectsAvailable, /* No projects available */
    ENoSitesAvailable, /* No sites available */
    ENoConnection, /* No connection */
    ELocationFailed /* Failed obtaining location */
} SpotzErrorType;

#endif /* SpotzErrorTypes_h */