#pragma once
#include <vector>
#include <string>
//一行只允许一个导入到lua的类

#define ExtensionClassAssistant(...)
#define BASECLUACLASS(base) public base
//#define BASECLUACLASS(ARG) public ARG
#define CLUACLASSEND
//被包含类的定义内部不能使用/**/
// struct 或 class 
//会在上边指定类里面查找 
//1 所有函数中 包含前缀EXPORTFUN 的函数集合自动生成lua关联函数
//2 所有成员变量中,前缀如果有EXPORTVALSET 自动关联到lua aa.value = obj,EXPORTVALGET 自动关联到 if aa.value then
#define EXPORTVALSET
#define EXPORTVALGET
#define EXPORTFUN
//#define CPP2LUABACKFUN (...) (void)(__VA_ARGS__)*
#define CPP2LUABACKREGISTERFUN(NewType,...) typedef void( * NewType)( unsigned int , __VA_ARGS__)

//导出的父类指定
//指定导出的new 对象的函数或者 获取静态对象的函数
#define EXPORTOBJFUN 
#define MAKECLASS2TABLE(classNewObj,className,reg) lua_getglobal(L, "_G");\
	lua_newtable(L);\
	luaL_setfuncs(L, reg, 0);\
	lua_setfield(L, -2, #reg);\
	lua_getglobal(L, "_G");\
	lua_pushcfunction(L, classNewObj);\
	lua_setfield(L, -2, #className);\
	lua_pop(L,1);
class LuaUserDataBase {
public:
	unsigned int use00Class00Code_Id;
	unsigned int use00Lua00Obj00Hash_Id;
	LuaUserDataBase() {
		use00Lua00Obj00Hash_Id = 0;
		use00Class00Code_Id = 0;
	}
	virtual ~LuaUserDataBase();
	inline unsigned int getObjId() {
		return use00Lua00Obj00Hash_Id;
	}
	static LuaUserDataBase* getLuaObjectPool(unsigned int luaId);
	bool saveId2Map();

};
bool registerClassToCode(std::string name,std::vector<std::string> bases,bool funFlg = false);
bool setObjectClass(LuaUserDataBase*obj,std::string name);
void* getUserdata2void(std::string className, unsigned int idx);
template<typename T>
T* getUserdata2Class(std::string className, unsigned int idx) {
	void *p = getUserdata2void(className, idx);
	if (p == NULL)
		return NULL;
	return (T*)p;
}
#define GETUSERDATA2TYPE(className,var,idx) className * var = getUserdata2Class< className >(#className,idx);
#define REGISTERCLASS2CODE(className,base) registerClassToCode(#className,base)
