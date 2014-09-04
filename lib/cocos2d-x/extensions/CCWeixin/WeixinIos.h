#import "WXApi.h"
#import "CCWeixin.h"

@interface WeixinIos : NSObject <WXApiDelegate>
{
    WeixinObserver *observer_;
}

+ (WeixinIos*)shared;

- (BOOL)handleOpenURL:(NSURL *)url;
- (void)registerObserver:(WeixinObserver*)observer;
@end
