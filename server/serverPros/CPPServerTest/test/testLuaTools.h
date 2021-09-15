#pragma once
#include "../luaTools/LuaDefineTools.h"
#include <string>
CPP2LUABACKREGISTERFUN(Type1,int,int,int);
class LuaTools1 :public LuaUserDataBase
{
	Type1 type1;
public:
	EXPORTOBJFUN LuaTools1();
	EXPORTOBJFUN LuaTools1(std::string a);
	EXPORTOBJFUN LuaTools1(int b);
	EXPORTOBJFUN LuaTools1(bool b);
	EXPORTVALGET int userid;
	std::string name;
	EXPORTFUN bool setName(std::string pname);
	EXPORTVALSET EXPORTVALGET double salary;
	EXPORTFUN void test002(int arg, std::string var1, float var2);
	EXPORTFUN void test002(int arg, std::string var1){}
	EXPORTFUN void test002(int arg, std::string var1, float var2,int a1){}
	EXPORTFUN void test002(int arg, std::string var1, float var2,std::string as){}
	EXPORTFUN void test002(int arg, int arg1){}
	EXPORTFUN int test002(int arg, LuaTools1 *lt,  Type1 type1) { return 2; }
	 
};
CLUACLASSEND
class LuaTools3 :public LuaUserDataBase,BASECLUACLASS(LuaTools1) 
{

};
CLUACLASSEND
class LuaTools5 :public LuaUserDataBase,BASECLUACLASS(LuaTools1){
public:
	EXPORTVALSET EXPORTVALGET int userabl;
	EXPORTFUN void testAdd(int a, int b, int c);
};
CLUACLASSEND
class LuaTools2 :public LuaUserDataBase,BASECLUACLASS(LuaTools1,LuaTools3)
{
public:
	EXPORTOBJFUN LuaTools2();
	EXPORTOBJFUN LuaTools2(std::string a);
	EXPORTOBJFUN LuaTools2(int b);
	EXPORTOBJFUN LuaTools2(bool b);
	EXPORTVALGET int userid;
	std::string name;
	EXPORTFUN bool setName(std::string pname);
	EXPORTVALSET EXPORTVALGET double salary;

};
CLUACLASSEND
