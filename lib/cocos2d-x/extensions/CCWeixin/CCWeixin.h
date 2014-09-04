#ifndef WEIXIN_H
#define WEIXIN_H

#include "CCLuaValue.h"
using namespace cocos2d;

class WeixinResp{
public:
    WeixinResp():errcode(0),errtype(0){};
    ~WeixinResp();
    void set_errcode(int code){errcode=code;};
    void set_type(int type){errtype=type;};
    void set_str(const char* str);
    int get_errcode(){return errcode;};
    int get_errtype(){return errtype;};
    std::string get_errstr(){return errstr;};
#if CC_LUA_ENGINE_ENABLED > 0
    const cocos2d::CCLuaValueDict convertToLuaTable(void);
#endif
private:
    int errcode;
    std::string errstr;
    int errtype;
};
class WeixinReq{
public:
    WeixinReq(){};
    ~WeixinReq();
    int get_type(){return type;};
    std::string get_desc(){return desc;};
    std::string get_title(){return title;};
    std::string get_ext(){return ext;};
    void set_desc(const char *des);
    void set_title(const char *tit);
    void set_ext(const char *ex);
    void set_type(int t);
#if CC_LUA_ENGINE_ENABLED > 0
    const cocos2d::CCLuaValueDict convertToLuaTable(void);
#endif
private:
    int type;
    std::string desc;
    std::string title;
    std::string ext;
};
class WeixinObserver{
public:
    virtual void onReq(WeixinReq *)=0;
    virtual void onResp(WeixinResp *)=0;
};

class CCWeixin:public WeixinObserver
{
public:
    static CCWeixin *instance();
    const static int TIMELINE=1;
    const static int FRIENDS=2;
    const static int FAVORITE=3;
    
    void regApp(const char * wx_app_id );

    bool isWeixinAvailable();

    void SendText(const char * text_msg);
    void PostText(const char * text_msg);
    
    void SendUrl(const char * text, const char * title, const char *url, const char *thumbfile);
    void PostUrl(const char * text, const char * title, const char *url, const char *thumbfile);

    void SendMusic(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile);
    void PostMusic(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile);

    void SendImage(const char * text, const char * title, const char * imagefile,  const char * thumbfile);
    void PostImage(const char * text, const char * title, const char * imagefile,  const char * thumbfile);

    void SendVideo(const char * text, const char * title, const char * videofile,  const char * thumbfile);
    void PostVideo(const char * text, const char * title, const char * videofile,  const char * thumbfile);
    
    void SendApp(const char *text, const char * title, const char * custom_info, const char * thumbfile);
    void PostApp(const char *text, const char * title, const char * custom_info, const char * thumbfile);

    void registerObserver(WeixinObserver* observer);
    void registerListener(cocos2d::LUA_FUNCTION listener);
    
    virtual void onReq(WeixinReq *wxreq);
    virtual void onResp(WeixinResp *wxresp);
    
private:
    static CCWeixin* s_instance;
    WeixinObserver* m_observer;
    cocos2d::LUA_FUNCTION       m_listener;
    
    CCWeixin():m_observer(NULL),m_listener(0){};
    ~CCWeixin();
    void TextMsg(const char* text_msg, int dest);
    void UrlMsg(const char * text, const char * title, const char *url, const char *thumbfile, int dest);
    void MusicMsg(const char * text, const char * title, const char * url, const char * data_url, const char * thumbfile, int dest);
    void ImageMsg(const char * text, const char * title, const char * imagefile, const char * thumbfile, int dest);
    void VideoMsg(const char * text, const char * title, const char * videofile,  const char * thumbfile, int dest);
    void AppMsg(const char *text, const char * title, const char * custom_info, const char * thumbfile, int dest);
    void passWeixinRespToLuaListener(WeixinResp* wxresp);
    void passWeixinReqToLuaListener(WeixinReq* wxreq);
};

#endif 
