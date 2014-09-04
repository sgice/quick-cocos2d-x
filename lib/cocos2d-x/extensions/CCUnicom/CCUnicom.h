#ifndef CC_UNICOM_H
#define CC_UNICOM_H
#include "CCLuaValue.h"

class CCUnicomObserver{
public:
    virtual void onPay(bool success, const char *goodsubid, const char *errstr)=0;
};
class CCUnicom:public CCUnicomObserver
{
public:
    
    ~CCUnicom();
    
    static CCUnicom *instance();
    
    void registerObserver(CCUnicomObserver* observer);
    void registerListener(cocos2d::LUA_FUNCTION listener);

    void paysms( const char * goodname, const char * goodsubid, 
                 const char * costmoney);
    void onPay(bool success, const char *goodsubid, const char *errstr);
    
private:
    CCUnicom():m_listener(0),m_observer(NULL){};
    static CCUnicom *s_instance;
    cocos2d::LUA_FUNCTION m_listener;
    CCUnicomObserver * m_observer;
};

#endif /* CC_UNICOM_H */
