//
//  LOLZConfiguration.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 28/04/2014.
//  Copyright (c) 2014 Spotz Pty Ltd. All rights reserved.
//
//#import "LZHPUser.h"

// Max threshold before beacon requires ranging (slower). Max is 20
#define SPOTZ_BEACONS_MAX_THRESHOLD 16

static NSString * const SPOTZ_SDK_VERSION = @"3.0.0";
static NSString * const SPOTZ_API_PROD_HOST = @"spotz-api.localz.io";
static NSString * const SPOTZ_API_DEV_HOST = @"spotz-dev.localz.io";
static NSString * const SPOTZ_API_PROD_URL = @"https://spotz-api.localz.io";
static NSString * const SPOTZ_API_DEV_URL = @"https://spotz-dev.localz.io";

static NSString * const SPOTZ_DB_FILENAME = @"spotz.dbcache";

static NSString * const SPOTZ_PROJECT_ID = @"__spz_project_id";
static NSString * const SPOTZ_PROJECT_KEY = @"__spz_project_key";
static NSString * const SPOTZ_DEVICE_ID = @"__spz_device_id";
static NSString * const SPOTZ_TYPES = @"__spz_types";

static NSString * const SPOTZ_ENV_ID = @"env";
static NSString * const SPOTZ_ENV_HOST = @"host";
static NSString * const SPOTZ_ENV_URL = @"gatewayURL";

//static NSString * const SpotzSDKPushId = @"__SpotzSDKPushId";
//static NSString * const SpotzSDKSessionId = @"__SpotzSDKSessionId";
//static NSString * const SpotzSDKIsAgent = @"__SpotzSDKIsAgent";
//static NSString * const SpotzSDKUser = @"__SpotzSDKUser";
//static NSString * const SpotzSDKCustomer = @"__SpotzSDKCustomer";
//static NSString * const SpotzSDKLocation = @"__SpotzSDKLocation";
//static NSString * const SpotzSDKLastLocation = @"__SpotzSDKLastLocation";
//static NSString * const SpotzSDKAreas = @"__SpotzSDKAreas";
//
//static NSString * const SpotzSDKDirectMonitorFlag = @"__SpotzSDKDirectMonitorFlag";
//
//static NSString * const SpotzConfigurationGatewayURL = @"gatewayURL";


/**
 *  Default settings
 */

//#define REFRESH_LOCATIONS_IN_DAY 1
//#define REFRESH_CATEGORIES_IN_DAY 1
//#define REFRESH_OFFERS_IN_SECONDS 5

extern NSString * const SPOTZ_PROJECT_ID;
extern NSString * const SPOTZ_PROJECT_KEY;
extern NSString * const SPOTZ_DEVICE_ID;
extern NSString * const SPOTZ_TYPES;
//
//extern NSString * const SpotzSDKSessionId;
//extern NSString * const SpotzSDKUser;
//extern NSString * const SpotzSDKLocation;
//extern NSString * const SpotzSDKLastLocation;
//extern NSString * const SpotzSDKAreas;

//extern NSString * const SpotzConfigurationGatewayURL;
extern NSString * const SPOTZ_ENV;

@interface SpotzConfiguration : NSObject

// True if SDK is running in dev mode
@property (nonatomic) BOOL isDevEnv;
@property (nonatomic) BOOL isDebug;
//@property (nonatomic) int totalCache;

/**
 *  Returns an instance of this class
 *
 *  @return instance of the class
 */
+ (SpotzConfiguration *) shared;

- (void) configureWithParams:(NSDictionary *)config;

/**
 *  Initialise shared instance for the given environment. If called after initial call, it will update values to the given environment.
 *
 * @param env Environment to use [Production,Development]
 */
- (void) configureForEnv:(NSString *)env;

/**
 *  Check if SDK is set correctly - i.e project Id and key are present and set
 */
- (BOOL) isSDKOk;

/**
 *  Returns the value stored in the configuration file based on SpotzEnvironments.plist
 *  If there is an override value for the key given, it will return the override value
 *  If the value exists for the target build, it will return the target build value
 *  Otherwise it will return the default value set. If not found it will return null
 *
 *  @param key the key name to retrieve
 *
 *  @return returns the value for the given key
 */
- (id) getValue:(NSString *)key;

/**
 *  Override value of the SDK config
 *
 *  @param key    the key name to override
 *  @param object the object to override with
 */
- (void) overrideKey:(NSString *)key withObject:(id)object;

/**
 *  Retrieve SDK Version
 *
 *  @return sdk version
 */
- (NSString *) sdkVersion;

/**
 *  Set application Id and client Key
 *
 *  @param projectId projectID
 *  @param projectKey projectKey
 */
- (void) setProjectId:(NSString *)pId projectKey:(NSString *)key;

/**
 *  Returns projectId
 */
- (NSString *) projectId;

/**
 *  Returns projectKey
 */
- (NSString *) projectKey;

/**
 *  Retrieve device ID from user defaults
 */
- (NSString *) deviceId;

/**
 *  Set Device ID
 *
 *  @param deviceId device ID
 */
- (void) setDeviceId:(NSString *)deviceId;

///**
// *  Retrieve push ID from user defaults
// */
//- (NSString *) pushId;
//
///**
// *  Set Push ID
// *
// *  @param pushId push ID
// */
//- (void) setPushId:(NSString *)pushId;
//
///**
// *  Retrieve session ID from user defaults
// */
//- (NSString *) sessionId;
//
///**
// *  Set Session ID
// *
// *  @param sessionId session ID
// */
//- (void) setSessionId:(NSString *)sessionId;
//
///**
// *  Removes SessionId
// */
//- (void) removeSessionId;

///**
// *  Returns user
// *
// *  @return LOLZUser object or nil if doesn't exist
// */
//- (LZHPUser *) user;
//
///**
// *  Set user object
// *
// *  @param user LOLZUser object to store
// */
//- (void) setUser:(LZHPUser *)user;

///**
// *  Returns profile photo's hash
// *
// *  @return NSString photo hash of nil if doesn't exist
// */
//- (NSString *) profilePhotoHash;
//
///**
// *  Set profile photo hash
// */
//- (void) setProfilePhotoHash:(NSString *)profilePhotoHash;

///**
// *  Returns location
// *
// *  @return LOLZSite object or nil if doesn't exist
// */
//- (LOLZLocation *) location;
//
///**
// *  Set location object
// *
// *  @param user LOLZSite object to store
// */
//- (void) setLocation:(LOLZLocation *)location;
//
///**
// *  Returns user's last location
// *
// *  @return CLLocation of user's last location
// */
//- (CLLocation *)lastLocation;
//
///**
// *  Set user's last location
// *
// *  @param location CLLocation of user's location
// */
//- (void) setLastLocation:(CLLocation *)location;

/**
 * Retrieve Host server
 *
 *  @return host server
 */
- (NSString *) host;

///**
// *  DB File Path
// *
// *  @return return file location of the DB
// */
//- (NSString *) dbFilePath;

/**
 *  Delete all Spotz config to factory setting (i.e. none set)
 */
- (void) reset;

- (BOOL) pLog;

- (void) setDebugMode:(BOOL)debug;
//
//- (void) setMaxCache:(int)totalCache;

@end
