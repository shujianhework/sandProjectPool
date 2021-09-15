#include "../test/testLuaTools.h"
#include "ser_autoLua_testLuaTools.h"

static std::string luaSave2CFunctionName = "";

static int Ser_AutoLua_LuaTools1_index_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools1_newindex_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools1_setName(lua_State* L);
static int Ser_AutoLua_LuaTools1_test002(lua_State* L);
static int Ser_AutoLua_LuaTools1_newobj_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools1_gc_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools2_index_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools2_newindex_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools2_setName(lua_State* L);
static int Ser_AutoLua_LuaTools2_newobj_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools2_gc_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools5_index_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools5_newindex_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools5_testAdd(lua_State* L);
static int Ser_AutoLua_LuaTools5_setName(lua_State* L);
static int Ser_AutoLua_LuaTools5_newobj_luaTable(lua_State* L);
static int Ser_AutoLua_LuaTools5_gc_luaTable(lua_State* L);

luaL_Reg Reg_lua_LuaTools1__001[]{
	{"__index",Ser_AutoLua_LuaTools1_index_luaTable},
	{"__newindex",Ser_AutoLua_LuaTools1_newindex_luaTable},
	{"aaaa",Ser_AutoLua_LuaTools1_newindex_luaTable},
	{"__gc",Ser_AutoLua_LuaTools1_gc_luaTable}
};

luaL_Reg Reg_lua_LuaTools2__001 []{
	{"__index",Ser_AutoLua_LuaTools2_index_luaTable},
	{"baaa",Ser_AutoLua_LuaTools2_gc_luaTable},
	{"__newindex",Ser_AutoLua_LuaTools2_newindex_luaTable},
	{"__gc",Ser_AutoLua_LuaTools2_gc_luaTable}
};

luaL_Reg Reg_lua_LuaTools5__001 []{
	{"__index",Ser_AutoLua_LuaTools5_index_luaTable},
	{"__newindex",Ser_AutoLua_LuaTools5_newindex_luaTable},
	{"__gc",Ser_AutoLua_LuaTools5_gc_luaTable}
};


