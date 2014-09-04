#import "ChartboostIOSDelegate.h"

@implementation ChartboostIOSDelegate

-(BOOL)shouldRequestInterstitialsInFirstSession{
    return YES;
}
-(void)didDismissInterstitial:(CBLocation)location{
    NSLog(@"cache chartboost interstitial: %llu\n", location );
    [[Chartboost sharedChartboost] cacheInterstitial:location];
}
-(void)didDismissMoreApps{
    [[Chartboost sharedChartboost] cacheMoreApps];
}
-(void)didFailToLoadInterstitial:(CBLocation)location withError:(CBLoadError)error{
    NSLog(@"fail to load chartboost interstitial, location: %llu, error %d\n", location, error-CBLoadErrorInternal );
    //[[Chartboost sharedChartboost] cacheInterstitial:location];
}
-(void)didCacheMoreApps{
    
}
-(void)didCacheInterstitial:(CBLocation)location{
    NSLog(@"success cache interstitial location: %llu\n", location);
}
@end