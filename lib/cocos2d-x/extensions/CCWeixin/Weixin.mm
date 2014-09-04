#include "CCWeixin.h"
#include "WeixinIos.h"
#include "CCLuaEngine.h"

using namespace cocos2d;


CCWeixin *CCWeixin::s_instance=NULL;

CCWeixin *CCWeixin::instance(){
    if (s_instance == NULL) {
        s_instance=new CCWeixin();
        [[WeixinIos shared] registerObserver:s_instance];
    }
    return s_instance;
}
CCWeixin::~CCWeixin(){
#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
#endif

}

#if CC_LUA_ENGINE_ENABLED > 0
void CCWeixin::passWeixinRespToLuaListener(WeixinResp* wxresp)
{
    CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
    
    CCLuaValueDict event;
    event["wxresp"] = CCLuaValue::dictValue(wxresp->convertToLuaTable());
    
    stack->pushCCLuaValueDict(event);
    stack->executeFunctionByHandler(m_listener, 1);
}
void CCWeixin::passWeixinReqToLuaListener(WeixinReq* wxreq)
{
    CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
    
    CCLuaValueDict event;
    event["wxreq"] = CCLuaValue::dictValue(wxreq->convertToLuaTable());
    
    stack->pushCCLuaValueDict(event);
    stack->executeFunctionByHandler(m_listener, 1);
}
void CCWeixin::registerListener(cocos2d::LUA_FUNCTION listener){
    if (m_listener)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
}
#endif

void CCWeixin::registerObserver(WeixinObserver *observer){
    m_observer = observer;
}
void CCWeixin::onResp(WeixinResp *wxresp){
    if (m_observer) m_observer->onResp(wxresp);
    if (m_listener) passWeixinRespToLuaListener(wxresp);
}
void CCWeixin::onReq(WeixinReq *wxreq){
    if (m_observer) m_observer->onReq(wxreq);
    if (m_listener) passWeixinReqToLuaListener(wxreq);
}
void CCWeixin::regApp(const char * wx_app_id){
    [WXApi registerApp:[NSString stringWithUTF8String:wx_app_id]];
}

bool CCWeixin::isWeixinAvailable(){
    return [WXApi isWXAppSupportApi];
}

void CCWeixin::SendText(const char * text_msg){
    TextMsg(text_msg, FRIENDS);
}
void CCWeixin::PostText(const char *text_msg){
    TextMsg(text_msg, TIMELINE);
}
void CCWeixin::TextMsg(const char * text_msg, int dest){
	SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    req.text = [ [NSString alloc] initWithUTF8String:text_msg ];
    req.bText = true;
    
    if (dest == FRIENDS){
       req.scene=WXSceneSession;
    }else if (dest == TIMELINE){
        req.scene=WXSceneTimeline;
    }
    [WXApi sendReq:req];
}
void CCWeixin::SendUrl(const char * text, const char * title, const char *url, const char *thumbfile){
    UrlMsg(text, title, url, thumbfile, FRIENDS);
}
void CCWeixin::PostUrl(const char * text, const char * title, const char *url, const char *thumbfile){
    UrlMsg(text, title, url, thumbfile, TIMELINE);
}
void CCWeixin::UrlMsg(const char * text, const char * title, const char *url, const char *thumbfile, int dest){
	SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    WXMediaMessage *message = [WXMediaMessage message];
    
	NSString* wxtext = [[ NSString alloc ] initWithUTF8String:text ];
	NSString* wxtitle = [[ NSString alloc ] initWithUTF8String:title];
	NSString* wxthumbfile = [[ NSString alloc ] initWithUTF8String:thumbfile ];
	NSString* wxurl = [[ NSString alloc ] initWithUTF8String:url ];
    
    req.bText=false;
    req.message=message;
    message.title = wxtitle;
    message.description = wxtext;
    [message setThumbImage:[UIImage imageWithContentsOfFile:wxthumbfile]];
    WXWebpageObject *url_ext=[WXWebpageObject object];
    url_ext.webpageUrl=wxurl;
    message.mediaObject=url_ext;
    if (dest == FRIENDS){
        req.scene=WXSceneSession;
    }else if (dest == TIMELINE){
        req.scene=WXSceneTimeline;
    }
    [WXApi sendReq:req];
}

void CCWeixin::SendMusic(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile){
    MusicMsg(text, title, url, data_url, thumbfile, FRIENDS);
}
void CCWeixin::PostMusic(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile){
    MusicMsg(text, title, url, data_url, thumbfile, TIMELINE);
}
void CCWeixin::MusicMsg(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile, int dest){
	SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    WXMediaMessage *message = [WXMediaMessage message];

	NSString* wxtext = [[ NSString alloc ] initWithUTF8String:text ];
	NSString* wxtitle = [[ NSString alloc ] initWithUTF8String:title];
	NSString* wxthumbfile = [[ NSString alloc ] initWithUTF8String:thumbfile ];
	NSString* wxurl = [[ NSString alloc ] initWithUTF8String:url ];
    NSString* wxdataurl=[[NSString alloc] initWithUTF8String:data_url];
    
    req.bText=false;
    req.message=message;
    message.title = wxtitle;
    message.description = wxtext;
    [message setThumbImage:[UIImage imageWithContentsOfFile:wxthumbfile]];
    WXMusicObject *music_ext=[WXMusicObject object];
    music_ext.musicDataUrl=wxdataurl;
    music_ext.musicUrl=wxurl;
    message.mediaObject=music_ext;
    if (dest == FRIENDS){
        req.scene=WXSceneSession;
    }else if (dest == TIMELINE){
        req.scene=WXSceneTimeline;
    }
    [WXApi sendReq:req];
    
}

