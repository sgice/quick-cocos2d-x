#include <jni.h>
#include <string.h>
#include "jni/JniHelper.h"
#include "CCLuaEngine.h"
#include "CCWeixin.h"

const static char * CLASS_NAME = "org/cocos2dx/lib/CCWeixin";

using namespace cocos2d;
using namespace std;

CCWeixin *CCWeixin::s_instance=NULL;

CCWeixin *CCWeixin::instance(){
    if (s_instance == NULL) {
        s_instance=new CCWeixin();
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
    JniMethodInfo t;
    jstring appid;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "regApp", "(Ljava/lang/String;)V")){
        appid = t.env->NewStringUTF(wx_app_id);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, appid);
        t.env->DeleteLocalRef(appid);
        t.env->DeleteLocalRef(t.classID);
    }
}

bool CCWeixin::isWeixinAvailable(){
    JniMethodInfo t;
    jboolean wxAvail = JNI_FALSE;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "wxAvail", "()Z")){
        wxAvail=t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return wxAvail==JNI_TRUE;
}

void CCWeixin::SendText(const char * text_msg){
    TextMsg(text_msg, FRIENDS);
}
void CCWeixin::PostText(const char *text_msg){
    TextMsg(text_msg, TIMELINE);
}
void CCWeixin::TextMsg(const char * text_msg, int dest){
    JniMethodInfo t;
    jstring text;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "TextMsg", "(Ljava/lang/String;I)V")){
        text = t.env->NewStringUTF(text_msg);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, text, dest);
        t.env->DeleteLocalRef(text);
        t.env->DeleteLocalRef(t.classID);
    }
}
void CCWeixin::SendUrl(const char * text, const char * title, const char *url, const char *thumbfile){
    UrlMsg(text, title, url, thumbfile, FRIENDS);
}
void CCWeixin::PostUrl(const char * text, const char * title, const char *url, const char *thumbfile){
    UrlMsg(text, title, url, thumbfile, TIMELINE);
}
void CCWeixin::UrlMsg(const char * text, const char * title, const char *url, const char *thumbfile, int dest){
    JniMethodInfo t;
    jstring j_text, j_title, j_url, j_thumb;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "UrlMsg", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")){
        j_text = t.env->NewStringUTF(text);
        j_title = t.env->NewStringUTF(title);
        j_url = t.env->NewStringUTF(url);
        j_thumb = t.env->NewStringUTF(thumbfile);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, j_text, j_title, j_url, j_thumb, dest);
        t.env->DeleteLocalRef(j_text);
        t.env->DeleteLocalRef(j_title);
        t.env->DeleteLocalRef(j_url);
        t.env->DeleteLocalRef(j_thumb);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CCWeixin::SendMusic(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile){
    MusicMsg(text, title, url, data_url, thumbfile, FRIENDS);
}
void CCWeixin::PostMusic(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile){
    MusicMsg(text, title, url, data_url, thumbfile, TIMELINE);
}
void CCWeixin::MusicMsg(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile, int dest){
    JniMethodInfo t;
    jstring j_text, j_title, j_url, j_data, j_thumb;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "MusicMsg", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")){
        j_text = t.env->NewStringUTF(text);
        j_title = t.env->NewStringUTF(title);
        j_url = t.env->NewStringUTF(url);
        j_data = t.env->NewStringUTF(data_url);
        j_thumb = t.env->NewStringUTF(thumbfile);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, j_text, j_title, j_url, j_data, j_thumb, dest);
        t.env->DeleteLocalRef(j_text);
        t.env->DeleteLocalRef(j_title);
        t.env->DeleteLocalRef(j_url);
        t.env->DeleteLocalRef(j_data);
        t.env->DeleteLocalRef(j_thumb);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CCWeixin::SendImage(const char * text, const char * title, const char * imagefile, const char * thumbfile){
    ImageMsg(text, title, imagefile, thumbfile, FRIENDS);
}
void CCWeixin::PostImage(const char * text, const char * title, const char * imagefile, const char * thumbfile){
    ImageMsg(text, title, imagefile, thumbfile, TIMELINE);
}
void CCWeixin::ImageMsg(const char * text, const char * title, const char * imagefile, const char * thumbfile, int dest){
    JniMethodInfo t;
    jstring j_text, j_title, j_image, j_thumb;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "ImageMsg", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")){
        j_text = t.env->NewStringUTF(text);
        j_title = t.env->NewStringUTF(title);
        j_image = t.env->NewStringUTF(imagefile);
        j_thumb = t.env->NewStringUTF(thumbfile);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, j_text, j_title, j_image, j_thumb, dest);
        t.env->DeleteLocalRef(j_text);
        t.env->DeleteLocalRef(j_title);
        t.env->DeleteLocalRef(j_image);
        t.env->DeleteLocalRef(j_thumb);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CCWeixin::SendVideo(const char * text, const char * title, const char * videofile,  const char * thumbfile){
    VideoMsg(text, title, videofile, thumbfile, FRIENDS);
}
void CCWeixin::PostVideo(const char * text, const char * title, const char * videofile,  const char * thumbfile){
    VideoMsg(text, title, videofile, thumbfile, TIMELINE);
}
void CCWeixin::VideoMsg(const char * text, const char * title, const char * videofile,  const char * thumbfile, int dest){
    JniMethodInfo t;
    jstring j_text, j_title, j_video, j_thumb;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "VideoMsg", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")){
        j_text = t.env->NewStringUTF(text);
        j_title = t.env->NewStringUTF(title);
        j_video = t.env->NewStringUTF(videofile);
        j_thumb = t.env->NewStringUTF(thumbfile);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, j_text, j_title, j_video, j_thumb, dest);
        t.env->DeleteLocalRef(j_text);
        t.env->DeleteLocalRef(j_title);
        t.env->DeleteLocalRef(j_video);
        t.env->DeleteLocalRef(j_thumb);
        t.env->DeleteLocalRef(t.classID);
    }
}

