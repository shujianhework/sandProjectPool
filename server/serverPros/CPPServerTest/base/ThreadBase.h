#pragma once
#include <queue>
#include <memory>

class ThreadBase
{
private:
	int state;
	int threadId;
	std::queue<void*> queues;
	void* paramPtr;
	unsigned int len;
public:
	ThreadBase();
	virtual ~ThreadBase() {}
	virtual void init() = 0;
	virtual void destroyed() = 0;
	virtual void warningMemory() = 0;
	virtual void onExit() = 0;
	virtual void push();
	virtual void pop();
	bool start(void* p1,unsigned int len);
	virtual bool onStart() = 0;
	static int threadStart(ThreadBase *tb);
};

