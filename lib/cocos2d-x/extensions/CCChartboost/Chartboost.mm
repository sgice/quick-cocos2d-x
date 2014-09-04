#include "CCChartboost.h"
#import "Chartboost.h"
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
    Chartboost *cb = [Chartboost sharedChartboost];
    
    cb.appId = [NSString stringWithUTF8String:appid];
    cb.appSignature = [NSString stringWithUTF8String:signature];
    
    // Required for use of delegate methods. See "Advanced Topics" section below.
    cb.delegate = cb_delegate;
    NSLog(@"chartboost startsession with appid %@, sign %@\n", cb.appId, cb.appSignature);
    // Begin a user session. Must not be dependent on user actions or any prior network requests.
    // Must be called every time your app becomes active.
    [cb startSession];
    
    // Show an interstitial
    //[cb cacheInterstitial];
    [cb cacheMoreApps];
}
bool CCChartboost::showAds(){
    bool shown = false;
    Chartboost *cb = [Chartboost sharedChartboost];
    
    if ([cb hasCachedInterstitial]){
        [cb showInterstitial];
        shown = true;
    }else{
        [cb cacheInterstitial];
    }
    return shown;
}
void CCChartboost::showMoreApp(){
    Chartboost *cb = [Chartboost sharedChartboost];
    
    [cb showMoreApps];
}
