#pragma once
#include "../InstanceManages.h"
#include "../base/ThreadBase.h"
class ThreadManagePool :INSTANCEITEM{
	std::map<std::string, ThreadBase* > LogicHashThread;
	std::vector<ThreadBase* > LogicArrThread;
	void initThreadId();
public:
	ThreadManagePool() {
		LogicHashThread = {};
		LogicArrThread = {};
		INSTANCECPPMAKE(ThreadManagePool);
		initThreadId();
	}
	~ThreadManagePool() {
	}
	//name == "" ==> ��֧�ֱ�ת��
	//name == 
	bool start(ThreadBase *tbs,bool isMain = false,std::string keyname = "");
	bool exit(ThreadBase* tbs);
	bool exit(std::string keyname);
	bool clear();
	bool post2ThreadData(std::string keyname,void *ptr,int len,bool isStack);

};