void CCWeixin::SendApp(const char *text, const char * title, const char * custom_info, const char * thumbfile){
    AppMsg(text, title, custom_info, thumbfile, FRIENDS);
}
void CCWeixin::PostApp(const char *text, const char * title, const char * custom_info, const char * thumbfile){
    AppMsg(text, title, custom_info, thumbfile, TIMELINE);
}
void CCWeixin::AppMsg(const char *text, const char * title, const char * custom_info, const char * thumbfile, int dest){
    JniMethodInfo t;
    jstring j_text, j_title, j_info, j_thumb;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "AppMsg", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V")){
        j_text = t.env->NewStringUTF(text);
        j_title = t.env->NewStringUTF(title);
        j_info = t.env->NewStringUTF(custom_info);
        j_thumb = t.env->NewStringUTF(thumbfile);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, j_text, j_title, j_info, j_thumb, dest);
        t.env->DeleteLocalRef(j_text);
        t.env->DeleteLocalRef(j_title);
        t.env->DeleteLocalRef(j_info);
        t.env->DeleteLocalRef(j_thumb);
        t.env->DeleteLocalRef(t.classID);
    }
}

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCWeixin_onRespJNI(JNIEnv*  env, jobject thiz, jint type, jint code, jstring str){
        WeixinResp resp;
        resp.set_type(type);
        resp.set_errcode(code);
        resp.set_str(JniHelper::jstring2string(str).c_str());
        CCWeixin::instance()->onResp(&resp);
    }
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCWeixin_onReqJNI(JNIEnv* env, jobject thiz, jint type, jstring desc, jstring title, jstring ext){
        WeixinReq req;
        req.set_type(type);
        req.set_desc(JniHelper::jstring2string(desc).c_str());
        req.set_title(JniHelper::jstring2string(title).c_str());
        req.set_ext(JniHelper::jstring2string(ext).c_str());
        CCWeixin::instance()->onReq(&req);
    }
}
