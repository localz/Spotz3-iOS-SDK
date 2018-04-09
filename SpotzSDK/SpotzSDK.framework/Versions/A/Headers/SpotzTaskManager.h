//
//  SpotzTaskManager.h
//  SpotzSDK
//
//  Created by Melvin Artemas on 15/08/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpotzTaskManager : NSObject
@property (nonatomic,strong) NSString *name;

- (instancetype) initWithName:(NSString *)taskName;

- (void) runIfInBackground;
- (BOOL) isRunning;

- (void) stopBackgroundTask;
@end
