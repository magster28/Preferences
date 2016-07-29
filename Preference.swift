//
//  Preference.swift
//
//  Created by MacNeil Fernandes on 6/16/13.
//  Copyright (c) 2013 Magster. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHOR, THE VOICES IN HIS HEAD OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//  This class is meant to be as reusable as possible. Just change the keys and the
//  implementations of the classes below.
//  In addition, this class makes use of a SINGLE instance of the sharedPreference object
//  so that it can be used throughout the application.
//
//  USAGE:
//  The instance of this class will be a shared instance that is persisted throughout the application lifecycle.
//  Preference *appPrefs = [Preference sharedInstance]; -- INVOKE THE SHARED INSTANCE
//  appPrefs.lastUpdateDate = [NSDate date]; -- SET VALUES
//  [appPrefs savePreferences]; -- SAVE THE PREFERENCES
//
//  *Updated 2015/032/28 - swift usage
//  Invoke the Shared instance
//  Preference.shared
//  At the End when saving (usually - application applicationDidEnterBackground
//  Preference.saveSharedPreferences()
//
//  Additional keys to be used to save additional preferences,
//  you need to define the Constants for the key String and then the corresponding public field.
//
//  Version History
//  Version     Date        Modified By         Modification Details
//  0.11        2013/09/18  MacNeil Fernandes   Removed Night Mode
//  0.12        2013/09/20  MacNeil Fernandes   Added the Current Version of the App
//  1.01        2013/10/07  MacNeil Fernandes   Moved the #defines to externs constant Strings for Performance
//  2.01        2015/02/28  MacNeil Fernandes   Migrated implementation to swift
//  2.02        2016/07/01  MacNeil Fernandes   Changes for version SWIFT 3.0 changes

import Foundation

// This is the shared Instance that is returned using the class variable for the shared instance.
// This makes the resuse of the class easier and reduces code.
// Private only accesible within this class
private let _sharedPreference = Preference()

class Preference: NSObject {
    // MARK:- SHARED INSTANCE
    
    // This is a Class Variable. SWIFT has a special way of handling the Class Variables. It
    // always has to be in this returned form.
    class var shared:Preference{
        return _sharedPreference
    }
    
    // Create the Properties here which will be stored as a User Preference
    
    // MARK: - PREFERENCE VARIABLES
    // Customize this as needed
    
    // Default BOOLEAN value - always YES in NSUserDefault
    var preferenceUsed = false
    
    // Last time this app was used
    var dateLastUpdated = NSDate()
    // Current Version of the app
    var currentVersion = ""
    
    // MARK:- INITIALIZATION
    // The init function will run when an instance of Preferences is created.
    required override init() {
        super.init()
        #if DEBUG
            NSLog("Running %@ : %@",NSStringFromClass(self.dynamicType),#function)
        #endif
        self.setupPreferences()
    }
    
    // MARK:- UTILITY FUNCTIONS
    // Setup the user Preferences
    func setupPreferences() {
        #if DEBUG
            NSLog("Running %@ : %@",NSStringFromClass(self.dynamicType),#function)
        #endif
        
        // 1. Get the User Default Preferences
        if let userPreferences = NSUserDefaults.standardUserDefaults() as NSUserDefaults? {
            print("Preferences are initialized")
            // 2. Check if there is already a value for the PreferencesUsed BOOL Value
            //  If YES, then get that date,
            //  If NO, then it means this App is run for the First Time, hence update with Default Values
            preferenceUsed = userPreferences.boolForKey(Global.Preferences.kPreferencesUsedKey)
            if preferenceUsed {
                print("PreferencesUSED are got from the NSUserDefaults, therefore retrieve")
                retrievePreferences()
            }
            else {
                print("PreferencesUSED are NOT got from the NSUserDefaults, therefore SET DEFAULT")
                defaultPreferences()
            }
        }
    }
    
    // Retrieve the Preference values and set the values of the clas variables!
    func retrievePreferences(){
        #if DEBUG
            NSLog("Running %@ : %@",NSStringFromClass(self.dynamicType),#function)
        #endif
        if let userPreferences = NSUserDefaults.standardUserDefaults() as NSUserDefaults? {
            dateLastUpdated = userPreferences.objectForKey(Global.Preferences.kPreferencesLastUpdatedKey) as! NSDate!
            currentVersion = userPreferences.stringForKey(Global.Preferences.kPreferencesVersionKey) as NSString! as String
        }
        NSLog("Value for Date Last Updated = \(dateLastUpdated)")
        NSLog("Value of the Current Version = \(currentVersion)")
    }
    
    // Set the default values for the preferences
    func defaultPreferences(){
        #if DEBUG
            NSLog("Running %@ : %@",NSStringFromClass(self.dynamicType),#function)
        #endif
        
        // 1. Preferences are used - TRUE
        preferenceUsed = true
        // 2. Date app was last used
        dateLastUpdated = NSDate()
        
        // 3. Version of the App, set to Current version 
        currentVersion = NSBundle.mainBundle().infoDictionary!["CFBundleShortVersionString"] as! String  
    }
    
    // MARK:- CLASS FUNCTIONS
    class func save(prefs:Preference){
        
        #if DEBUG
            NSLog("save: Preference - START")
        #endif
        
        if let userPreferences = NSUserDefaults.standardUserDefaults() as NSUserDefaults? {
            
            // This is always True in the Preferences File
            userPreferences.setBool(true, forKey: Global.Preferences.kPreferencesUsedKey)
            
            // Save Custom Key values
            prefs.dateLastUpdated = NSDate()
            userPreferences.setObject(prefs.dateLastUpdated, forKey: Global.Preferences.kPreferencesLastUpdatedKey)
            userPreferences.setValue(prefs.currentVersion, forKey: Global.Preferences.kPreferencesVersionKey)
        }
        #if DEBUG
            NSLog("COMPLETED save: Preferences")
        #endif
    }
    
    class func saveSharedPreferences(){
        Preference.save(Preference.shared)
    }
    
}
