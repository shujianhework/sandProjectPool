#include "LuaScriptManage.h"
#include <iostream>


bool LuaScriptManage::startFile(std::string path)
{
	if (L == NULL) {
		L = luaL_newstate();
		luaL_openlibs(L);
	}
	auto_register_all_Class();
	int ret = luaL_loadfile(L, path.c_str());
	if (ret) {
		return false;
	}
	return true;	
}

bool LuaScriptManage::pcall(int retArg, std::function<unsigned(SCTIPTCTYPE)> param)
{
	unsigned paramcout = 0;
	if (param != nullptr) {
		paramcout = param(L);
	}
	lua_pcall(L, paramcout, retArg, 0);
	return true;
}

void LuaScriptManage::putValue(long long value)
{
	lua_pushinteger(L, value);
}

void LuaScriptManage::putValue(double value)
{
	lua_pushnumber(L, value);
}

void LuaScriptManage::putValue(unsigned long long value)
{
	lua_pushinteger(L, value);
}
void LuaScriptManage::putValue(bool value)
{
	lua_pushboolean(L, value);
}

void LuaScriptManage::putValue()
{
	lua_pushnil(L);
}

void LuaScriptManage::putValue(std::string key)
{
	lua_pushstring(L, key.c_str());
}

void LuaScriptManage::putValue(void* ptr, int size)
{
	
}

void LuaScriptManage::putValue(std::function<int(SCTIPTCTYPE)> value)
{

}

void LuaScriptManage::newTable()
{
	lua_newtable(L);
}

void LuaScriptManage::pop(int idx)
{
	lua_pop(L, idx);
}

void LuaScriptManage::getGlobal(std::string key)
{
	lua_getglobal(L, key.c_str());
}

void LuaScriptManage::setfield(int idx, std::string key)
{
	lua_setfield(L, idx, key.c_str());
}
