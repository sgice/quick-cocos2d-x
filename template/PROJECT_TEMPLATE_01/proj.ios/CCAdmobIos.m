#import "CCAdmob/CCAdmobIos.h"
#import "AppController.h"
#import "RootViewController.h"

@interface CCAdmobIos(intern)
- (GADRequest *)createRequest;
- (void) loadInter;

@end

@implementation CCAdmobIos

static CCAdmobIos * instance=NULL;

+ (CCAdmobIos *)shared
{
    @synchronized(self) {
        if (instance == nil) {
            instance = [[self alloc] init];
        }
    }
    return instance;
}
- (void) init:(NSString *)admobid interstitial:(NSString *)interid position:(int)pos
{
    self.admobID = admobid;
    self.interID = interid;
    AppController* appController = (AppController*) [UIApplication sharedApplication].delegate;
    RootViewController *viewController = appController->viewController;
    int y;
    if (pos == 1) {
        y = 0 ;
    }else{
        y = viewController.view.frame.size.height-50;
    }
    self.adBanner = [[[GADBannerView alloc]
                      initWithAdSize:kGADAdSizeBanner
                      origin:CGPointMake((viewController.view.frame.size.width-320)/2,y)]
                     autorelease];
    
    // Need to set this to no since we're creating this custom view.
    NSArray *vComp = [[UIDevice currentDevice].systemVersion componentsSeparatedByString:@"."];
    
    if ([[vComp objectAtIndex:0] intValue] >= 6) {
        self.adBanner.translatesAutoresizingMaskIntoConstraints = NO;
    }
    self.adBanner.adUnitID = self.admobID;
    self.adBanner.delegate = self;
    [self.adBanner setRootViewController:viewController];
    [viewController.view addSubview:self.adBanner];
    [self.adBanner loadRequest:[self createRequest]];
    
    //[self loadInter];
    self.interAdReady=NO;
    self.interAdLoading=NO;
    
}
- (void) loadInter
{
    self.interstitialAd = [[GADInterstitial alloc] init];
    self.interstitialAd.delegate = self;
    self.interstitialAd.adUnitID = self.interID;
    self.interAdLoading = YES;
    self.interAdReady = NO;
    [self.interstitialAd loadRequest:[self createRequest]];
}
- (bool) showInter
{
    bool shown = false;
    if (self.interAdReady) {
        AppController* appController = (AppController*) [UIApplication sharedApplication].delegate;
        RootViewController *viewController = appController->viewController;
        [self.interstitialAd presentFromRootViewController:viewController];
        self.interAdReady = NO;
        shown = true;
    }else if(!self.interAdLoading){
        [self loadInter];
    }
    return shown;
}
- (void)interstitialDidReceiveAd:(GADInterstitial *)interstitial {
    NSLog(@"Received admob interstitial successfully");
    self.interAdLoading=NO;
    self.interAdReady=YES;
}

- (void)interstitial:(GADInterstitial *)interstitial
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"Failed to receive admob interstitial with error: %@", [error localizedFailureReason]);
    self.interAdReady=NO;
    self.interAdLoading=NO;
}

- (void) showBanner
{
    self.adBanner.hidden = NO;
}
- (void) hideBanner
{
    self.adBanner.hidden = YES;
}

- (void)adViewDidReceiveAd:(GADBannerView *)adView {
    NSLog(@"Received admob banner successfully");
}
- (void)adView:(GADBannerView *)view
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"Failed to receive admob banner with error: %@", [error localizedFailureReason]);
}
- (void)interstitialDidDismissScreen:(GADInterstitial *)ad{
    [self loadInter];
}
- (GADRequest *)createRequest
{
    GADRequest *request = [GADRequest request];
    
    // Make the request for a test ad. Put in an identifier for the simulator as
    // well as any devices you want to receive test ads.
    request.testDevices = @[
     GAD_SIMULATOR_ID
    ];
    return request;
}
@end