#include <jni.h>
#include <string.h>
#include "jni/JniHelper.h"
#include "CCLuaEngine.h"
#include "CCUnicom.h"

const static char * CLASS_NAME = "org/cocos2dx/lib/CCUnicom";

using namespace cocos2d;
using namespace std;

CCUnicom *CCUnicom::s_instance=NULL;

CCUnicom *CCUnicom::instance(){
    if (s_instance == NULL){
        s_instance = new CCUnicom();
    }
    return s_instance;
}

void CCUnicom::paysms( const char * goodname, const char * goodsubid, 
                 const char * costmoney){
    JniMethodInfo t;
    jstring gname, gid, cmoney;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "paysms", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")){
        gname = t.env->NewStringUTF(goodname);
        gid = t.env->NewStringUTF(goodsubid);
        cmoney = t.env->NewStringUTF(costmoney);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, gname, gid, cmoney);
        t.env->DeleteLocalRef(gname);
        t.env->DeleteLocalRef(gid);
        t.env->DeleteLocalRef(cmoney);
        t.env->DeleteLocalRef(t.classID);
    }
}
void CCUnicom::onPay(bool success, const char *goodsubid, const char *errstr){
    if (m_observer){
        m_observer->onPay(success, goodsubid, errstr);
    }
    if (m_listener){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        
        CCLuaValueDict event;
        CCLuaValueDict transaction;
        transaction["productIdentifier"]=CCLuaValue::stringValue(goodsubid);
        transaction["quantity"]=CCLuaValue::intValue(1);
        transaction["state"]=success?CCLuaValue::stringValue("purchased"):CCLuaValue::stringValue("failed");
        transaction["errstr"] = CCLuaValue::stringValue(errstr);
        
        event["transaction"] = CCLuaValue::dictValue(transaction);
        stack->pushCCLuaValueDict(event);
        stack->executeFunctionByHandler(m_listener, 1);
    }
}

void CCUnicom::registerObserver(CCUnicomObserver *observer){
    m_observer = observer;
}
CCUnicom::~CCUnicom(){
#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
#endif
}

void CCUnicom::registerListener(cocos2d::LUA_FUNCTION listener){
    if (m_listener)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
}

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCUnicom_onSMSresult(JNIEnv*  env, jobject thiz, jboolean success, jstring goodsubid, jstring errstr){
        string gsid = JniHelper::jstring2string(goodsubid);
        string estr = JniHelper::jstring2string(errstr);
        CCUnicom::instance()->onPay((success==JNI_TRUE), gsid.c_str(), estr.c_str() );
    }
}
