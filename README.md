# Preferences
Utility class which makes it easy to save preferences to the NSUserDefaults in a swift project.

This class is meant to be as reusable as possible. Just change the keys and the implementations of the classes below.

This class makes use of a SINGLE instance of the sharedPreference object (Singleton)

USAGE:
The instance of this class will be a shared instance that is persisted throughout the application lifecycle.

// Objective - C
Preference *appPrefs = [Preference sharedInstance]; -- INVOKE THE SHARED INSTANCE
appPrefs.lastUpdateDate = [NSDate date]; -- SET VALUES
[appPrefs savePreferences]; -- SAVE THE PREFERENCES

//  *Updated 2015/02/28 - SWIFT
Invoke the Shared instance (Usually in didFinishLaunchingWithOptions)
Preference.shared

At the End when saving (usually in applicationDidEnterBackground)
Preference.saveSharedPreferences()

1. Create Additional keys to be used to save additional preferences, you need to define the Constants for the 
key String and then the corresponding public field.
SAMPLE:In Global.swift file, 
struct Preferences {
        static let kPreferencesUsedKey = "com.example.preferences.used"
        static let kPreferencesLastUpdatedKey = "com.example.last.update.date"
        static let kPreferencesIsFirstRun = "com.example.is.first.run"
        static let kPreferencesVersionKey = "com.example.version.key"
    }

2. While Using in Preference.swift class
preferenceUsed = userPreferences.boolForKey(Global.Preferences.kPreferencesUsedKey)

3. Add default values

4. Accomodate in case the string is new and is not present in the Preferences when the key is used for the first time.

NOTE:
I use #if DEBUG to conditionally print the Log data. Change this in the Build Settings. Add -DDEBUG or -DRELEASE
