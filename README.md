Spotz SDK 3.1.4
===============

## Adding the Spotz SDK framework to your project

Just add the following line to your Podfile:
```
pod 'SpotzSDK', :git => 'https://github.com/localz/Spotz3-iOS-SDK.git'
```

How to use the SDK
==================

**Currently only devices that support Bluetooth Low Energy (iPhone 4s or above, running iOS 7 or better) are able to make use of the Spotz SDK**. It is safe to include the SDK on earlier versions of iOS or devices that don't support Bluetooth Low Energy.

There are only 4 actions to implement - **configure, initialize, start services and listen!**

*Refer to the sample app code for a working implementation of the SDK.*


**1. Set authorization message**

For iOS 8 or later, please add the following key to Info.plist with a message that will be presented to the user when they first start the app.
```
NSLocationAlwaysUsageDescription
```

**2. Initialize the Spotz SDK**

Import the SpotzSDK header into the AppDelegate, then in the didFinishLaunchingWithOptions method add the following:

Swift
```
SpotzSDK.initWithAppId("<Enter your app ID here>", appKey: "<Enter your client key here>", delegate: self, config:nil)
```

Objective-C
```
[SpotzSDK initWithAppId:@"<Enter your app ID here>" appKey:@"<Enter your client key here>" delegate:self config:nil];
```

When initialization is successful, it will call the spotzSDKInitSuccessfull delegate method

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
        SpotzSDK.shared().startSpotz()
    }
}

func spotzSiteInit(error: NSError?)
{
    if let error = error
    {
        NSLog("Error initalizing spotz sites \(error)")
    }
}

func spotzSiteChangedToSite(newSite: SpotzSiteDetails!, error: NSError?)
{
    if let error = error
    {
        NSLog("Error updating to new site \(newSite.siteId). \(error)");
    }
    else
    {
        print("Updated to new site \(newSite.siteId)");
    }
}

```

Objective-C
```
- (void)spotzInit:(NSError *)error
{
    if(!error)
    {
        [[SpotzSDK shared] startSpotz];
    }
    else
    {
        NSLog(@"Error initializing spot %@",error);
    }
}

- (void)spotzSiteInit:(NSError *)error
{
    if (error)
    {
        NSLog(@"Error initalizing spotz sites");
    }
}

