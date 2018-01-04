//
//  SpotzMacros.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 16/11/16.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//
#import "SpotzConfiguration.h"

#ifndef SpotzMacros_h
#define SpotzMacros_h


#ifdef DEBUG
#define PLog(fmt, ...) { if([[SpotzConfiguration shared] pLog]) NSLog((@"PDEBUG: %s [Line %d] %@"), __PRETTY_FUNCTION__, __LINE__, [NSString stringWithFormat:(fmt), ##__VA_ARGS__]); }
#else
#define PLog(...)
#endif

#define SLog(fmt, ...) { if([SpotzConfiguration shared].isDebug || [[SpotzConfiguration shared] pLog]) NSLog((@"%s [Line %d] %@"), __PRETTY_FUNCTION__, __LINE__, [NSString stringWithFormat:(fmt), ##__VA_ARGS__]); }

// This will output without showing date and time as shown by MLog
#define MLog(format, ...) { printf("%s\n", [[NSString stringWithFormat:format, ##__VA_ARGS__] UTF8String]); }

#define DEFINE_SHARED_INSTANCE_USING_BLOCK(block) \
static dispatch_once_t pred = 0; \
__strong static id _sharedObject = nil; \
dispatch_once(&pred, ^{ \
_sharedObject = block(); \
}); \
return _sharedObject;

#endif /* SpotzMacros_h */
