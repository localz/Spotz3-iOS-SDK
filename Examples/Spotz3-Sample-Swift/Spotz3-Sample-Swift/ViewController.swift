//
//  ViewController.swift
//  Spotz3-Sample-Swift
//
//  Created by Daniel Sykes-Turner on 13/10/2015.
//  Copyright © 2015 Localz Pty Ltd. All rights reserved.
//

import UIKit


class ViewController: UIViewController {
    // Some UI elements to show what we can see
    @IBOutlet weak var lblSpotName: UILabel!
    @IBOutlet weak var lblBeaconMajor: UILabel!
    @IBOutlet weak var lblBeaconMinor: UILabel!
    @IBOutlet weak var lblBeaconUUID: UILabel!
    @IBOutlet weak var lblBeaconDistance: UILabel!
    @IBOutlet weak var distanceView: UIProgressView!
    @IBOutlet weak var lblGeofenceLatitude: UILabel!
    @IBOutlet weak var lblGeofenceLongitude: UILabel!
    
    // To keep track of what we've seen
    var lastSeenSpotz: SpotzData?
    var maxDistance: Float = 0
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        self.updateUISpotzExit(nil)
        
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
                self.updateUISpotzEntry(spot)
            }
        }
        
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
                self.updateUISpotzExit(spot)
            }
        }
        
        NSNotificationCenter.defaultCenter().addObserverForName(SpotzRangingNotification, object: nil, queue: nil) { (note:NSNotification!) -> Void in
            
            if let data = note.userInfo,
                let spot = data["data"] as? SpotzData
            {
                print("Range Spotz: \(spot.name) at \(spot.distance())")
                
                // Do something great with this Spot
                self.updateUISpotzEntry(spot)
            }
        }
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func updateUISpotzEntry(data :SpotzData!) {
    
        // Check if this beacon is different to the last one we saw,
        //  or if this is the first beacon we've seen
        if (self.lastSeenSpotz == nil || self.lastSeenSpotz!.name != data.name)
        {
            self.lastSeenSpotz = data
            self.maxDistance = 0
        }
        
        // Update the distance upper bound if needed
        if (data.distance() > self.maxDistance)
        {
            self.maxDistance = data.distance()
        }
        
        // Update the neccessary labels
        self.lblSpotName.text = "Name: \(data.name)"
        
        if (data.beacons.count > 0),
            let closestBeacon = data.beacons[0] as? SpotzBeaconDetails
        {
            self.lblBeaconMajor.text = "Major: \(closestBeacon.major)"
            self.lblBeaconMinor.text = "Minor: \(closestBeacon.minor)"
            self.lblBeaconUUID.text = "UUID: \(closestBeacon.uuid.UUIDString)"
            
            self.lblBeaconDistance.text = "Distance \(closestBeacon.distance)"
            self.distanceView.progress = data.distance() / self.maxDistance
        }
        else
        {
            self.lblBeaconMajor.text = "Major"
            self.lblBeaconMinor.text = "Minor"
            self.lblBeaconUUID.text = "UUID:"
            
            self.lblBeaconDistance.text = "Distance:"
            self.distanceView.progress = 0
        }
        
        if (data.geo != nil)
        {
            self.lblGeofenceLatitude.text = "Latitude: \(data.geo.latitude)"
            self.lblGeofenceLongitude.text = "Longitude: \(data.geo.longitude)"
        }
        else
        {
            self.lblGeofenceLatitude.text = "Latitude:"
            self.lblGeofenceLongitude.text = "Longitude:"
        }
    }
    
    func updateUISpotzExit(data :SpotzData?) {
    
        // Check if this beacon is different to the last one we saw
        if (data == nil || (self.lastSeenSpotz != nil && self.lastSeenSpotz!.name == data!.name))
        {
            self.lastSeenSpotz = nil
            self.maxDistance = 0
            
            self.lblSpotName.text = "Name:"
            self.lblBeaconMajor.text = "Major:"
            self.lblBeaconMinor.text = "Minor:"
            self.lblBeaconUUID.text = "UUID:"
            
            self.lblBeaconDistance.text = "Distance:"
            self.distanceView.progress = 0
            
            self.lblGeofenceLatitude.text = "Latitude:"
            self.lblGeofenceLongitude.text = "Longitude:"
        }
    }
}

