#include "register_GameDyFuncsVersion_packges.h"
#include "extend_package_define_helper.h"
#include <LuaBasicConversions.h>
extern "C" {
    #include "lua.h"
    #include "tolua++.h"
}
DEF_CHECKCPP2LUASTAICNOCLASS(GameDyfuncsVersion, _getAllFunInfos)
    tolua_pushstring(L, cocos2d::GameDyfuncsVersion::getAllFunInfos().c_str());
    return 1;
DEF_CHECKCPPEND

DEF_CHECKCPP2LUASTAICNOCLASS(GameDyfuncsVersion, _getCppVersion)
    tolua_pushstring(L, cocos2d::GameDyfuncsVersion::getGameCppVersion().c_str());
    return 1;
DEF_CHECKCPPEND

DEF_CHECKCPP2LUASTAICNOCLASS(GameDyfuncsVersion, getArgvLen)
        int len = cocos2d::GameDyfuncsVersion::getArgvLen();
    tolua_pushnumber(L, len);
    return 1;
DEF_CHECKCPPEND

DEF_CHECKCPP2LUASTAICNOCLASS(GameDyfuncsVersion, getArgvByIdx)
    //int argc = lua_gettop(L) - 1;
    int argc = 1;
    if (argc == 1) {
        unsigned int idx = tolua_tonumber(L, 2, 0);
        tolua_pushstring(L, cocos2d::GameDyfuncsVersion::getArgvByIdx(idx).c_str());
        return 1;
    }    
DEF_CHECKCPPEND

int register_GameDyFunVersion_packges(lua_State* L)
{
    lua_State* tolua_S = L;
    cocos2d::GameDyfuncsVersion::addFunInfo("_getAllFunInfos", "string getAllFunInfos()");
    cocos2d::GameDyfuncsVersion::addFunInfo("_getCppVersion", "string getGameCppVersion()");
    cocos2d::GameDyfuncsVersion::addFunInfo("getArgvLen", "string getArgvLen()");
    cocos2d::GameDyfuncsVersion::addFunInfo("getArgvByIdx", "string getArgvByIdx(unsigned int idx)");
    CHECKTOLUAFUNCCALL(GameDyfuncsVersion, _getAllFunInfos);
    CHECKTOLUAFUNCCALL(GameDyfuncsVersion, _getCppVersion);
    CHECKTOLUAFUNCCALL(GameDyfuncsVersion, getArgvLen);
    CHECKTOLUAFUNCCALL(GameDyfuncsVersion, getArgvByIdx);

    return 0;
}