- (void)spotzSiteChangedToSite:(SpotzSiteDetails *)newSite error:(NSError *)error
{
    if(error)
    {
        NSLog(@"Error updating to new site %@",newSite.siteId);
    }
    else
    {
        NSLog(@"Updated to new site %@",newSite.siteId);
    }
}
```

You can place this listener where it makes sense

**4. Listen for notifications**

Swift
```
// Spotz entry notification
NSNotificationCenter.defaultCenter().addObserverForName(SpotzInsideNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in

    if let data = note.userInfo,
        let spot = data["data"] as? SpotzData
    {
        // Take out the Spotz data print what we have
        print("Inside Spotz!")

        if spot.beacons.count > 0,
            let beacon = spot.beacons[0] as? SpotzBeaconDetails
        {
            // Print out the closest beacon
            print("Entry beacon (\(spot.name)) detected with UUID: \(beacon.uuid.UUIDString) major: \(beacon.major) minor: \(beacon.minor)")
        }
        if let geo = spot.geo
        {
            // Print out the geofence if there is one
            print("Entry geofence (\(spot.name)) detected with latitude: \(geo.latitude) longitude \(geo.longitude)");
        }
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
NSNotificationCenter.defaultCenter().addObserverForName(SpotzOutsideNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in

    if let data = note.userInfo,
        let spot = data["data"] as? SpotzData
    {
        // Take out the Spotz data print what we have
        print("Outside Spotz!")

        if spot.beacons.count > 0,
            let beacon = spot.beacons[0] as? SpotzBeaconDetails
        {
            // Print out the closest beacon
            print("Exit beacon (\(spot.name)) detected with UUID: \(beacon.uuid.UUIDString) major: \(beacon.major) minor: \(beacon.minor)")
        }
        if let geo = spot.geo
        {
            // Print out the geofence if there is one
            print("Exit geofence (\(spot.name)) detected with latitude: \(geo.latitude) longitude \(geo.longitude)");
        }
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

// Spotz ranging notification
NSNotificationCenter.defaultCenter().addObserverForName(SpotzRangingNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in

    if let data = note.userInfo,
        let spot = data["data"] as? SpotzData
    {
        print("Range Spotz: \(spot.name) at \(spot.distance())")

        // Do something great with this Spot
    }
}
```

Objective-C
```
// Spotz entry notification
[[NSNotificationCenter defaultCenter] addObserverForName:SpotzInsideNotification object:nil queue:nil usingBlock:^(NSNotification *note)
{
    if (note.userInfo)
    {
        // Take out the Spotz data print what we have
        NSDictionary *data = note.userInfo;
        SpotzData *spot = data[@"data"];
        NSLog(@"Inside Spotz!");

        if(spot.beacons.count > 0)
        {
            // Print out the closest beacon
            SpotzBeaconDetails *beacon = spot.beacons[0];
            NSLog(@"Entry beacon (%@) detected with UUID: %@ major: %i minor: %i",spot.name,beacon.uuid.UUIDString,beacon.major,beacon.minor);
        }
        if (spot.geo)
        {
            // Print out the geofence if there is one
            SpotzGeoDetails *geo = spot.geo;
            NSLog(@"Entry geofence (%@) detected with latitude: %f longitude %f",spot.name,geo.latitude,geo.longitude);
        }
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
[[NSNotificationCenter defaultCenter] addObserverForName:SpotzOutsideNotification object:nil queue:nil usingBlock:^(NSNotification * _Nonnull note) {

    if (note.userInfo)
    {
        // Take out the Spotz data print what we have
        NSDictionary *data = note.userInfo;
        SpotzData *spot = data[@"data"];
        NSLog(@"Outside Spotz!");

        if(spot.beacons.count > 0)
        {
            // Print out the closest beacon
            SpotzBeaconDetails *beacon = spot.beacons[0];
            NSLog(@"Exit beacon (%@) detected with UUID: %@ major: %i minor: %i",spot.name,beacon.uuid.UUIDString,beacon.major,beacon.minor);
        }
        if (spot.geo)
        {
            // Print out the geofence if there is one
            SpotzGeoDetails *geo = spot.geo;
            NSLog(@"Exit geofence (%@) detected with latitude: %f longitude %f",spot.name,geo.latitude,geo.longitude);
        }
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

// Spotz ranging notification
[[NSNotificationCenter defaultCenter] addObserverForName:SpotzRangingNotification object:nil queue:nil usingBlock:^(NSNotification *note)
{
    if (note.userInfo)
    {
        NSDictionary *data = note.userInfo;
        SpotzData *spot = data[@"data"];

        NSLog(@"Range Spotz: %@ at %f", spot.name, spot.distance);

        // Do something great with this Spot
        [self updateUISpotzEntry:spot];
    }
}];
```

You can listen for the following notifications:

- SpotzInsideNotification
- SpotzOutsideNotification
- SpotzRangingNotification
- SpotzInsideSiteGeoNotification
- SpotzOutsideSiteGeoNotification
...and more! Check SpotzConstant.h for a full list.

**5. Add details to the SDK for Integrations (Optional)**

If you'd like to integrate the Spotz system with your own servers or one of integration partners, have a look at the [Spotz Integration Documents](https://github.com/localz/Spotz-Docs) on how to do this.

To pass information to our SDK, please use the following lines of code.

Objective-C
```
[[SpotzSDK shared] updateExtension:@"Pony Play" type:@"httpWebook" data:@{@"type":@"pony",@"name":@"sparkles"}]
```
Swift
```
SpotzSDK.shared().updateExtension("Pony Play", type: "httpWebhook", data: ["type":"pony","name":"thunder"])
```

**6. Implement Closest Beacon Notification (experimental)**

There may be a need to only show the closest beacon to the device at a particular time. This could be because you’re in a busy environment with lots of beacons, and the information you’re trying to present is only applicable to the beacon that’s nearby. From SDK v3.1.4.2 we have made this easier and included this logic within our SDK.

#### Configuration
To enable notifications for the closest Spot only, pass the 'enableSmoothing' flag with a value of 'true' to the SDK:

Swift
```
SpotzSDK.initWithAppId("<Enter your app ID here>", appKey: "<Enter your client key here>", delegate: self, config:["enableSmoothing":"true"])
```

Objective-C
```
[SpotzSDK initWithAppId:@"<Enter your app ID here>" appKey:@"<Enter your client key here>" delegate:self config:@{@"enableSmoothing":@"true"}];
```

#### Listen for SpotzClosestBeaconNotification notification
Once enabled, it will start sending SpotzClosestBeaconNotification of the closest ranging type beacons that are detected:

Swift
```
// Spotz Closest Beacon Spot
NSNotificationCenter.defaultCenter().addObserverForName(SpotzClosestBeaconNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in

    if let data = note.userInfo,
        let spot = data["data"] as? SpotzData
    {
        print("Range Spotz: \(spot.name) at \(spot.distance())")

        // Do something great with this Spot
    }
    else
    {
        // no closest beacons found i.e all beacons are out of range
    }
}
```

Objective-C
```
// Spotz Closest Beacon Spot
[[NSNotificationCenter defaultCenter] addObserverForName:SpotzClosestBeaconNotification object:nil queue:nil usingBlock:^(NSNotification *note)
{
    if (note.userInfo)
    {
        NSDictionary *data = note.userInfo;
        SpotzData *spot = data[@"data"];

        NSLog(@"Closest spot: %@ at %f", spot.name, spot.distance);

        // Do something great with this Spot
        // ...
    }
    else
    {
        // no closest beacons found i.e all beacons are out of range
    }
}];
```

#### Set the Spot to ‘Range’
Ensure the beacon spot is set to range. Go to Spotz console -> [Project name] -> Application Setup -> Spots -> [Spot name] -> Spot Triggers -> Configuration, and set the Spot beacon ranging to 'Far' distance

#### Set the Cut-off Distances
The cutoff distance will help in filtering out the beacons that we are not interested in detecting at a particular location. We have developed a tool that will assist you in setting this up.

##### Using Beacon Scanner App
Send us an email to get access to the beta version of the 'Beacon Scanner' app and login to your account.

##### Manually
Each spot will need to be configured with a cutoff distance. Since each hardware device may read the beacon differently, using the below configuration, we can set out the 'effective range' for each spot

Add the following to the Spot's attribute:

```
name: cufoff_distance/Apple
value: <the value detected by the beacon scanner>
```
with the cutoff value for Apple iOS devices

```
name: cufoff_distance
value: <the value detected by the beacon scanner>
```
This cutoff value will be applied to all Android devices

**7. Implement background fetch to keep Spotz changes up to date (Optional)**

To ensure the changes on the Spotz console are applied across the devices while app is in the background (not killed), do the following:

1. Ensure that you have checked the box in the Background Modes -> Background fetch of your app's Capabilities section.

2. In the didFinishLaunchingWithOptions

    Objective-C
    ```
    [[UIApplication sharedApplication] setMinimumBackgroundFetchInterval:UIApplicationBackgroundFetchIntervalMinimum];
    ```

    Swift
    ```
    UIApplication.sharedApplication().setMinimumBackgroundFetchInterval(UIApplicationBackgroundFetchIntervalMinimum)
    ```

3. Implement performFetchWithCompletionHandler method in your app delegate to handle the background fetch.

    Objective-C
    ```
    - (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler
    {
        [[SpotzSDK shared] appPerformFetchWithCompletionHandler:completionHandler];
    }
    ```

    Swift
    ```
    func application(application: UIApplication, performFetchWithCompletionHandler completionHandler: (UIBackgroundFetchResult) -> Void) {
        SpotzSDK.shared().appPerformFetchWithCompletionHandler(completionHandler)
    }
    ```

**Other things to remember**

When Spots are triggered while device is unable to communicate with the server, the events are stored locally until the device is back online and another trigger event occurs. If extension is set for the Spot, it may trigger the events multiple times in a short period of time. It is recommended that the extension endpoint checks for the date of the event before processing it as the event received may no longer be relevant or valid.

When the above event occurs, only the last response from the extension will be returned to the to the client (if extension response is enabled).

Offline events that have been cached will be removed if the app is killed or no Spot has been triggered before the device comes back online.

When available, SpotzBeaconDetails or SpotzGeoDetails object is set in the SpotzData, for both SpotzInsideNotification and SpotzOutsideNotification events.

You cannot monitor for more than 20 regions (20 regions = total beacons + total geofences) per app.
There is also a device limit which you are not told about. On smaller devices (e.g. iPod touch) this is 20 regions. On larger devices (e.g. iPhone 6) this is 30 regions.
Spotz SDK will try its best to go around this limitation. Look out for any warnings in the log file when the SDK detected more than 20 registered within the app.

Geofences are not as accurate as beacons, AT BEST they have an accuracy of 5 meters.
So it is very possible that a devices can physically cross a geofences area but not be picked up because the device still thinks it is outside due to the low accuracy. Walking around a little may help.

Contribution
============
For bugs, feature requests, or other questions, [file an issue](https://github.com/localz/Spotz3-iOS-SDK/issues/new).

License
=======
Copyright 2017 Localz Pty Ltd
