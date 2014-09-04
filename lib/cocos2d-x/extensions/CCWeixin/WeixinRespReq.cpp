#include "CCWeixin.h"

void WeixinResp::set_str(const char *str){
    errstr=std::string(str);
}
WeixinResp::~WeixinResp(){
}
WeixinReq::~WeixinReq(){
}
void WeixinReq::set_desc(const char *des){
    desc = std::string(des);
}
void WeixinReq::set_ext(const char *ex){
    ext = std::string(ex);
}
void WeixinReq::set_title(const char *tit){
    title = std::string(tit);
}
void WeixinReq::set_type(int t){
    type = t;
}
#if CC_LUA_ENGINE_ENABLED > 0
const cocos2d::CCLuaValueDict WeixinResp::convertToLuaTable(void){
    CCLuaValueDict resp_;
    
    resp_["errtype"] = CCLuaValue::intValue(errtype);
    resp_["errcode"] = CCLuaValue::intValue(errcode);
    resp_["errstr"] = CCLuaValue::stringValue(errstr);
    return resp_;
}
const cocos2d::CCLuaValueDict WeixinReq::convertToLuaTable(void){
    CCLuaValueDict req_;
    
    req_["type"] = CCLuaValue::intValue(type);
    req_["desc"] = CCLuaValue::stringValue(desc);
    req_["title"] = CCLuaValue::stringValue(title);
    req_["ext"] = CCLuaValue::stringValue(ext);
    return req_;
}

#endif
