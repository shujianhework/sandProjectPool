#include "../Manages/LuaScriptManage.h"
#include "../tools/StringTools.h"



//以下包含的头文件以及对应实现文件是代码生成工具生成的，本文件也是工具生成


#include "ser_autoLua_testLuaTools.h"

std::string LuaScriptManage::luaSave2CFunctionTableName(){
	return "sys_lua2csave_funs_table";
}
lua_CFunction LuaScriptManage::getLuaFun2cpp(LuaUserDataBase* ludb, std::string saveKey){

	if ( ludb == NULL || ludb->use00Lua00Obj00Hash_Id == 0)
		return NULL;

	lua_getglobal(L,this->luaSave2CFunctionTableName().c_str());
	lua_getfield(L,-1,StringTools::number2Str(ludb->use00Lua00Obj00Hash_Id).c_str());
	if (lua_type(L, -1) == LUA_TTABLE) {
		lua_getfield(L, -2, saveKey.c_str());
		if (lua_type(L, -1) == LUA_TFUNCTION) {
			lua_CFunction fun = lua_tocfunction(L, -1);
			lua_pop(L, 1);
			return fun;
		}
		lua_pop(L, 1);
	}
	lua_pop(L, 1);

	return NULL;
}
bool LuaScriptManage::saveLuaFun2cpp(LuaUserDataBase* ludb, std::string saveKey, lua_CFunction luaFun){

	if ( ludb == NULL || ludb->use00Lua00Obj00Hash_Id == 0)
		return false;

	lua_getglobal(L,this->luaSave2CFunctionTableName().c_str());
	lua_getfield(L,-1,StringTools::number2Str(ludb->use00Lua00Obj00Hash_Id).c_str());
	lua_pushcfunction(L,luaFun);
	lua_setfield(L,-2,saveKey.c_str());

	return true;
}
void LuaScriptManage::auto_register_all_Class(){

	auto LSM = GETINSTANCEMANAGE(LuaScriptManage);
	auto L = LSM->getL();
	lua_getglobal(L,"_G");
	lua_newtable(L);
	lua_pushstring(L,LSM->luaSave2CFunctionTableName().c_str());
	lua_rawseti(L, -2, 0);
	ser_autoLua_file_testLuaTools();
	
}