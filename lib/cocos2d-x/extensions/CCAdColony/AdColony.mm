#import <AdColony/AdColony.h>
#import "CCAdColony.h"
#import "AdColonyIOSDelegate.h"
#include "CCLuaEngine.h"
using namespace cocos2d;

CCAdColony *CCAdColony::s_instance=NULL;
AdColonyIOSDelegate *s_delegate=NULL;

CCAdColony *CCAdColony::instance(){
    if (s_instance == NULL){
        s_instance = new CCAdColony();
        s_delegate = [[[AdColonyIOSDelegate alloc]init] autorelease];
        [s_delegate registerObserver:s_instance];
    }
    return s_instance;
}

void CCAdColony::configAd(const char* appid, const char *zoneid){
    [AdColony configureWithAppID: [NSString stringWithUTF8String:appid]
                         zoneIDs: [NSArray arrayWithObjects:[NSString stringWithUTF8String:zoneid], Nil]
                         delegate:s_delegate
                         logging:false ];

}
void CCAdColony::showAds(const char *zoneid){
    [AdColony playVideoAdForZone:[NSString stringWithUTF8String:zoneid] withDelegate:s_delegate];
}
int CCAdColony::rewardsAvailable(const char * zoneid){
    return [AdColony getVirtualCurrencyRewardsAvailableTodayForZone:[NSString stringWithUTF8String:zoneid]];
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
