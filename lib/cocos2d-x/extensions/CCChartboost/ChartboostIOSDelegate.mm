#import "ChartboostIOSDelegate.h"

@implementation ChartboostIOSDelegate

-(BOOL)shouldRequestInterstitialsInFirstSession{
    return YES;
}
-(void)didDismissInterstitial:(CBLocation)location{
    NSLog(@"cache chartboost interstitial: %@\n", location );
    [Chartboost cacheInterstitial:location];
}
-(void)didDismissMoreApps{
    [Chartboost cacheMoreApps:CBLocationHomeScreen];
}
-(void)didFailToLoadInterstitial:(CBLocation)location withError:(CBLoadError)error{
    NSLog(@"fail to load chartboost interstitial, location: %@, error %d\n", location, error-CBLoadErrorInternal );
}
-(void)didCacheMoreApps{
    
}
-(void)didCacheInterstitial:(CBLocation)location{
    NSLog(@"success cache interstitial location: %@\n", location);
}
@end