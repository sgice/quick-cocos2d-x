#import "WeixinIos.h"

@implementation WeixinIos

static WeixinIos* instance=nil;

+(WeixinIos*)shared{
    @synchronized(self) {
        if (instance == nil) {
            instance = [[self alloc] init];
        }
    }
    return instance;
    
}

-(BOOL)handleOpenURL:(NSURL *)url{
    return [WXApi handleOpenURL:url delegate:self];
}
-(void)registerObserver:(WeixinObserver*)observer{
    observer_=observer;
}
-(void)onReq:(BaseReq*)req{
    WeixinReq wxreq;
    
    wxreq.set_type([req type]);
    if ( [req isKindOfClass:[ShowMessageFromWXReq class]]) {
        ShowMessageFromWXReq *shmsg=(ShowMessageFromWXReq*)req;
        WXMediaMessage *msg=[shmsg message];
        NSString *str;
        str=[msg title];
        if (str) wxreq.set_title([str cStringUsingEncoding:NSUTF8StringEncoding ]);
        str=[msg description];
        if (str) wxreq.set_desc([str cStringUsingEncoding:NSUTF8StringEncoding]);
        if ([[msg mediaObject] isKindOfClass:[WXAppExtendObject class]]) {
            WXAppExtendObject *appObj = [msg mediaObject];
            str = [appObj extInfo];
            if (str) wxreq.set_ext([str cStringUsingEncoding:NSUTF8StringEncoding]);
        }
    }

    observer_->onReq(&wxreq);
}
-(void)onResp:(BaseResp*)resp{
    WeixinResp wxresp;
    
    wxresp.set_errcode([resp errCode]);
    wxresp.set_type([resp type]);
    if([resp errStr]) wxresp.set_str([[resp errStr] cStringUsingEncoding:NSUTF8StringEncoding]);
    observer_->onResp(&wxresp);
}
@end