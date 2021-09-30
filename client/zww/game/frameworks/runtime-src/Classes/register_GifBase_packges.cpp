#include "gif/GifBase.h"
#include "extend_package_define_helper.h"
#include "base/CCGameDyFuncsVersion.h"
#include "2d/CCNode.h"
#include "gif/InstantGif.h"
#include "gif/CacheGif.h"
#include <LuaBasicConversions.h>
extern "C" {
    #include "lua.h"
    #include "tolua++.h"
}
extern std::unordered_map<std::string, std::string>  g_luaType;
extern std::unordered_map<std::string, std::string>  g_typeCast;

USING_NS_CC;
DEF_CHECKCPP2LUASTAIC2OBJCLASS(GifBase, create, "CheckCpp.gifbase")
    argc =lua_gettop(L) - 1;
    bool ok = true;
    if (argc == 2) {
        std::string path = "";
        bool isCache = false;
        ok &= luaval_to_std_string(tolua_S, 2, &path, "CheckCpp.gifbase:create");
        ok &= luaval_to_boolean(tolua_S, 3, &isCache, "CheckCpp.gifbase:create");
        if (ok == false) {
            return 0;
        }
        if (isCache) {
            cobj = CacheGif::create(path.c_str());
        }
        else {
            cobj = InstantGif::create(path.c_str());
        }
        object_to_luaval<GifBase>(tolua_S, "CheckCpp.gifbase", cobj);
        return 1;
    }
    DEF_CHECKCPP2LUASTAIGOTOERR(GifBase, create, "cc.Label")
DEF_CHECKCPPEND

DEF_CHECKCPP2LUASTAICOBJCLASS(GifBase, getSize, "CheckCpp.gifbase")
argc = lua_gettop(L) - 1;
    bool ok = true;
    if (cobj != NULL) {
        cocos2d::Size size = cobj->getSize();
        size_to_luaval(tolua_S, size);
        return 1;
    }
    DEF_CHECKCPP2LUASTAIGOTOERR(GifBase, getSize, "cc.Label")
DEF_CHECKCPPEND
int  register_Gifbase_packges(lua_State* L)
{
    lua_State* tolua_S = L;

    tolua_usertype(L, "CheckCpp.gifbase");
    tolua_cclass(L, "gifbase","CheckCpp.gifbase", "cc.Node",nullptr);
    tolua_beginmodule(L, "gifbase");
    GameDyfuncsVersion::addFunInfo("create", "gifbase::create(string)");
    GameDyfuncsVersion::addFunInfo("create", "gifobj::getSize()");
    CHECKTOLUAFUNCCALL(GifBase, create);
    CHECKTOLUAFUNCCALL(GifBase, getSize);
    std::string typeName = typeid(GifBase).name();
    g_luaType[typeName] = "CheckCpp.gifbase";
    g_typeCast["gifbase"] = "CheckCpp.gifbase";

    return 0;
}