void CCWeixin::SendImage(const char * text, const char * title, const char * imagefile, const char * thumbfile){
    ImageMsg(text, title, imagefile, thumbfile, FRIENDS);
}
void CCWeixin::PostImage(const char * text, const char * title, const char * imagefile, const char * thumbfile){
    ImageMsg(text, title, imagefile, thumbfile, TIMELINE);
}
void CCWeixin::ImageMsg(const char * text, const char * title, const char * imagefile, const char * thumbfile, int dest){
	SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    WXMediaMessage *message = [WXMediaMessage message];
    
	NSString* wxtext = [[ NSString alloc ] initWithUTF8String:text ];
	NSString* wxtitle = [[ NSString alloc ] initWithUTF8String:title];
	NSString* wxthumbfile = [[ NSString alloc ] initWithUTF8String:thumbfile ];
	NSString* wximagefile = [[ NSString alloc ] initWithUTF8String:imagefile ];
    
    req.bText=false;
    req.message=message;
    message.title = wxtitle;
    message.description = wxtext;
    [message setThumbImage:[UIImage imageWithContentsOfFile:wxthumbfile]];
    WXImageObject *image_ext=[WXImageObject object];
    image_ext.imageData=[NSData dataWithContentsOfFile:wximagefile];
    message.mediaObject=image_ext;
    if (dest == FRIENDS){
        req.scene=WXSceneSession;
    }else if (dest == TIMELINE){
        req.scene=WXSceneTimeline;
    }
    [WXApi sendReq:req];
}

void CCWeixin::SendVideo(const char * text, const char * title, const char * videofile,  const char * thumbfile){
    VideoMsg(text, title, videofile, thumbfile, FRIENDS);
}
void CCWeixin::PostVideo(const char * text, const char * title, const char * videofile,  const char * thumbfile){
    VideoMsg(text, title, videofile, thumbfile, TIMELINE);
}
void CCWeixin::VideoMsg(const char * text, const char * title, const char * videofile,  const char * thumbfile, int dest){
	SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    WXMediaMessage *message = [WXMediaMessage message];
    
	NSString* wxtext = [[ NSString alloc ] initWithUTF8String:text ];
	NSString* wxtitle = [[ NSString alloc ] initWithUTF8String:title];
	NSString* wxthumbfile = [[ NSString alloc ] initWithUTF8String:thumbfile ];
	NSString* wxvideofile = [[ NSString alloc ] initWithUTF8String:videofile ];
    
    req.bText=false;
    req.message=message;
    message.title = wxtitle;
    message.description = wxtext;
    [message setThumbImage:[UIImage imageWithContentsOfFile:wxthumbfile]];
    WXVideoObject *video_ext=[WXVideoObject object];
    video_ext.videoUrl=wxvideofile;
    message.mediaObject=video_ext;
    if (dest == FRIENDS){
        req.scene=WXSceneSession;
    }else if (dest == TIMELINE){
        req.scene=WXSceneTimeline;
    }
    [WXApi sendReq:req];
}

void CCWeixin::SendApp(const char *text, const char * title, const char * custom_info, const char * thumbfile){
    AppMsg(text, title, custom_info, thumbfile, FRIENDS);
}
void CCWeixin::PostApp(const char *text, const char * title, const char * custom_info, const char * thumbfile){
    AppMsg(text, title, custom_info, thumbfile, TIMELINE);
}
void CCWeixin::AppMsg(const char *text, const char * title, const char * custom_info, const char * thumbfile, int dest){
	SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init]autorelease];
    WXMediaMessage *message = [WXMediaMessage message];
    
	NSString* wxtext = [[ NSString alloc ] initWithUTF8String:text ];
	NSString* wxtitle = [[ NSString alloc ] initWithUTF8String:title];
	NSString* wxthumbfile = [[ NSString alloc ] initWithUTF8String:thumbfile ];
	NSString* wxappinfo = [[ NSString alloc ] initWithUTF8String:custom_info ];
    
    req.bText=false;
    req.message=message;
    message.title = wxtitle;
    message.description = wxtext;
    [message setThumbImage:[UIImage imageWithContentsOfFile:wxthumbfile]];
    WXAppExtendObject *app_ext=[WXAppExtendObject object];
    app_ext.extInfo=wxappinfo;
    message.mediaObject=app_ext;
    if (dest == FRIENDS){
        req.scene=WXSceneSession;
    }else if (dest == TIMELINE){
        req.scene=WXSceneTimeline;
    }
    [WXApi sendReq:req];
}
