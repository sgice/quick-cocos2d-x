#include <jni.h>
#include <string.h>
#include "jni/JniHelper.h"
#include "CCLuaEngine.h"
#include "CCTelcom.h"

const static char * CLASS_NAME = "org/cocos2dx/lib/CCTelcom";

using namespace cocos2d;
using namespace std;

CCTelcom *CCTelcom::s_instance=NULL;

CCTelcom *CCTelcom::instance(){
    if (s_instance == NULL){
        s_instance = new CCTelcom();
    }
    return s_instance;
}

void CCTelcom::paysms( const char * stext, const char * goodsubid, const char *orderid){
    JniMethodInfo t;
    jstring txt, gid, oid;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "paysms", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")){
        txt = t.env->NewStringUTF(stext);
        gid = t.env->NewStringUTF(goodsubid);
        oid = t.env->NewStringUTF(orderid);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, txt, gid, oid);
        t.env->DeleteLocalRef(txt);
        t.env->DeleteLocalRef(gid);
        t.env->DeleteLocalRef(oid);
        t.env->DeleteLocalRef(t.classID);
    }
}
void CCTelcom::onPay(bool success, const char *goodsubid){
    if (m_observer){
        m_observer->onPay(success, goodsubid);
    }
    if (m_listener){
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        
        CCLuaValueDict event;
        CCLuaValueDict transaction;
        transaction["productIdentifier"]=CCLuaValue::stringValue(goodsubid);
        transaction["quantity"]=CCLuaValue::intValue(1);
        transaction["state"]=success?CCLuaValue::stringValue("purchased"):CCLuaValue::stringValue("failed");
        
        event["transaction"] = CCLuaValue::dictValue(transaction);
        stack->pushCCLuaValueDict(event);
        stack->executeFunctionByHandler(m_listener, 1);
    }
}

void CCTelcom::registerObserver(CCTelcomObserver *observer){
    m_observer = observer;
}
CCTelcom::~CCTelcom(){
#if CC_LUA_ENGINE_ENABLED > 0
    if (m_listener)
    {
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
#endif
}

void CCTelcom::registerListener(cocos2d::LUA_FUNCTION listener){
    if (m_listener)
    {
        printf("remove old listener %d\n", m_listener);
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
    printf("add listener %d\n", listener);
}

extern "C" {
    JNIEXPORT void JNICALL Java_org_cocos2dx_lib_CCTelcom_onSMSresult(JNIEnv*  env, jobject thiz, jboolean success, jstring goodsubid){
        string gsid = JniHelper::jstring2string(goodsubid);
        CCTelcom::instance()->onPay((success==JNI_TRUE), gsid.c_str() );
    }
}
