#include "ThreadManagePool.h"

void ThreadManagePool::initThreadId()
{

}

bool ThreadManagePool::start(ThreadBase* tbs, bool isMain, std::string keyname)
{
    if (tbs == NULL)
        return false;
    if (keyname == "") {
        
    }
    else {
        auto iter = LogicHashThread.find(keyname);
        if (iter != LogicHashThread.end()) {
            return false;
        }
    }
    return false;
}

bool ThreadManagePool::exit(ThreadBase* tbs)
{
    return false;
}

bool ThreadManagePool::exit(std::string keyname)
{
    return false;
}

bool ThreadManagePool::clear()
{
    return false;
}

bool ThreadManagePool::post2ThreadData(std::string keyname, void* ptr, int len, bool isStack)
{
    return false;
}
