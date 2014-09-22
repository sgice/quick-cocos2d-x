#ifndef CC_TELCOM_H
#define CC_TELCOM_H
#include "CCLuaValue.h"

class CCTelcomObserver{
public:
    virtual void onPay(bool success, const char *goodid)=0;
};
class CCTelcom:public CCTelcomObserver
{
public:
    
    ~CCTelcom();
    
    static CCTelcom *instance();
    
    void registerObserver(CCTelcomObserver* observer);
    void registerListener(cocos2d::LUA_FUNCTION listener);

    void paysms( const char * stext, const char * goodsubid, const char *oderid);
    void onPay(bool success, const char *goodsubid);
    
private:
    CCTelcom():m_listener(0),m_observer(NULL){};
    static CCTelcom *s_instance;
    cocos2d::LUA_FUNCTION m_listener;
    CCTelcomObserver * m_observer;
};

#endif /* CC_TELCOM_H */
