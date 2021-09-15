#pragma once
#include "../InstanceManages.h"
class MemberManage:INSTANCEITEM
{
	unsigned char* base;
	
public:
	MemberManage():base(NULL){
		if (INSTANCECPPMAKE(MemberManage) == true) {
			init();
		}
	}
	~MemberManage() {
	}
	virtual void init();
	virtual void uninit();
	virtual void onExit();
	void* malloc(int size);
	bool free(void*& p);
	int getRefcount(const void *p);
	bool addRefCount(void *p);
	bool autoRefCount(void* p);

	
};

