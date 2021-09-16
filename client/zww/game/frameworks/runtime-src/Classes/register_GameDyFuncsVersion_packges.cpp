#include "register_GameDyFuncsVersion_packges.h"
#include "extend_package_define_helper.h"

DEF_CHECKCPP2LUASTAICNOCLASS(GameDyfuncsVersion, _getAllFunInfos)
    tolua_pushstring(L, cocos2d::GameDyfuncsVersion::getAllFunInfos().c_str());
    return 1;
DEF_CHECKCPPEND

DEF_CHECKCPP2LUASTAICNOCLASS(GameDyfuncsVersion, _getCppVersion)
    tolua_pushstring(L, cocos2d::GameDyfuncsVersion::getGameCppVersion().c_str());
    return 1;
DEF_CHECKCPPEND

int register_GameDyFunVersion_packges(lua_State* L)
{
    lua_State* tolua_S = L;
    cocos2d::GameDyfuncsVersion::addFunInfo("_getAllFunInfos", "string getAllFunInfos()");
    cocos2d::GameDyfuncsVersion::addFunInfo("_getCppVersion", "string getGameCppVersion()");
    CHECKTOLUAFUNCCALL(GameDyfuncsVersion, _getAllFunInfos);
    CHECKTOLUAFUNCCALL(GameDyfuncsVersion, _getCppVersion);

    return 0;
}
