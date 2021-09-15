#include "../InstanceManages.h"
#include <iostream>
#include <vector>

InstanceManages* InstanceManages::instance = NULL;

void InstanceManages::init()
{
}
InstanceManages::InstanceManages() {
	pool.clear();
}
InstanceManages::~InstanceManages() {

}
void InstanceManages::onExit() {
	
	std::vector<std::string> names = {};
	for (auto iter = pool.begin(); iter != pool.end() ; iter++)
	{
		names.push_back(iter->first);
	}

	for (auto& name : names)
	{
		auto iter = pool.find(name);
		if (iter != pool.end()) {
			iter->second->onExit();
		}
	}
	for (auto& name : names)
	{
		auto iter = pool.find(name);
		if (iter != pool.end() && iter->second != NULL) {
			delete iter->second;
			iter->second = NULL;
		}
	}
}
