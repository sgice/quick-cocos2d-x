#include <jni.h>
#include <string.h>
#include "jni/JniHelper.h"
#include "CCChartboost.h"

using namespace cocos2d;
static const char * CLASS_NAME="org/cocos2dx/lib/CCChartboost";
CCChartboost *CCChartboost::s_instance = NULL;

CCChartboost * CCChartboost::instance()
{
    if (s_instance == NULL){
        s_instance = new CCChartboost();
    }
    return s_instance;
}

void CCChartboost::startSession(const char* appid, const char *signature)
{
}
bool CCChartboost::showAds()
{
    JniMethodInfo t;
    jboolean shown = JNI_FALSE;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showCBAds", "()Z")){
        shown = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    return shown == JNI_TRUE;
}
void CCChartboost::showMoreApp()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showCBMoreApp", "()V")){
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