void ser_autoLua_file_testLuaTools(){
	LuaScriptManage* LSM = GETINSTANCEMANAGE(LuaScriptManage);
	luaSave2CFunctionName = LSM->luaSave2CFunctionTableName();
	lua_State *L = LSM->getL();

	lua_getglobal(L, "_G"); 
	std::map<std::string, lua_CFunction> funs = {};
	for (int i = 0; i < sizeof(Reg_lua_LuaTools1__001)/sizeof(luaL_Reg); i++)
	{
		luaL_Reg lg = Reg_lua_LuaTools1__001[i];
		funs.insert(std::make_pair(lg.name, lg.func));
	}
	LSM->pushDict<lua_CFunction>(funs, [](lua_State* L1, lua_CFunction f1) {
		lua_pushcfunction(L1, f1);
	}, "Reg_lua_LuaTools1__001");
	/*lua_newtable(L); 
	luaL_setfuncs(L, Reg_lua_LuaTools1__001, 0);*/
	//lua_setfield(L, -2, "Reg_lua_LuaTools1__001"); 
	lua_getglobal(L, "_G"); 
	lua_pushcfunction(L, Ser_AutoLua_LuaTools1_newobj_luaTable);
	lua_setfield(L, -2, "LuaTools1"); 

	lua_getglobal(L, "_G");
	lua_newtable(L);
	luaL_setfuncs(L, Reg_lua_LuaTools2__001, 0);
	lua_setfield(L, -2, "Reg_lua_LuaTools2__001");
	lua_pop(L, 1);
	lua_getglobal(L, "_G");
	lua_pushcfunction(L, Ser_AutoLua_LuaTools2_newobj_luaTable);
	lua_setfield(L, -2, "LuaTools2");

	lua_getglobal(L, "_G");
	lua_newtable(L);
	luaL_setfuncs(L, Reg_lua_LuaTools5__001, 0);
	lua_setfield(L, -2, "Reg_lua_LuaTools5__001");
	lua_pop(L, 1);
	lua_getglobal(L, "_G");
	lua_pushcfunction(L, Ser_AutoLua_LuaTools5_newobj_luaTable);
	lua_setfield(L, -2, "LuaTools5");
	/*MAKECLASS2TABLE(Ser_AutoLua_LuaTools1_newobj_luaTable,LuaTools1,Reg_lua_LuaTools1__001);
	MAKECLASS2TABLE(Ser_AutoLua_LuaTools5_newobj_luaTable, LuaTools5, Reg_lua_LuaTools5__001);
	MAKECLASS2TABLE(Ser_AutoLua_LuaTools2_newobj_luaTable,LuaTools2,Reg_lua_LuaTools2__001);*/
	REGISTERCLASS2CODE(LuaTools1,{},true);
	REGISTERCLASS2CODE(LuaTools5,{"LuaTools1"});
	REGISTERCLASS2CODE(LuaTools2, { "LuaTools1" });
};
static int Ser_AutoLua_LuaTools1_setName(lua_State* L){

	GETUSERDATA2TYPE(LuaTools1, obj, 1);
	if (obj != NULL &&  lua_type( L,2) == LUA_TSTRING &&  true ){
		std::string auto_stdstring_1 = lua_tostring(L,2);
		lua_pushboolean(L,obj->setName(auto_stdstring_1));
		return 1;
	}

	return 0;
}
static int Ser_AutoLua_LuaTools1_test002(lua_State* L){

	GETUSERDATA2TYPE(LuaTools1, obj, 1);
	if (obj != NULL &&  lua_type( L,2) == LUA_TNUMBER &&  lua_type( L,3) == LUA_TSTRING &&  lua_type( L,4) == LUA_TNUMBER &&  lua_type( L,5) == LUA_TSTRING &&  true ){
		int auto_int_1 = lua_tonumber(L,2);
		std::string auto_stdstring_2 = lua_tostring(L,3);
		float auto_float_3 = lua_tonumber(L,4);
		std::string auto_stdstring_4 = lua_tostring(L,5);
		obj->test002(auto_int_1, auto_stdstring_2, auto_float_3, auto_stdstring_4);
		return 0;
	}

	if (obj != NULL &&  lua_type( L,2) == LUA_TNUMBER &&  lua_type( L,3) == LUA_TSTRING &&  lua_type( L,4) == LUA_TNUMBER &&  lua_type( L,5) == LUA_TNUMBER &&  true ){
		int auto_int_1 = lua_tonumber(L,2);
		std::string auto_stdstring_2 = lua_tostring(L,3);
		float auto_float_3 = lua_tonumber(L,4);
		int auto_int_4 = lua_tonumber(L,5);
		obj->test002(auto_int_1, auto_stdstring_2, auto_float_3, auto_int_4);
		return 0;
	}

	if (obj != NULL &&  lua_type( L,2) == LUA_TNUMBER &&  lua_type( L,3) == LUA_TSTRING &&  lua_type( L,4) == LUA_TNUMBER &&  true ){
		int auto_int_1 = lua_tonumber(L,2);
		std::string auto_stdstring_2 = lua_tostring(L,3);
		float auto_float_3 = lua_tonumber(L,4);
		obj->test002(auto_int_1, auto_stdstring_2, auto_float_3);
		return 0;
	}

	if (obj != NULL &&  lua_type( L,2) == LUA_TNUMBER &&  lua_type( L,3) == LUA_TUSERDATA &&  lua_type( L,4) == LUA_TFUNCTION &&  true ){
		int auto_int_1 = lua_tonumber(L,2);
		GETUSERDATA2TYPE(LuaTools1, auto_LuaTools1_2, 3);
		auto auto_Type1_3 = lua_tocfunction(L, 4);
		GETINSTANCEMANAGE(LuaScriptManage)->saveLuaFun2cpp(obj,"LuaTools1_test002_4_",auto_Type1_3);

		Type1 auto_Type1_3_fun = [](unsigned int objId, int callback0 ,int callback1 ,int callback2 ) {

			LuaUserDataBase* obj = LuaUserDataBase::getLuaObjectPool(objId);
			auto c2luaback = GETINSTANCEMANAGE(LuaScriptManage)->getLuaFun2cpp(obj,"LuaTools1_test002_4_");
			if ( c2luaback == NULL){
				printf("theread id not lua theread or");
				return;
			}
			auto L = GETINSTANCEMANAGE(LuaScriptManage)->getL();
			lua_pushnumber(L,callback0);
			lua_pushnumber(L,callback1);
			lua_pushnumber(L,callback2);
			return ;
		};

		lua_pushnumber(L,obj->test002(auto_int_1, auto_LuaTools1_2, auto_Type1_3_fun));
		return 1;
	}

	if (obj != NULL &&  lua_type( L,2) == LUA_TNUMBER &&  lua_type( L,3) == LUA_TSTRING &&  true ){
		int auto_int_1 = lua_tonumber(L,2);
		std::string auto_stdstring_2 = lua_tostring(L,3);
		obj->test002(auto_int_1, auto_stdstring_2);
		return 0;
	}

	if (obj != NULL &&  lua_type( L,2) == LUA_TNUMBER &&  lua_type( L,3) == LUA_TNUMBER &&  true ){
		int auto_int_1 = lua_tonumber(L,2);
		int auto_int_2 = lua_tonumber(L,3);
		obj->test002(auto_int_1, auto_int_2);
		return 0;
	}

	return 0;
}
static int Ser_AutoLua_LuaTools1_index_luaTable(lua_State* L){

	GETUSERDATA2TYPE(LuaTools1, obj, -2);
	if (lua_type(L,-1) != LUA_TSTRING){
		 return 0;
 	}

	std::string key = lua_tostring(L, -1);
	if ( key == "setName"){
		lua_pushcfunction(L, Ser_AutoLua_LuaTools1_setName);
		return 1;
	}

	if ( key == "test002"){
		lua_pushcfunction(L, Ser_AutoLua_LuaTools1_test002);
		return 1;
	}

	if ( obj == NULL )
		return 0;
	if ( key == "salary"){
		lua_pushnumber(L,obj->salary);
		return 1;
	}

	if ( key == "userid"){
		lua_pushnumber(L,obj->userid);
		return 1;
	}

	return 0;
}
static int Ser_AutoLua_LuaTools1_newindex_luaTable(lua_State* L){

	if (lua_type(L,2) != LUA_TSTRING){
		 return 0;
 	}
	std::string key = lua_tostring(L, 2);
	GETUSERDATA2TYPE(LuaTools1, obj, 1);
	double autovalsalary = lua_tonumber(L,3);
	if ( key == "salary"){
		obj->salary = autovalsalary;
		return 0;
	}
	return 0;
}
static int Ser_AutoLua_LuaTools1_gc_luaTable(lua_State* L){

	LuaTools1* obj = (LuaTools1*)lua_touserdata(L,-1);
	
	return 0;
}
static int Ser_AutoLua_LuaTools1_newobj_luaTable(lua_State* L){

	char *p = (char*)lua_newuserdata(L, sizeof( LuaTools1));
	LuaTools1* ret = NULL;
	if ( ret == NULL &&  lua_type( L,1) == LUA_TSTRING &&  true ){
		std::string auto_stdstring_1 = lua_tostring(L,1);
		ret = new(p)LuaTools1(auto_stdstring_1);
	}

	if ( ret == NULL &&  lua_type( L,1) == LUA_TBOOLEAN &&  true ){
		bool auto_bool_1 = lua_toboolean(L,1);
		ret = new(p)LuaTools1(auto_bool_1);
	}

	if ( ret == NULL &&  lua_type( L,1) == LUA_TNUMBER &&  true ){
		int auto_int_1 = lua_tonumber(L,1);
		ret = new(p)LuaTools1(auto_int_1);
	}

	if ( ret == NULL &&  true ){
		ret = new(p)LuaTools1();
	}

	if(ret == NULL){
		return 0;
	}
	setObjectClass(ret, "LuaTools1");
	lua_getglobal(L, "Reg_lua_LuaTools1__001");
	lua_setmetatable(L, -2);
	return 1;
}
static int Ser_AutoLua_LuaTools2_setName(lua_State* L){

	GETUSERDATA2TYPE(LuaTools2, obj, 1);
	if (obj != NULL &&  lua_type( L,2) == LUA_TSTRING &&  true ){
		std::string auto_stdstring_1 = lua_tostring(L,2);
		lua_pushboolean(L,obj->setName(auto_stdstring_1));
		return 1;
	}

	return 0;
}
static int Ser_AutoLua_LuaTools2_index_luaTable(lua_State* L){

	GETUSERDATA2TYPE(LuaTools2, obj, -2);
	if (lua_type(L,-1) != LUA_TSTRING){
		 return 0;
 	}

	std::string key = lua_tostring(L, -1);
	if ( key == "setName"){
		lua_pushcfunction(L, Ser_AutoLua_LuaTools2_setName);
		return 1;
	}

	if ( obj == NULL )
		return 0;
	if ( key == "salary"){
		lua_pushnumber(L,obj->salary);
		return 1;
	}

	if ( key == "userid"){
		lua_pushnumber(L,obj->userid);
		return 1;
	}

	return 0;
}
static int Ser_AutoLua_LuaTools2_newindex_luaTable(lua_State* L){

	if (lua_type(L,2) != LUA_TSTRING){
		 return 0;
 	}
	std::string key = lua_tostring(L, 2);
	GETUSERDATA2TYPE(LuaTools2, obj, 1);
	double autovalsalary = lua_tonumber(L,3);
	if ( key == "salary"){
		obj->salary = autovalsalary;
		return 0;
	}
	return 0;
}
static int Ser_AutoLua_LuaTools2_gc_luaTable(lua_State* L){

	LuaTools2* obj = (LuaTools2*)lua_touserdata(L,-1);
	
	return 0;
}
static int Ser_AutoLua_LuaTools2_newobj_luaTable(lua_State* L){

	char *p = (char*)lua_newuserdata(L, sizeof( LuaTools2));
	LuaTools2* ret = NULL;
	if ( ret == NULL &&  lua_type( L,1) == LUA_TSTRING &&  true ){
		std::string auto_stdstring_1 = lua_tostring(L,1);
		ret = new(p)LuaTools2(auto_stdstring_1);
	}

	if ( ret == NULL &&  lua_type( L,1) == LUA_TBOOLEAN &&  true ){
		bool auto_bool_1 = lua_toboolean(L,1);
		ret = new(p)LuaTools2(auto_bool_1);
	}

	if ( ret == NULL &&  lua_type( L,1) == LUA_TNUMBER &&  true ){
		int auto_int_1 = lua_tonumber(L,1);
		ret = new(p)LuaTools2(auto_int_1);
	}

	if ( ret == NULL &&  true ){
		ret = new(p)LuaTools2();
	}

	if(ret == NULL){
		return 0;
	}
	setObjectClass(ret, "LuaTools2");
	lua_getglobal(L, "Reg_lua_LuaTools2__001");
	lua_setmetatable(L, -2);
	return 1;
}
static int Ser_AutoLua_LuaTools5_testAdd(lua_State* L){

	GETUSERDATA2TYPE(LuaTools5, obj, 1);
	if (obj != NULL &&  lua_type( L,2) == LUA_TNUMBER &&  lua_type( L,3) == LUA_TNUMBER &&  lua_type( L,4) == LUA_TNUMBER &&  true ){
		int auto_int_1 = lua_tonumber(L,2);
		int auto_int_2 = lua_tonumber(L,3);
		int auto_int_3 = lua_tonumber(L,4);
		obj->testAdd(auto_int_1, auto_int_2, auto_int_3);
		return 0;
	}

	return 0;
}
static int Ser_AutoLua_LuaTools5_setName(lua_State* L){

	GETUSERDATA2TYPE(LuaTools5, obj, 1);
	if (obj != NULL &&  lua_type( L,2) == LUA_TSTRING &&  true ){
		std::string auto_stdstring_1 = lua_tostring(L,2);
		lua_pushboolean(L,obj->setName(auto_stdstring_1));
		return 1;
	}

	return 0;
}
static int Ser_AutoLua_LuaTools5_index_luaTable(lua_State* L){

	GETUSERDATA2TYPE(LuaTools5, obj, -2);
	if (lua_type(L,-1) != LUA_TSTRING){
		 return 0;
 	}

	std::string key = lua_tostring(L, -1);
	if ( key == "testAdd"){
		lua_pushcfunction(L, Ser_AutoLua_LuaTools5_testAdd);
		return 1;
	}

	if ( key == "setName"){
		lua_pushcfunction(L, Ser_AutoLua_LuaTools5_setName);
		return 1;
	}

	if ( obj == NULL )
		return 0;
	if ( key == "salary"){
		lua_pushnumber(L,obj->salary);
		return 1;
	}

	if ( key == "userid"){
		lua_pushnumber(L,obj->userid);
		return 1;
	}

	if ( key == "userabl"){
		lua_pushnumber(L,obj->userabl);
		return 1;
	}

	return 0;
}
static int Ser_AutoLua_LuaTools5_newindex_luaTable(lua_State* L){

	if (lua_type(L,2) != LUA_TSTRING){
		 return 0;
 	}
	std::string key = lua_tostring(L, 2);
	GETUSERDATA2TYPE(LuaTools5, obj, 1);
	double autovalsalary = lua_tonumber(L,3);
	if ( key == "salary"){
		obj->salary = autovalsalary;
		return 0;
	}
	int autovaluserabl = lua_tonumber(L,3);
	if ( key == "userabl"){
		obj->userabl = autovaluserabl;
		return 0;
	}
	return 0;
}
static int Ser_AutoLua_LuaTools5_gc_luaTable(lua_State* L){

	LuaTools5* obj = (LuaTools5*)lua_touserdata(L,-1);
	
	return 0;
}
static int Ser_AutoLua_LuaTools5_newobj_luaTable(lua_State* L){

	char *p = (char*)lua_newuserdata(L, sizeof( LuaTools5));
	LuaTools5* ret = NULL;
	if ( ret == NULL &&  true ){
		ret = new(p)LuaTools5();
	}

	if(ret == NULL){
		return 0;
	}
	setObjectClass(ret, "LuaTools5");
	lua_getglobal(L, "Reg_lua_LuaTools5__001");
	lua_setmetatable(L, -2);
	return 1;
}
