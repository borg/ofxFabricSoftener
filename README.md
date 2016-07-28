# ofxFabricSoftener
Make remote logging with Fabric easy


[Fabric](https://fabric.io/home) (former Crashlytics) is fantastic for remote logging iOS and OSX (and Android) and it works with openFrameworks apps.

This is super quick WIP with purpose to make life easier using remote logging and Fabric. It's more instructions than an addon.



1. Install and follow [instructions](https://fabric.io/home)
2. Set your bunde identifieir
3. Add your app from Fabric app and follwo instructions
4. Make sure to select DWARF with dSYM File for Debug in Build Settings
5. Make pretty. Add icons from Icon Composer in Apple Graphics tools and put in data folder.
6. Edit Project.xconfig to add icon They will appear in the Fabric console.
7. If you enable Answers you get emails about issues.

Note: Logs only appear in Fabric console on crash and restart.




On OSX in main.mm (rename)
`
#include "ofMain.h"
#define USE_CRASHLYTICS
#include "ofxFabricSoftener.h"
`
Include near the top in main.mm <-note mm

`
int main( ){
    ofxFabricSoftener::setup();
...
}`


 
 
On iOS in your AppRootDelegate.mm
`
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    ofxFabricSoftener::setup();

    [super applicationDidFinishLaunching:application];

}
`


C++ style
`
Crashlytics.sharedInstance().recordError(error)
`

Obj-C style
`
[CrashlyticsKit recordError:error];
`


The idea is to create a consistent log and easily be able to 
switch the flag. Not done.
`

#define NSLog(...) CLS_LOG(__VA_ARGS__)
`

So, we don't ever use CLS_LOG explicitly. We only use NSLog, but all the NSLogs make it to the Crashlytics dashboard.


    //Log messages will be part of crash reports (but not without a crash)
    //NSMutableDictionary*cLog = [[NSMutableDictionary alloc] init];
    //[cLog setObject:@"Log msg: Hey folks" forKey:@"LogKey"];
    //CLS_LOG(@"This is a crash from live machine");
    //[CrashlyticsKit setObjectValue:@"My object value" forKey:@"TjosanKey"];
    //[[Crashlytics sharedInstance] crash];



Todo: Look at https://github.com/gameoverhack/ofxLogger/blob/master/src/ofxLogger.h
*/

