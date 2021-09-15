#pragma once
#include "base/SObject.h"
#include <cstddef>
#include <string>
#include <map>
#include <mutex>
#include "platform/PlatformBrid.h"
class InstanceManages :public SObject
{

	static InstanceManages* instance;
public:
	class InstanceBase :public SObject {
		protected:
			bool insert(InstanceBase *item,std::string name);
		protected:
			virtual void init()=0;
			virtual void uninit() {}
		public:
			virtual void onExit() {}
		public:
			virtual ~InstanceBase() {}
	};
private:
	std::map<std::string, InstanceBase*> pool;

private:

	void init();
	InstanceManages();
	~InstanceManages();

public:

	
	static InstanceManages* getInstance() {
		if (instance == NULL) {
			std::mutex mt;
			mt.lock();
			instance = new InstanceManages();
			instance->init();
			mt.unlock();
		}
		return instance;
	}
	static void destroy() {
		if (instance != NULL) {
			instance->onExit();
			S_Sleep(2000);
			delete instance;
			instance = NULL;
		}
	}
	virtual void onExit();
	
	template<typename T>
	T* getInstance(std::string str) {
		auto iter = pool.find(str);

		if (iter == pool.end())
		{
			T* t1 = new T();
			//pool.insert(std::make_pair(str, t1));
			return t1;
		}
		T* t = (T*)(iter->second);
		return t;
	}

};

#define INSTANCEITEM public InstanceManages::InstanceBase
#define GETINSTANCEMANAGE(className) InstanceManages::getInstance()->getInstance<className>(#className)
#define INSTANCECPPMAKE(className) this->insert(this,#className)