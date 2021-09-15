#pragma once
#include <vector>
#include <string>
//һ��ֻ����һ�����뵽lua����

#define ExtensionClassAssistant(...)
#define BASECLUACLASS(base) public base
//#define BASECLUACLASS(ARG) public ARG
#define CLUACLASSEND
//��������Ķ����ڲ�����ʹ��/**/
// struct �� class 
//�����ϱ�ָ����������� 
//1 ���к����� ����ǰ׺EXPORTFUN �ĺ��������Զ�����lua��������
//2 ���г�Ա������,ǰ׺�����EXPORTVALSET �Զ�������lua aa.value = obj,EXPORTVALGET �Զ������� if aa.value then
#define EXPORTVALSET
#define EXPORTVALGET
#define EXPORTFUN
//#define CPP2LUABACKFUN (...) (void)(__VA_ARGS__)*
#define CPP2LUABACKREGISTERFUN(NewType,...) typedef void( * NewType)( unsigned int , __VA_ARGS__)

//�����ĸ���ָ��
//ָ��������new ����ĺ������� ��ȡ��̬����ĺ���
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
