#include "LuaDefineTools.h"
#include <string>
#include "../Manages/LuaScriptManage.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
static std::map<std::string,unsigned int*> classHashMap = {};
unsigned char* ptr1 = NULL;
unsigned int maxlen = 512;
unsigned int uselen = 0;
static std::map<unsigned int, bool> useFunHandles = {};
static std::map<unsigned int, unsigned int> objPools = {};
static std::map<unsigned int, unsigned int> objPoolsEx = {};
static std::map<unsigned int, LuaUserDataBase*> dyAddLuaObjectPools = {};
bool registerClassToCode(std::string name, std::vector<std::string> bases, bool funFlg){

	if (classHashMap.find(name) != classHashMap.end())
		return false;
	const unsigned int nowlen = name.length() + bases.size() + (sizeof(unsigned int) * 3);
	if ((nowlen + uselen) > maxlen) {
		unsigned char* ptr2 = new unsigned char[maxlen + nowlen + 512];
		if (ptr2 == NULL)
			return false;
		if (uselen > 0) {
			memcpy(ptr2, ptr1, uselen);
		}
		memset(&ptr2[uselen], 0, maxlen + nowlen + 512 - uselen);
		if (uselen > 0)
			delete ptr1;
		ptr1 = ptr2;
	}
	else if (uselen == 0 && ptr1 == NULL) {
		ptr1 = new unsigned char[maxlen];
		memset(ptr1, 0, maxlen);
	}
	unsigned char* p1 = &ptr1[uselen];
	int offset = name.size();
	memcpy(p1, name.c_str(), offset);
	p1[offset] = 0;
	int hashCode = classHashMap.size() + 1024;
	offset++;
	memcpy(&p1[offset], &hashCode, sizeof(hashCode));
	offset += sizeof(hashCode);
	int baselens = bases.size();
	memcpy(&p1[offset], &baselens, sizeof(hashCode));
	for (int i = 0; i < baselens; i++)
	{
		offset += sizeof(hashCode);
		auto iter = classHashMap.find(bases[i]);
		if (iter == classHashMap.end()) {
			memset(p1, 0, offset);
			return false;
		}
		hashCode = *(iter->second);
		memcpy(&p1[offset], &hashCode, sizeof(hashCode));
	}
	classHashMap.insert( std::make_pair((char*)p1, (unsigned int*)&p1[name.size() + 1]) );
	uselen += offset;
	uselen += sizeof(hashCode);
	if (funFlg) {
		useFunHandles.insert(std::make_pair(hashCode, 1));
	}
	return 0;
}
bool setObjectClass(LuaUserDataBase* obj, std::string name){
	auto iter = classHashMap.find(name);
	if (iter == classHashMap.end() || obj == NULL) {
		return false;
	}
	unsigned int *hashCode = iter->second;
	obj->use00Class00Code_Id = *hashCode;
	if (useFunHandles.find(obj->use00Class00Code_Id) == useFunHandles.end()) {
		obj->use00Lua00Obj00Hash_Id = 0;
		return true;
	}
	unsigned int size = objPools.size();
	if (size == 0) {
		srand(time(NULL));
	}
	unsigned int hash_id = rand() % 0x3ffff + 1;
	unsigned int max = (unsigned int)-2;
	if (size < 0x3ffffff) {
		int tryLen = 3500;
		hash_id = size + 1;
		while (tryLen > 0) {
			if (objPools.find(hash_id) == objPools.end()) {
				obj->use00Lua00Obj00Hash_Id = hash_id;
				objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
				return true;
			}
			if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
				obj->use00Lua00Obj00Hash_Id = hash_id;
				objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
				return true;
			}
			hash_id = rand() % 0x3ffff + 1;
			tryLen--;
		}
	}
	else {
		int tryLen = 0xfffff;
		hash_id = size + 1;
		while (tryLen > 0) {
			if (objPools.find(hash_id) == objPools.end()) {
				obj->use00Lua00Obj00Hash_Id = hash_id;
				objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
				return true;
			}
			if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
				obj->use00Lua00Obj00Hash_Id = hash_id;
				objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
				return true;
			}
			hash_id = rand() % 0x3ffff + 1;
			tryLen--;
		}
	}
	if (objPools.find(hash_id) == objPools.end()) {
		obj->use00Lua00Obj00Hash_Id = hash_id;
		objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
		return true;
	}
	if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
		obj->use00Lua00Obj00Hash_Id = hash_id;
		objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
		return true;
	}
	hash_id = time(NULL);
	if (objPools.find(hash_id) == objPools.end()) {
		obj->use00Lua00Obj00Hash_Id = hash_id;
		objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
		return true;
	}
	if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
		obj->use00Lua00Obj00Hash_Id = hash_id;
		objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
		return true;
	}
	//Ó²±éÀú
	for (size_t i = 1; i < 0xffffff; i++)
	{
		hash_id = i;
		if (objPools.find(hash_id) == objPools.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
		if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}

		hash_id = 0xffffff + i * 2;
		if (objPools.find(hash_id) == objPools.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
		if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
	}
	for (size_t i = 0x2ffffff; i < 0xfffffff; i++)
	{
		hash_id = i;
		if (objPools.find(hash_id) == objPools.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
		if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}

		hash_id = 0xfffffff + i * 3;
		if (objPools.find(hash_id) == objPools.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
		if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
	}
	
	for (unsigned int i = 1; i < 0xffffff; i++)
	{
		hash_id = max - i;
		if (objPools.find(hash_id) == objPools.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
		if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}

		hash_id = hash_id - 0xffffff;
		if (objPools.find(hash_id) == objPools.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPools.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
		if (objPoolsEx.find(hash_id) == objPoolsEx.end()) {
			obj->use00Lua00Obj00Hash_Id = hash_id;
			objPoolsEx.insert(std::make_pair(hash_id, obj->use00Class00Code_Id));
			return true;
		}
	}
	return false;
}
bool isObjectClass(LuaUserDataBase* obj, std::string name) {
	
	auto iter = classHashMap.find(name);
	if (iter == classHashMap.end() || obj == NULL) {
		return false;
	}
	unsigned int* objCode = iter->second;
	char* p = (char*)obj;
	unsigned int* srcCode = (unsigned int*)p[-4];
	return (*srcCode == *objCode);
}
bool isAddr2ConvertClass(LuaUserDataBase* obj, std::string name)
{
	auto iter = classHashMap.find(name);
	if (iter == classHashMap.end() || obj == NULL) {
		return false;
	}
	unsigned int* objCode = iter->second;
	if (obj->use00Class00Code_Id == objCode[0])
		return true;
	unsigned int len = objCode[1];
	for (unsigned int i = 0; i < len; i++)
	{
		if (objCode[i + 2] == obj->use00Class00Code_Id)
			return true;
	}
	return false;

}
bool removeObjId(LuaUserDataBase* obj)
{
	if (obj != NULL) {
		if (obj->use00Lua00Obj00Hash_Id == 0)
			return false;
		auto iter = objPools.find(obj->use00Lua00Obj00Hash_Id);
		auto funiter = useFunHandles.find(obj->use00Lua00Obj00Hash_Id);
		if (funiter != useFunHandles.end())
			useFunHandles.erase(funiter);
		if (iter != objPools.end() || iter->second == obj->use00Class00Code_Id) {
			objPools.erase(iter);
			return true;
		}
		auto iterex = objPoolsEx.find(obj->use00Lua00Obj00Hash_Id);
		if (iter != objPoolsEx.end() || iter->second == obj->use00Class00Code_Id) {
			objPoolsEx.erase(iter);
			return true;
		}
	}
	return false;
}
void* getUserdata2void(std::string className, unsigned int idx) {
	
	lua_State* L = GETINSTANCEMANAGE(LuaScriptManage)->getL();
	if (lua_type(L, idx) != LUA_TUSERDATA)
		return NULL;
	void *p = lua_touserdata(L, idx);
	if (p == NULL)
		return NULL;
	LuaUserDataBase* ludb = (LuaUserDataBase*)p;
	if (isAddr2ConvertClass(ludb, className))
		return p;
	return NULL;

}

LuaUserDataBase::~LuaUserDataBase()
{
	removeObjId(this);	
}

LuaUserDataBase* LuaUserDataBase::getLuaObjectPool(unsigned int luaId)
{

	auto iter = dyAddLuaObjectPools.find(luaId);
	if (iter == dyAddLuaObjectPools.end()) {
		return NULL;
	}
	return iter->second;;
}

bool LuaUserDataBase::saveId2Map()
{
	if (this->use00Lua00Obj00Hash_Id == 0) {
		return false;
	}
	if (dyAddLuaObjectPools.find(this->use00Lua00Obj00Hash_Id) != dyAddLuaObjectPools.end())
		return true;
	dyAddLuaObjectPools.insert(std::make_pair(this->use00Lua00Obj00Hash_Id, this));
	return true;
}
