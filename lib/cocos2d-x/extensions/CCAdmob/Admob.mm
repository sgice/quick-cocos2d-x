#import "CCAdmob.h"
#import "CCAdmobIos.h"

CCAdmob *CCAdmob::s_instance=NULL;

CCAdmob *CCAdmob::instance(){
    if (s_instance == NULL){
        s_instance = new CCAdmob();
    }
    return s_instance;
}
void CCAdmob::init(const char * admob_id, const char * inter_id, int pos){
    [[CCAdmobIos shared ]init:[NSString stringWithUTF8String:admob_id] interstitial:[NSString stringWithUTF8String:inter_id] position:pos];
}
bool CCAdmob::showInter(){
    return [[CCAdmobIos shared] showInter];
}
void CCAdmob::showBanner(){
    [[CCAdmobIos shared] showBanner];
}
void CCAdmob::hideBanner(){
    [[CCAdmobIos shared] hideBanner];
}
