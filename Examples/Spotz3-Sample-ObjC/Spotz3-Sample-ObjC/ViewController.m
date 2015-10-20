//
//  ViewController.m
//  Spotz3-Sample-ObjC
//
//  Created by Daniel Sykes-Turner on 13/10/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//

#import "ViewController.h"
#import <SpotzSDK/SpotzSDK.h>

@interface ViewController ()
// Some UI elements to show what we can see
@property (weak, nonatomic) IBOutlet UILabel *lblSpotName;
@property (weak, nonatomic) IBOutlet UILabel *lblBeaconMajor;
@property (weak, nonatomic) IBOutlet UILabel *lblBeaconMinor;
@property (weak, nonatomic) IBOutlet UILabel *lblBeaconUUID;
@property (weak, nonatomic) IBOutlet UILabel *lblBeaconDistance;
@property (weak, nonatomic) IBOutlet UIProgressView *distanceView;
@property (weak, nonatomic) IBOutlet UILabel *lblGeofenceLatitude;
@property (weak, nonatomic) IBOutlet UILabel *lblGeofenceLongitude;

// To keep track of what we've seen
@property (strong, nonatomic) SpotzData *lastSeenSpotz;
@property (nonatomic) float maxDistance;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [self updateUISpotzExit:nil];
    
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
            [self updateUISpotzEntry:spot];
        }
    }];
    
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
            [self updateUISpotzExit:spot];
        }
    }];
    
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
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)updateUISpotzEntry:(SpotzData *)data {
    
    // Check if this beacon is different to the last one we saw,
    //  or if this is the first beacon we've seen
    if (!self.lastSeenSpotz || ![self.lastSeenSpotz.name isEqualToString:data.name])
    {
        self.lastSeenSpotz = data;
        self.maxDistance = 0;
    }
    
    // Update the distance upper bound if needed
    if (data.distance > self.maxDistance)
        self.maxDistance = data.distance;
    
    // Update the neccessary labels
    self.lblSpotName.text = [NSString stringWithFormat:@"Name: %@", data.name];
    
    if (data.beacons.count > 0)
    {
        SpotzBeaconDetails *closestBeacon = data.beacons[0];
        self.lblBeaconMajor.text = [NSString stringWithFormat:@"Major: %i", closestBeacon.major];
        self.lblBeaconMinor.text = [NSString stringWithFormat:@"Minor: %i", closestBeacon.minor];
        self.lblBeaconUUID.text = [NSString stringWithFormat:@"UUID: %@", closestBeacon.uuid.UUIDString];
        
        self.lblBeaconDistance.text = [NSString stringWithFormat:@"Distance %f", closestBeacon.distance];
        self.distanceView.progress = data.distance / self.maxDistance;
    }
    else
    {
        self.lblBeaconMajor.text = @"Major";
        self.lblBeaconMinor.text = @"Minor";
        self.lblBeaconUUID.text = @"UUID:";
        
        self.lblBeaconDistance.text = @"Distance:";
        self.distanceView.progress = 0;
    }
    
    if (data.geo)
    {
        self.lblGeofenceLatitude.text = [NSString stringWithFormat:@"Latitude: %f", data.geo.latitude];
        self.lblGeofenceLongitude.text = [NSString stringWithFormat:@"Longitude: %f", data.geo.longitude];
    }
    else
    {
        self.lblGeofenceLatitude.text = @"Latitude:";
        self.lblGeofenceLongitude.text = @"Longitude:";
    }
}

- (void)updateUISpotzExit:(SpotzData *)data {
    
    // Check if this beacon is different to the last one we saw
    if ((self.lastSeenSpotz && [self.lastSeenSpotz.name isEqualToString:data.name]) || !data)
    {
        self.lastSeenSpotz = nil;
        self.maxDistance = 0;
        
        self.lblSpotName.text = @"Name:";
        self.lblBeaconMajor.text = @"Major:";
        self.lblBeaconMinor.text = @"Minor:";
        self.lblBeaconUUID.text = @"UUID:";
        
        self.lblBeaconDistance.text = @"Distance:";
        self.distanceView.progress = 0;
        
        self.lblGeofenceLatitude.text = @"Latitude:";
        self.lblGeofenceLongitude.text = @"Longitude:";
    }
}

@end
