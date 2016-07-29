// FOR HISTORICAL PURPOSES ONLY
//
//  Preference.h
//  Photo Math
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
//  This class is meant to be as resuaable as possible. Just change the keys and the
//  implementations of the classes below.
//  In addition, this class makes use of a SINGLE instance of the sharedPreference object
//  so that it can be used throughout the application.

#import "Preference.h"
#import "UtilityConstants.h"
//#import "Metadata.h"

/*
 * This is the static class that is used for the management for the share preferences
 * used throughout the app. The Clas method will take care of instantiatiomn of this shared
 * preference object
 */
@implementation Preference

// This is the Static preference variable that will be used throughout the app
static Preference *sharedInstance = nil;

#pragma mark - INITIALIZATION
-(id)init{
    if (DEBUG) NSLog(@"Running %@ %@", self.class , NSStringFromSelector(_cmd));
    if (self = [super init]){
        [self loadPreferences];
    }
    return self;
}


#pragma mark - PRIVATE FUNCTIONS
/*!
 * This is the function that loads the preferences.
 * If the NSUserDefaults is already set load the values from there,
 * Else Set to the default values
 */
-(void)loadPreferences{
    if (DEBUG) NSLog(@"Running %@ %@", self.class , NSStringFromSelector(_cmd));
    
    // 1. Get the User Default NSuSerDefaults Object
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    
    // 2. Check for the validity of the user Defaults
    if (userDefaults){
        
        // Check the file to see if there are values present else set default values
        // 4. Get the Last Updated Date
        _lastUpdateDate = [userDefaults objectForKey:KEY_LAST_TIME_UPDATED];
    
        if (_lastUpdateDate){
            //NSLog(@"%@", _lastUpdateDate);
            // 3. Retrieve the values for the various Keys
            _isUsedMoreThanOnce = [userDefaults boolForKey:KEY_IS_USED_MORE_THAN_ONCE];
            //_isNightModeOn = [userDefaults boolForKey:KEY_NIGHT_MODE];
            _currentVersion = [userDefaults objectForKey:KEY_CURRENT_VERSION];
        } else{
            // This means that we need to set to the default values
            [self setDefaultPreferences];
            
            // Save the data to the NSUserDefaults file
            [self savePreferences];
        }
    }
}

#pragma mark - CLASS FUNCTION
/*!
 * This is the class method that will return the static instance of the preference class.
 * the classes that wish to leverage the shared preferences need to make a call to this CLASS FUNCTION.
 * \returns Static instance of the Preference class.
 */
+(Preference *) sharedInstance{
    if (DEBUG) NSLog(@"Running %@ %@", self.class , NSStringFromSelector(_cmd));
    
    if (nil == sharedInstance){
        // This means that the sharedInstance was never set. Therefore call the init function
        // which in turn will set the values to the values last used or the values that are Default
        sharedInstance = [[self alloc]init];
    }
    return sharedInstance;
}

#pragma mark - PUBLIC FUNCTION
/*!
 * This is the Function that will save the data in the NSUserDefaults file
 */
-(void)savePreferences{
    if (DEBUG) NSLog(@"Running %@ %@", self.class , NSStringFromSelector(_cmd));
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    if (DEBUG) NSLog(@"SAVING -- Last Update Date: %@", _lastUpdateDate);
    [userDefaults setObject:_lastUpdateDate forKey:KEY_LAST_TIME_UPDATED];
    if (DEBUG) NSLog(@"SAVING -- Used More than Once: %@", _isUsedMoreThanOnce? @"YES":@"NO");
    [userDefaults setBool:_isUsedMoreThanOnce forKey:KEY_IS_USED_MORE_THAN_ONCE];
    if (DEBUG) NSLog(@"SAVING -- Current Version: %@", _currentVersion);
    [userDefaults setObject:_currentVersion forKey:KEY_CURRENT_VERSION];
    [userDefaults synchronize];
}

/*!
 * Function that will set the default Preferences
 */
-(void)setDefaultPreferences{
    if (DEBUG) NSLog(@"Running %@ %@", self.class , NSStringFromSelector(_cmd));
    
    _lastUpdateDate = [NSDate date];
    //_isNightModeOn = NO;
    _currentVersion = [Metadata version];
}


@end
