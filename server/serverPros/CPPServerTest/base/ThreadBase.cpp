#include "ThreadBase.h"
unsigned int offsetThread = 0x1fff03;
unsigned int offsetThreadMax = 0x2fffffff;
void ThreadBase::push()
{
}
void ThreadBase::pop()
{
}
bool ThreadBase::start(void* p1, unsigned int len)
{
    if (this->state == 0) {
        this->state = 1;
        this->paramPtr = p1;
        this->len = len;

        return true;
    }
    return false;

}

int ThreadBase::threadStart(ThreadBase* tb)
{
    return 0;
}

ThreadBase::ThreadBase():
    state(0), threadId(offsetThread), paramPtr(NULL),len(0)
{
    offsetThread++;
    
}
