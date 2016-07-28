// =============================================================================
//
// ofxFabricSoftener.h
// GifAnimator
//
// Created by Andreas Borg on 7/25/16
//
// Copyright (c) 2015-2016 Andreas Borg
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================

#ifndef _ofxFabricSoftener
#define _ofxFabricSoftener

#include "ofMain.h"

#ifdef USE_CRASHLYTICS
#import <Fabric/Fabric.h>
#import <Crashlytics/Crashlytics.h>
#endif

/*
WIP
Addon to make life easier using remote logging and Fabric.


Make sure to select DWARF with dSYM File for Debug in Build Settings


1. Install and follow instructions
https://fabric.io/home



Add runscript in Build Phases
eg.

./Fabric.framework/run 0331da435e106345f6cg4563ed1704a6480185cbba eb71374594765b735cf01b750475480e68704dfdh3a9bb7a1ca0541db66c753f76




On OSX in main.mm (rename)


Include near the top in main.mm <-note mm
#include "ofMain.h"
#define USE_CRASHLYTICS
#include "ofxFabricSoftener.h"

int main( ){
    ofxFabricSoftener::setup();
...
}

 
 
On iOS in your AppRootDelegate.mm

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    ofxFabricSoftener::setup();

    [super applicationDidFinishLaunching:application];

}



C++ style
Crashlytics.sharedInstance().recordError(error)

Obj-C style
[CrashlyticsKit recordError:error];



The idea is to create a consistent log and easily be able to 
switch the flag. Not done.

#define NSLog(...) CLS_LOG(__VA_ARGS__)

So, we don't ever use CLS_LOG explicitly. We only use NSLog, but all the NSLogs make it to the Crashlytics dashboard.


    //Log messages will be part of crash reports (but not without a crash)
    //NSMutableDictionary*cLog = [[NSMutableDictionary alloc] init];
    //[cLog setObject:@"Log msg: Hey folks" forKey:@"LogKey"];
    //CLS_LOG(@"This is a crash from live machine");
    //[CrashlyticsKit setObjectValue:@"My object value" forKey:@"TjosanKey"];
    //[[Crashlytics sharedInstance] crash];




Make pretty. Add icons from Icon Composer in Apple Graphics tools
and put in data folder.

//Edit Project.xconfig to add icon
ICON_NAME_DEBUG = icon.icns
ICON_NAME_RELEASE = icon.icns
ICON_FILE_PATH = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/

//IF YOU WANT AN APP TO HAVE A CUSTOM ICON - PUT THEM IN YOUR DATA FOLDER AND CHANGE ICON_FILE_PATH to:
ICON_FILE_PATH = bin/data/

They will appear in the Fabric console.

If you enable Answers you get emails about issues.


Todo: Look at https://github.com/gameoverhack/ofxLogger/blob/master/src/ofxLogger.h
*/


inline std::string methodName(const std::string& prettyFunction)
{
    size_t colons = prettyFunction.find("::");
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = prettyFunction.rfind("(") - begin;

    return prettyFunction.substr(begin,end) + "()";
}

#define __METHOD_NAME__ methodName(__PRETTY_FUNCTION__)

inline std::string className(const std::string& prettyFunction)
{
    size_t colons = prettyFunction.find("::");
    if (colons == std::string::npos)
        return "::";
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = colons - begin;

    return prettyFunction.substr(begin,end);
}

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)


/*
inline ostream& operator<<(ostream& os, MyClass& s){
    os <<__METHOD_NAME__<<" MyClass "<<s->name<<endl;
    return os;
}

#define LOG_VERBOSE _LOG_VERBOSE, typeid(this).name(), __func__, __LINE__


*/


class ofxFabricSoftener {
	
  public:
	
	ofxFabricSoftener(){};
    
    
    static void setup(){
        #ifdef USE_CRASHLYTICS
            #if defined(TARGET_OSX)
                [[NSUserDefaults standardUserDefaults] registerDefaults:@{ @"NSApplicationCrashOnExceptions": @YES }];
            #endif
            [Fabric with:@[[Crashlytics class]]];
        #endif
    }

};

#endif
