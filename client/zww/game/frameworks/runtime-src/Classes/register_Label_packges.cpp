#include "register_Label_packges.h"
#include "extend_package_define_helper.h"
#include "base/CCGameDyFuncsVersion.h"
extern "C" {
    #include "lua.h"
    #include "tolua++.h"
}
USING_NS_CC;

DEF_CHECKCPP2LUASTAICOBJCLASS(Label, setOtherFontFlg, "cc.Label")
    argc = 1;// lua_gettop(L) - 1;
    if (argc == 1) {
        int otherFontFlg = tolua_tonumber(L, 2, 0);
        cobj->setOtherFontFlg(otherFontFlg);
        tolua_pushboolean(L, true);
        return 1;
    }
    DEF_CHECKCPP2LUASTAIGOTOERR(Label, setOtherFontFlg, "cc.Label")
DEF_CHECKCPPEND

DEF_CHECKCPP2LUASTAICOBJCLASS(Label, isUnderline, "cc.Label")
    tolua_pushboolean(L, cobj->isUnderline());
    return 1;
    DEF_CHECKCPP2LUASTAIGOTOERR(Label, isUnderline, "cc.Label")
DEF_CHECKCPPEND

DEF_CHECKCPP2LUASTAICOBJCLASS(Label, isItalic, "cc.Label")
    tolua_pushboolean(L, cobj->isItalic());
    return 1;
    DEF_CHECKCPP2LUASTAIGOTOERR(Label, isItalic, "cc.Label")
DEF_CHECKCPPEND

DEF_CHECKCPP2LUASTAICOBJCLASS(Label, isStrikeOut, "cc.Label")
    tolua_pushboolean(L, cobj->isStrikeOut());
    return 1;
    DEF_CHECKCPP2LUASTAIGOTOERR(Label, isStrikeOut, "cc.Label")
DEF_CHECKCPPEND


int register_Label_packges(lua_State* L)
{
    lua_State* tolua_S = L;

    GameDyfuncsVersion::addFunInfo("setOtherFontFlg", "boolean setOtherFontFlg(cc.Label,number)");
    GameDyfuncsVersion::addFunInfo("isUnderline", "boolean isUnderline(cc.Label)");
    GameDyfuncsVersion::addFunInfo("isItalic", "boolean isItalic(cc.Label)");
    GameDyfuncsVersion::addFunInfo("isStrikeOut", "boolean isStrikeOut(cc.Label)");

    CHECKTOLUAFUNCCALL(Label, setOtherFontFlg);
    CHECKTOLUAFUNCCALL(Label, isUnderline);
    CHECKTOLUAFUNCCALL(Label, isItalic);
    CHECKTOLUAFUNCCALL(Label, isStrikeOut);

    return 0;
}
