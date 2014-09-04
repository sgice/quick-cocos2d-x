#ifndef CC_ADCOLONY_H
#define CC_ADCOLONY_H
#include "CCLuaValue.h"

class CCAdColonyObserver{
public:
    virtual void onReward(int amount, const char *zoneid)=0;
    virtual void onAdStart(const char *zoneid)=0;
    virtual void onAdFinish(bool shown, const char *zoneid)=0;
};
class CCAdColony:public CCAdColonyObserver
{
public:
    
    ~CCAdColony();
    
    static CCAdColony *instance();
    
    void configAd(const char* appid, const char *zoneid);
    void showAds(const char *zoneid);
    int rewardsAvailable(const char * zoneid);
    void onReward(int amount, const char *zoneid);
    void onAdStart(const char *zoneid);
    void onAdFinish(bool shown, const char *zoneid);
    
    void registerObserver(CCAdColonyObserver* observer);
    void registerListener(cocos2d::LUA_FUNCTION listener);
    
private:
    CCAdColony():m_listener(0),m_observer(NULL){};
    static CCAdColony *s_instance;
    cocos2d::LUA_FUNCTION m_listener;
    CCAdColonyObserver * m_observer;
};

#endif /* CC_ADCOLONY_H */
