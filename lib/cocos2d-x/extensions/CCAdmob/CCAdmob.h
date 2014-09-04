#ifndef CC_ADMOB_H
#define CC_ADMOB_H

class CCAdmob
{
public:
    
    ~CCAdmob(){};
    
    const static int TOP=1;
    const static int BOTTOM=2;
    static CCAdmob *instance();
    
    void init(const char * admob_id, const char * inter_id, int pos);
    bool showInter();
    void showBanner();
    void hideBanner();
    
private:
    CCAdmob(){};
    static CCAdmob *s_instance;
};

#endif /* CC_ADMOB_H */
