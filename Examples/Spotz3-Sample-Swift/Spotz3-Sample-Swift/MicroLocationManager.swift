//
//  MicroLocationManager.swift
//  Spotz3-Sample-Swift
//
//  Created by Paul Wong on 2/02/2016.
//  Copyright © 2016 Localz Pty Ltd. All rights reserved.
//

import UIKit

extension UIView : SpotzSDKDelegate {
    public func spotzInit(error: NSError?) {
    }

    public func spotzSiteInit(error: NSError?) {
    }

    public func spotzSiteChangedToSite(newSite: SpotzSiteDetails?, error: NSError?) {
    }
}

class NormalClass : NSObject, SpotzSDKDelegate {
    func spotzInit(error: NSError?) {
    }

    func spotzSiteInit(error: NSError?) {
    }

    func spotzSiteChangedToSite(newSite: SpotzSiteDetails?, error: NSError?) {
    }
}
