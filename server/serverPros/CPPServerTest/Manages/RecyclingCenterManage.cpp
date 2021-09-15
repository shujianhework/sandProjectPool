#include "RecyclingCenterManage.h"
#include <vector>

std::string RecyclingCenterManage::push(SObject* obj, unsigned long time) {
	
	if (obj == NULL)
		return "";
	//检查是否是重复对象
	std::mutex mt;
	mt.lock();
	for (auto iter = pool.begin(); iter != pool.end(); iter++) {
		SObject* item = iter->second->obj;
		if (item == obj)
		{
			mt.unlock();
			return iter->first;
		}
	}
	char arr[20] = "";
	sprintf(arr, "Recyc0x%d", *(int*)obj);
	RecyclingItem* ri = new RecyclingItem(arr,time);
	ri->obj = obj;
	mt.unlock();

	return arr;
}
std::string RecyclingCenterManage::push(const char* addr, unsigned long len)
{
	if (addr == NULL || len > 0x500000)
		return "";
	//检查是否是重复对象
	for (auto iter = pool.begin(); iter != pool.end(); iter++) {
		SObject* item = iter->second->obj;
		std::string key = iter->first;
		if (key.find("RecycP0x") != std::string::npos) {
			RecyclingCountItem* RCI = (RecyclingCountItem*)(iter->second);
			if (RCI->len == len) {
				return key;
			}
		}
	}
	char arr[20] = "";
	sprintf(arr, "RecycP0x%d", *(int*)addr);
	unsigned char* p = new unsigned char[len+1];
	if (p == NULL)
		return "";
	std::mutex mt;
	mt.lock();
	RecyclingCountItem* ri = new RecyclingCountItem(arr);
	ri->obj =NULL;
	ri->addr = p;
	memcpy(ri->addr, addr, len);
	ri->addr[len] = 0;
	ri->len = len;
	mt.unlock();

	return arr;
}
bool RecyclingCenterManage::erase(std::string key) {
	
	auto iter = pool.find(key);
	if (iter == pool.end())
		return false;

	std::mutex mt;
	mt.lock();
	iter->second->obj->onExit();
	delete iter->second->obj;
	delete iter->second;
	iter->second = NULL;
	pool.erase(key);
	mt.unlock();

	return true;
}
bool RecyclingCenterManage::pop(std::string key,SObject*& obj) {

	auto iter = pool.find(key);
	if (iter == pool.end())
		return false;
	if (iter->first.find("RecycP0x") != std::string::npos)
		return false;
	obj = iter->second->obj;
	delete iter->second;
	pool.erase(key);
	return true;

}
bool RecyclingCenterManage::pop(std::string key, unsigned char*& obj, unsigned int& len)
{
	auto iter = pool.find(key);
	if (iter == pool.end())
		return false;
	if (iter->first.find("Recyc0x") != std::string::npos)
		return false;
	RecyclingCountItem* RCI = (RecyclingCountItem*)(iter->second);
	obj = RCI->addr;
	len = RCI->len;
	delete iter->second;
	pool.erase(key);
	return true;
}
bool RecyclingCenterManage::peekCountItem(std::string key, unsigned char*& obj, unsigned int& len)
{
	auto iter = pool.find(key);
	if (iter == pool.end())
		return false;
	if (iter->first.find("Recyc0x") != std::string::npos)
		return false;
	RecyclingCountItem* RCI = (RecyclingCountItem*)(iter->second);
	obj = RCI->addr;
	len = RCI->len;
	delete iter->second;
	pool.erase(key);
	return false;
}
bool RecyclingCenterManage::swap(std::string key)
{

	return false;
}
void RecyclingCenterManage::init() {
	clear();
}
void RecyclingCenterManage::clear(bool isPrv) {

	if (pool.size() == 0)
		return;
	std::vector<std::string> keys;
	std::mutex mt;
	mt.lock();
	for (auto iter = pool.begin(); iter != pool.end(); iter++) {
		keys.push_back(iter->first);
	}
	for (int i = 0; i < keys.size(); i++)
	{
		auto iter = pool.find(keys[i]);
		SObject* obj = iter->second->obj;
		if (obj != NULL) {
			obj->onExit();
			delete obj;
			obj = NULL;
		}
		
		delete iter->second;
		iter->second = NULL;
		pool.erase(keys[i]);
	}
	mt.unlock();
	if (pool.size() > 0) {
		clear(true);
	}
	pool.clear();
}

RecyclingCenterManage::RecyclingItem::RecyclingItem(std::string rkey, unsigned time):obj(NULL)
{
	if (rkey.length() == 0 || rkey.length() > 14) {
		throw new std::string("abnormal key len");
	}
	memcpy(key, rkey.c_str(), rkey.length());
	this->survivalTime = time;
}
