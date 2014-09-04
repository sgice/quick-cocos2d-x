#ifndef COCOS_CHARTBOOST_H
#define COCOS_CHARTBOOST_H

class CCChartboost
{
public:

    ~CCChartboost(){};
    
    static CCChartboost *instance();

    void startSession(const char* appid, const char *signature);
    bool showAds();
    void showMoreApp();

private:
    CCChartboost(){};
    static CCChartboost *s_instance;
};

#endif /* COCOS_CHARTBOOST_H */
