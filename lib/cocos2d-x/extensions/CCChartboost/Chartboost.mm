#include "CCChartboost.h"
#import <Chartboost/Chartboost.h>
#import "ChartboostIOSDelegate.h"

CCChartboost *CCChartboost::s_instance = NULL;
ChartboostIOSDelegate *cb_delegate = NULL;

CCChartboost *CCChartboost::instance(){
    if (s_instance == NULL){
        s_instance = new CCChartboost();
        cb_delegate = [[ChartboostIOSDelegate alloc] init];
    }
    return s_instance;
}

void CCChartboost::startSession(const char* appid, const char *signature){
    // Begin a user session. Must not be dependent on user actions or any prior network requests.
    // Must be called every time your app becomes active.
    [Chartboost startWithAppId:[NSString stringWithUTF8String:appid] appSignature:[NSString stringWithUTF8String:signature] delegate:cb_delegate];
    
    // Show an interstitial
    //[cb cacheInterstitial];
    //[Chartboost cacheMoreApps];
}
bool CCChartboost::showAds(){
    bool shown = false;
    if ([Chartboost hasInterstitial:CBLocationHomeScreen]){
        [Chartboost showInterstitial:CBLocationHomeScreen];
        shown = true;
    }else{
        [Chartboost cacheInterstitial:CBLocationHomeScreen];
    }
    return shown;
}
void CCChartboost::showMoreApp(){
    [Chartboost showMoreApps:CBLocationHomeScreen];
}
