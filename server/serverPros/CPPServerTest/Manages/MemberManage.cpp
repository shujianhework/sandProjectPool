#include "MemberManage.h"

#define DYMEMBERMAXSIZE 0XFFFFFFFF

void MemberManage::init(){
    base = new unsigned char[DYMEMBERMAXSIZE];
}

void MemberManage::uninit(){
    if (base != NULL)
        delete base;
    base = NULL;
}

void MemberManage::onExit()
{
    if (base != NULL)
        delete base;
    base = NULL;
}

void* MemberManage::malloc(int size)
{
    return nullptr;
}

bool MemberManage::free(void*& p)
{
    return false;
}

int MemberManage::getRefcount(const void* p)
{
    return 0;
}

bool MemberManage::addRefCount(void* p)
{
    return false;
}

bool MemberManage::autoRefCount(void* p)
{
    return false;
}
