#include "testLuaTools.h"

LuaTools1::LuaTools1():name(""),userid(0),salary(0.0)
{
}
LuaTools1::LuaTools1(std::string a) : name(""), userid(0), salary(0.0){}
LuaTools1::LuaTools1(int b) : name(""), userid(0), salary(0.0){}
LuaTools1::LuaTools1(bool b) : name(""), userid(0), salary(0.0){}
bool LuaTools1::setName(std::string pname)
{
    if (name.size() == 0) {
        name = pname;
        return true;
    }
    return false;
}

void LuaTools1::test002(int arg, std::string var1, float var2)
{

}

LuaTools2::LuaTools2() :name(""), userid(0), salary(0.0)
{
}
LuaTools2::LuaTools2(std::string a) : name(""), userid(0), salary(0.0) {}
LuaTools2::LuaTools2(int b): name(""), userid(0), salary(0.0) {
}
LuaTools2::LuaTools2(bool b) : name(""), userid(0), salary(0.0) {}
bool LuaTools2::setName(std::string pname)
{
    if (name.size() == 0) {
        name = pname;
        return true;
    }
    return false;
}

void LuaTools5::testAdd(int a, int b, int c)
{
    int sum = a + b + c;
    sum = a * sum;
    sum = sum / b;
    return ;
}
