Spotz SDK 3.1.5 REALTIME SDK
============================

## Adding the Spotz SDK framework to your project

Just add the following line to your Podfile:
```
...
source 'https://github.com/localz/Spotz-iOS-Specs.git'
source 'https://github.com/CocoaPods/Specs.git'
...
pod 'SpotzRTSDK'
```

How to use the SDK
==================

**1. Set authorization message**

For iOS 8 or later, please add the following key to Info.plist with a message that will be presented to the user when they first start the app.
```
NSLocationAlwaysUsageDescription
```

For location update while app is the background only, in Xcode you will need to enable `Background Modes` and `Location updates`. You will also need to enter the necessary reason for requiring background location update in the app description, when submitting to the AppStore.

**2. Initialize the Spotz SDK**

Import the SpotzSDK header into the AppDelegate, then in the didFinishLaunchingWithOptions method add the following:

Swift
```
SpotzSDK.initWithAppId("<Enter your app ID here>", appKey: "<Enter your client key here>", delegate: self, config:nil)
SpotzSDK.shared().enableBackgroundLocation();
SpotzSDK.shared().backgroundLocationRecordInterval(10);
```

Objective-C
```
[SpotzSDK initWithAppId:@"<Enter your app ID here>" appKey:@"<Enter your client key here>" delegate:self config:nil];
[[SpotzSDK shared] enableBackgroundLocation];
[[SpotzSDK shared] backgroundLocationRecordInterval:10];
```

When initialization is successful, it will call the spotzInit delegate method. See below for details.

**3. Start services**

Swift
```
func spotzInit(error: NSError?)
{
    if let error = error
    {
        NSLog("Error initializing spot \(error)")
    }
    else
    {
        SpotzSDK.shared().startBackgroundLocation()
    }
}

```

Objective-C
```
- (void)spotzInit:(NSError *)error
{
    if(!error)
    {
        [[SpotzSDK shared] startBackgroundLocation];
    }
    else
    {
        NSLog(@"Error initializing spot %@",error);
    }
}
```

You can place this listener where it makes sense

**4. Listen for notifications**

Swift
```
// Spotz entry notification
NSNotificationCenter.defaultCenter().addObserverForName(SpotzRTInsideNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in

    if let data = note.userInfo,
        let spot = data["data"] as? SpotzData
    {
        // Take out the Spotz data print what we have
        print("Inside a predefined geofence")

        if let attributes = spot.attributes
        {
            // List the attributes for this spot
            print("Spot attributes:")
            for (key,value) in attributes
            {
                print("\t\(key) : \(value)");
            }
        }

        // Do something great with this Spot
    }
}

// Spotz dwell notification
NSNotificationCenter.defaultCenter().addObserverForName(SpotzRTDwellNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in

    if let data = note.userInfo,
        let spot = data["data"] as? SpotzData
    {
        // Take out the Spotz data print what we have
        print("Inside a predefined geofence after X period!")

        if let attributes = spot.attributes
        {
            // List the attributes for this spot
            print("Spot attributes:")
            for (key,value) in attributes
            {
                print("\t\(key) : \(value)");
            }
        }

        // Do something great with this Spot
    }
}

// Spotz exit notification
NSNotificationCenter.defaultCenter().addObserverForName(SpotzRTOutsideNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in

    if let data = note.userInfo,
        let spot = data["data"] as? SpotzData
    {
        // Take out the Spotz data print what we have
        print("Outside a predefined geofence!")

        if let attributes = spot.attributes
        {
            // List the attributes for this spot
            print("Spot attributes:")
            for (key,value) in attributes
            {
                print("\t\(key) : \(value)");
            }
        }

        // Do something great with this Spot
    }
}
```

Objective-C
```
// Spotz entry notification
[[NSNotificationCenter defaultCenter] addObserverForName:SpotzRTInsideNotification object:nil queue:nil usingBlock:^(NSNotification *note)
{
    if (note.userInfo)
    {
        // Take out the Spotz data print what we have
        NSDictionary *data = note.userInfo;
        SpotzData *spot = data[@"data"];
        NSLog(@"Inside a predefined geofence!");

        if (spot.attributes)
        {
            // List the attributes for this spot
            NSLog(@"Spot attributes:");
            for (NSString *key in spot.attributes.allKeys)
            {
                NSLog(@"\t%@ : %@", key, spot.attributes[key]);
            }
        }

        // Do something great with this Spot
    }
}];

// Spotz dwell notification
[[NSNotificationCenter defaultCenter] addObserverForName:SpotzRTDwellNotification object:nil queue:nil usingBlock:^(NSNotification *note)
{
    if (note.userInfo)
    {
        // Take out the Spotz data print what we have
        NSDictionary *data = note.userInfo;
        SpotzData *spot = data[@"data"];
        NSLog(@"Inside a predefined geofence after X period");

        if (spot.attributes)
        {
            // List the attributes for this spot
            NSLog(@"Spot attributes:");
            for (NSString *key in spot.attributes.allKeys)
            {
                NSLog(@"\t%@ : %@", key, spot.attributes[key]);
            }
        }

        // Do something great with this Spot
    }
}];

// Spotz exit notification
[[NSNotificationCenter defaultCenter] addObserverForName:SpotzRTOutsideNotification object:nil queue:nil usingBlock:^(NSNotification * _Nonnull note) {

    if (note.userInfo)
    {
        // Take out the Spotz data print what we have
        NSDictionary *data = note.userInfo;
        SpotzData *spot = data[@"data"];
        NSLog(@"Outside a predefined geofence!");

        if (spot.attributes)
        {
            // List the attributes for this spot
            NSLog(@"Spot attributes:");
            for (NSString *key in spot.attributes.allKeys)
            {
                NSLog(@"\t%@ : %@", key, spot.attributes[key]);
            }
        }

        // Do something great with this Spot
    }
}];

```

You can listen for the following notifications:

- SpotzRTInsideNotification
- SpotzRTDwellNotification
- SpotzRTOutsideNotification
...and more! Check SpotzConstant.h for a full list.

**5. Pause/resume/stop services**

In order to reduce battery consumption during non-tracking period, you can call `pauseBackgroundLocation` and `resumeBackgroundLocation` to pause/resume location tracking.

Once location services is no longer required, call `stopBackgroundLocation` to stop tracking the device.

Other methods to consider:
- Check if it has been started - `isBackgroundLocationStarted`
- Check if location is paused - `isBackgroundLocationPaused`

Contribution
============
For bugs, feature requests, or other questions, [file an issue](https://github.com/localz/Spotz3-iOS-SDK/issues/new).

License
=======
Copyright 2017 Localz Pty Ltd
