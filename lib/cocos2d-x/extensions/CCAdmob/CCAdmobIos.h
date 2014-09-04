#import "admob/GADAdSize.h"
#import "admob/GADBannerView.h"
#import "admob/GADInterstitial.h"
#import "admob/GADInterstitialDelegate.h"

@interface CCAdmobIos : NSObject <GADBannerViewDelegate, GADInterstitialDelegate>

@property(strong, nonatomic) GADBannerView *adBanner;
@property(strong, nonatomic) GADInterstitial *interstitialAd;
@property(strong, nonatomic) NSString *admobID;
@property(strong, nonatomic) NSString *interID;
@property(nonatomic) bool interAdReady;
@property(nonatomic) bool interAdLoading;

+ (CCAdmobIos*)shared;

- (void) init:(NSString *)admobid interstitial:(NSString *)interid position:(int)pos;
- (bool) showInter;
- (void) showBanner;
- (void) hideBanner;
@end
