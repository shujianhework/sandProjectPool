#ifndef __EXTEND_PACK_DEFINE_HELP_H__
#define __EXTEND_PACK_DEFINE_HELP_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif
//#include "base/CCGameDyFuncsVersion.h" 
//这个定义系列宏，用来简化C++ 2 lua 编写代码

#define DEF_CHECKCPP2LUASTAICNOCLASS(CLASS,FUN) static int lua_CheckCpp_##CLASS##_##FUN(lua_State* L) {
#if COCOS2D_DEBUG >= 1
#define DEF_CHECKCPP2LUASTAICOBJCLASS(CLASS,FUN,LUACLASS) static int lua_CheckCpp_##CLASS##_##FUN(lua_State* tolua_S) {\
	lua_State* L = tolua_S;\
	int argc = 0;\
	CLASS *cobj = NULL;\
	tolua_Error tolua_err;\
	if (!tolua_isusertype(tolua_S, 1, LUACLASS, 0, &tolua_err)) goto tolua_lerror;\
	cobj = (CLASS *)tolua_tousertype(tolua_S, 1, 0);\
	if (!cobj){\
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_CheckCpp_"#CLASS"_"#FUN"'", nullptr);\
		return 0;\
	}\
	
#define DEF_CHECKCPP2LUASTAIGOTOERR(CLASS,FUN,LUACLASS)\
	tolua_lerror:\
	tolua_error(tolua_S, "#ferror in function 'lua_CheckCpp_"#CLASS"_"#FUN"'", &tolua_err);
#else
#define DEF_CHECKCPP2LUASTAICOBJCLASS(CLASS,FUN,LUACLASS) static int lua_CheckCpp_##CLASS##_##FUN(lua_State* L) {\
	lua_State* L = tolua_S;\
	int argc = 0; \
	CLASS* cobj = NULL;\
	cobj = (CLASS *)tolua_tousertype(tolua_S, 1, 0);\
	argc = lua_gettop(tolua_S) - 1;
#define #define DEF_CHECKCPP2LUASTAIGOTOERR(CLASS,FUN,LUACLASS)
#endif
#define CHECKCPP2LUAERROR()
#define NAM_CHECKCPP2LUASTAICNOCLASS(CLASS,FUN) lua_CheckCpp_##CLASS##_##FUN
#define DEF_CHECKCPPEND return 0;}

#define CHECKTOLUAFUNCCALL(CLASS,FUNNAME) tolua_function(tolua_S, #FUNNAME ,NAM_CHECKCPP2LUASTAICNOCLASS(CLASS,FUNNAME))

#endif//__EXTEND_PACK_DEFINE_HELP_H__