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
//
//  USAGE: 
//  The instance of this class will be a shared instance that is persisted throughout the application lifecycle.
//  Preference *appPrefs = [Preference sharedInstance]; -- INVOKE THE SHARED INSTANCE
//  appPrefs.lastUpdateDate = [NSDate date]; -- SET VALUES
//  [appPrefs savePreferences]; -- SAVE THE PREFERENCES
//
//  Additional keys to be used to save additional preferences,
//  you need to define the Constants for the key String and then the corresponding public field.
//
//  Version History
//  Version     Date        Modified By         Modification Details
//  0.11        2013/09/18  MacNeil Fernandes   Removed Night Mode
//  0.12        2013/09/20  MacNeil Fernandes   Added the Current Version of the App
//  1.01        2013/10/07  MacNeil Fernandes   Moved the #defines to externs constant Strings for Performance

#import <Foundation/Foundation.h>

/* Keys for the NSUserDefaults file */

// Key for the Last Date and time updated
//#define KEY_LAST_TIME_UPDATED @"last_time_updated"
// Key for the App is used more than Once
//#define KEY_IS_USED_MORE_THAN_ONCE @"is_used_more_than_once"
// Key for the Night Mode of the App
//#define KEY_NIGHT_MODE @"night_mode"
/// Key for the Current Version of App
//#define KEY_CURRENT_VERION @"current_version"

@interface Preference : NSObject

#pragma mark - PUBLIC API
/*!
 * Last Time the app was used 
 */
@property (nonatomic) NSDate *lastUpdateDate;
/*!
 * Appliation has been used more than once. This is a flag that will have a 
 * NO value only for the First time the application is run 
 */
@property (nonatomic) BOOL isUsedMoreThanOnce;
/*!
 * The Current Version string for the application
 */
@property (nonatomic, strong) NSString *currentVersion;

#pragma mark - CLASS METHOD
+(Preference *) sharedInstance;

#pragma mark - PUBLIC FUNCTIONS
-(void) savePreferences;
-(void) setDefaultPreferences;
@end
