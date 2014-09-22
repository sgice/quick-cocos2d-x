#import <AdColony/AdColony.h>
#import "CCTelcom.h"
#include "CCLuaEngine.h"
using namespace cocos2d;

CCTelcom *CCTelcom::s_instance=NULL;

CCTelcom *CCTelcom::instance(){
    if (s_instance == NULL){
        s_instance = new CCTelcom();
    }
    return s_instance;
}

void CCTelcom::onPay(bool success, const char *goodsubid){
}
void CCTelcom::paysms( const char * stext, const char * goodsubid, const char * orderid){

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
        CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_listener);
    }
    m_listener = listener;
}
