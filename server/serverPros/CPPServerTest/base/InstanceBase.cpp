
#include <iostream>
#include <string>
#include "InstanceBase.h"
#include "../InstanceManages.h"
bool InstanceManages::InstanceBase::insert(InstanceBase* item, std::string name) {

	std::cout << name << std::endl;
	InstanceManages* im = InstanceManages::getInstance();
	auto prve = im->pool.find(name);
	if (prve != im->pool.end()) {
		throw std::string("InstanceBase Child Class Only unique objects can be generated and bound for management");
		return false;
	}
	im->pool.insert(std::make_pair(name, this));
	return true;

}