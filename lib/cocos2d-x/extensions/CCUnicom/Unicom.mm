#import "CCUnicom.h"
#include "CCLuaEngine.h"
using namespace cocos2d;

CCUnicom *CCUnicom::s_instance=NULL;

CCUnicom *CCUnicom::instance(){
    if (s_instance == NULL){
        s_instance = new CCUnicom();
    }
    return s_instance;
}

void CCUnicom::onPay(bool success, const char *goodsubid, const char *errstr){
}
void CCUnicom::paysms( const char * goodname, const char * goodsubid,
                           const char * costmoney){

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
