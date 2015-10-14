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
SpotzSDK.initializeWithAppId("<Enter your app ID here>", clientKey: "<Enter your client key here>", delegate: self, withOptions:nil)
```

Objective-C
```
[SpotzSDK initializeWithAppId:@"<Enter your app ID here>" clientKey:@"<Enter your client key here>" delegate:self withOptions:nil];
```

When initialization is successful, it will call the spotzSDKInitSuccessfull delegate method

**3. Start services**

Swift
```
func spotzInit(error: NSError?)
{
    if let error = error
    {
        NSLog("Error initializing spot %@",error)
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
        NSLog("Error initalizing spotz sites %@",error)
    }
}

func spotzSiteChangedToSite(newSite: SpotzSiteDetails!, error: NSError?)
{
    if let error = error
    {
        NSLog("Error updating to new site %@. %@",newSite.siteId, error);
    }
    else
    {
        NSLog("Updated to new site %@",newSite.siteId);
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
// Set up to receive notifications from your spots
NSNotificationCenter.defaultCenter().addObserverForName(SpotzInsideNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in
    if let data = note.userInfo as? NSDictionary
    {
        // Take out the Spotz object and its beacon
        if let spot = data["data"] as? SpotzData
        {
            // Entry region will be either a geofence or a beacon
            if let beacons = spot.beacons
            {
                NSLog("Entry beacon (%@) detected with UUID: %@ major: %i minor: %i",spotz.name,beacon.uuid,beacon.major,beacon.minor);
            }
            else if let geo = spot.geo
            {
                NSLog("Entry geofence (%@) detected with latitude: %f longitude: %f radius %i",geo.name,geo.latitude,geo.longitude,Int(geo.radius));
            }

            // Do something great with this Spot
        }
    }
}

NSNotificationCenter.defaultCenter().addObserverForName(SpotzRangingNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in
    if let data: NSDictionary = note.object as? NSDictionary
    {
        if let spot = data["data"] as? SpotzData
        {
            NSLog("Spot id: %@ name: %@",spot.spotId,spot.name);
            // Do something with this Spotz data
        }

        // get closest beacon
        let spotBeacon = spot.beacons[0];

        NSLog("Distance is (%@) m",spotBeacon.distance())

        // Do something great with this Spot
    }
}
```

Objective-C
```
[[NSNotificationCenter defaultCenter] addObserverForName:SpotzInsideNotification object:nil queue:nil usingBlock:^(NSNotification *note) {
    if (note.object)
    {
        // Take out the Spotz object and its beacon
        NSDictionary *data = note.userInfo;
        SpotzData *spot = data[@"data"];

        if(spot.beacons.count > 0)
        {
            // get closest beacon
            SpotzBeaconDetails *beacon = spot.beacons[0];
            NSLog(@"Entry beacon (%@) detected with UUID: %@ major: %i minor: %i",spot.name,beacon.uuid,beacon.major,beacon.minor);
        }
        else if (spot.geo)
        {
            SpotzGeoDetails *geo = spot.geo;
            NSLog(@"Entry geofence (%@) detected with latitude: %f longitude %f",spot.name,geo.latitude,geo.longitude);
        }

        // Do something great with this Spot
    }
}];

[[NSNotificationCenter defaultCenter] addObserverForName:SpotzRangingNotification object:nil queue:nil usingBlock:^(NSNotification *note) {
    if (note.object)
    {
        NSDictionary *data = note.userInfo;

        SpotzData *spot = data[@"data"];
        NSNumber *acc = data[@"accuracy"];

        NSLog(@"Spot id: %@ name: %@",spot.spotId,spot.name);

        // get closest beacon
        SpotzBeaconDetails *beacon = spotz.beacons[0];

        NSLog(@"Distance is %@ m", [beacon distance]);

        // Do something great with this Spot
    }
}];
```

You can listen for the following notifications:

- SpotzInsideNotification
- SpotzOutsideNotification
- SpotzRangingNotification
- SpotzInsideSiteGeoNotification
- SpotzOutsideSiteGeoNotification

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
