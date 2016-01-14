Spotz SDK
==========

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

**Other things to remember**

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
Copyright 2015 Localz Pty Ltd
