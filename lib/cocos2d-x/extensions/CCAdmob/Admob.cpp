#include <jni.h>
#include <string.h>
#include "jni/JniHelper.h"
#include "CCLuaEngine.h"
#include "CCAdmob.h"

const static char * CLASS_NAME = "org/cocos2dx/lib/CCAdmob";

using namespace cocos2d;
using namespace std;

CCAdmob *CCAdmob::s_instance=NULL;

CCAdmob *CCAdmob::instance(){
    if (s_instance == NULL){
        s_instance = new CCAdmob();
    }
    return s_instance;
}
void CCAdmob::init(const char * admobid, const char * inter_id, int pos){
//not to init here in android 
}
bool CCAdmob::showInter(){
    JniMethodInfo t;
    jboolean shown = JNI_FALSE;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showInter", "()Z")){
        shown = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return shown == JNI_TRUE;
}
void CCAdmob::showBanner(){
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showBanner", "()V")){
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
void CCAdmob::hideBanner(){
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "hideBanner", "()V")){
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}
