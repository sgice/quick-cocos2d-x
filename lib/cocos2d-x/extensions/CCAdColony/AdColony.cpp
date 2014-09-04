#include <jni.h>
#include <string.h>
#include "jni/JniHelper.h"
#include "CCLuaEngine.h"
#include "CCAdColony.h"

const static char * CLASS_NAME = "org/cocos2dx/lib/CCAdColony";

using namespace cocos2d;
using namespace std;

CCAdColony *CCAdColony::s_instance=NULL;

CCAdColony *CCAdColony::instance(){
    if (s_instance == NULL){
        s_instance = new CCAdColony();
    }
    return s_instance;
}

void CCAdColony::configAd(const char* appid, const char *zoneid){

}
void CCAdColony::showAds(const char *zoneid){
    JniMethodInfo t;
    jstring zid;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showAdcAds", "(Ljava/lang/String;)V")){
        zid = t.env->NewStringUTF(zoneid);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, zid);
        t.env->DeleteLocalRef(zid);
        t.env->DeleteLocalRef(t.classID);
    }
}
int CCAdColony::rewardsAvailable(const char * zoneid){
    JniMethodInfo t;
    jstring zid;
    jint rewards=0;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "AdcRewardsAvailable", "(Ljava/lang/String;)I")){
        zid = t.env->NewStringUTF(zoneid);
        rewards=t.env->CallStaticIntMethod(t.classID, t.methodID, zid);
        t.env->DeleteLocalRef(zid);
        t.env->DeleteLocalRef(t.classID);
    }
    return rewards;
}
void CCAdColony::onReward(int amount, const char *zoneid){
    if (m_observer){
        m_observer->onReward(amount, zoneid);
    }
    if (m_listener){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        
        CCLuaValueDict event;
        event["type"] = CCLuaValue::stringValue("reward");
        event["amount"] = CCLuaValue::intValue(amount);
        event["zoneid"] = CCLuaValue::stringValue(zoneid);
        stack->pushCCLuaValueDict(event);
        stack->executeFunctionByHandler(m_listener, 1);
    }
}
void CCAdColony::onAdStart(const char *zoneid){
    if (m_observer){
        m_observer->onAdStart(zoneid);
    }
    if (m_listener){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        
        CCLuaValueDict event;
        event["type"] = CCLuaValue::stringValue("start");
        event["zoneid"] = CCLuaValue::stringValue(zoneid);
        stack->pushCCLuaValueDict(event);
        stack->executeFunctionByHandler(m_listener, 1);
    }}
void CCAdColony::onAdFinish(bool shown, const char *zoneid){
    if(m_observer){
        m_observer->onAdFinish(shown, zoneid);
    }
    if (m_listener){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        
        CCLuaValueDict event;
        event["type"] = CCLuaValue::stringValue("finish");
        event["zoneid"] = CCLuaValue::stringValue(zoneid);
        stack->pushCCLuaValueDict(event);
        stack->executeFunctionByHandler(m_listener, 1);
    }}

void CCAdColony::registerObserver(CCAdColonyObserver *observer){
    m_observer = observer;
}
CCAdColony::~CCAdColony(){
#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
#endif
}

void CCAdColony::registerListener(cocos2d::LUA_FUNCTION listener){
    if (m_listener)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
}

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCAdColony_onAdStart(JNIEnv*  env, jobject thiz, jstring zoneid){
        string znid = JniHelper::jstring2string(zoneid);
        CCAdColony::instance()->onAdStart(znid.c_str());
    }
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCAdColony_onAdFinish(JNIEnv*  env, jobject thiz, jboolean shown, jstring zoneid){
        string znid = JniHelper::jstring2string(zoneid);
        CCAdColony::instance()->onAdFinish((shown==JNI_TRUE), znid.c_str());
    }
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCAdColony_onReward(JNIEnv*  env, jobject thiz, jint amount, jstring zoneid){
        string znid = JniHelper::jstring2string(zoneid);
        CCAdColony::instance()->onReward(amount, znid.c_str());
    }
}
