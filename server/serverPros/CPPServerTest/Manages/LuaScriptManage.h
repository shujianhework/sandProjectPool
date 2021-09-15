#pragma once
#include "../InstanceManages.h"
#include <functional>
extern "C" {
	#include "../lua/lua.h"
	#include "../lua/lualib.h"
	#include "../lua/lauxlib.h"
}
#include "../luaTools/LuaDefineTools.h"
#include "../test/testLuaTools.h"  ExtensionClassAssistant(LuaTools1,LuaTools2,LuaTools5)

#include <vector>
#include "../E_luaScriptClassMemberType.h"
#define SCTIPTCTYPE lua_State*
//还缺函数类型？？？
//backFun(back,param2,...)
class LuaScriptManage :INSTANCEITEM
{
	SCTIPTCTYPE L;
	std::function<int(void*, SCTIPTCTYPE, std::string)> backdyType;
	void auto_register_all_Class();
public:
	LuaScriptManage() {
		L = NULL;
		INSTANCECPPMAKE(LuaScriptManage);
		init();
	}
	void init() {
		if (L == NULL) {
			L = luaL_newstate();
			luaL_openlibs(L);
		}
	}
	~LuaScriptManage() {

		if (L != NULL)
			lua_close(L);
		L = NULL;
	}
	inline SCTIPTCTYPE getL() {
		return L;
	}
	std::string luaSave2CFunctionTableName();
	bool startFile(std::string path);
	bool pcall(int retArg, std::function<unsigned(SCTIPTCTYPE)> param = nullptr);
	void putValue(long long value);
	void putValue(double value);
	void putValue(unsigned long long value);
	void putValue(bool value);
	void putValue();
	void putValue(std::string key);
	void putValue(void* ptr, int size);
	void putValue(std::function<int(SCTIPTCTYPE)> value);
	void newTable();
	void pop(int idx = -1);
	void getGlobal(std::string key);
	bool saveLuaFun2cpp(LuaUserDataBase* ludb, std::string saveKey, lua_CFunction luaFun);
	lua_CFunction getLuaFun2cpp(LuaUserDataBase* ludb, std::string saveKey);
	void setfield(int idx, std::string key);

	template<typename T>
	void pushArrray(std::vector<T> vector, std::function<void(SCTIPTCTYPE, T)> back, std::string newKey = "") {

		if (newKey != "") {
			lua_newtable(L);
			lua_pushnumber(L, -1);
			lua_rawseti(L, -2, 0);
		}
		T* t = NULL;
		for (int i = 0; i < vector.size(); i++)
		{
			t = &vector[i];
			back(L, *t);
			lua_rawseti(L, -2, i + 1);
		}

	}
	template<typename T>
	void pushArray(T arr[], int len, std::function<void(SCTIPTCTYPE, T)> back, std::string newKey = "") {

		if (newKey != "") {
			lua_newtable(L);
			lua_pushnumber(L, -1);
			lua_rawseti(L, -2, 0);
		}
		T* t = NULL;
		for (int i = 0; i < arr.size(); i++)
		{
			t = &arr[i];
			back(L, *t);
			lua_rawseti(L, -2, i + 1);
		}

	}
	template<typename T>
	void pushDict(std::map<std::string, T> data, std::function<void(SCTIPTCTYPE, T)>back, std::string newKey = "") {

		if (newKey != "") {
			lua_newtable(L);
			lua_pushnumber(L, -1);
			lua_rawseti(L, -2, 0);
		}
		T* t = NULL;
		std::string key = "";
		
		for (auto iter = data.begin(); iter != data.end(); iter++) {

			key = iter->first;
			t = &(iter->second);
			back(L, *t);
			lua_setfield(L, -2, key.c_str());
		}

	}

};