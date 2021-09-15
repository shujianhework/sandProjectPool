#pragma once
#include "../InstanceManages.h"
#include "../socketTools/SocketItem.h"
#include <iostream>

//����buff������
// 
//1 ����Manage������֮������ⲿ�������ö��γ���Թ̶� �߻��������ݶ��γ�  GM ��̨���õ�... ���͵�������������ͻ���ʹ�� G_Data[key] = SObject ��ʽ����
//2 ��ʱ�������� ���û�ģ����γ������������ GM ��̨�����ض��������ݵ�һϵ�� ������ʱ�������ں����� �������� h���Զ�����
//3 ��������  ���ս����֮������� ����socket����ո�buff

class SocketManage :INSTANCEITEM
{
	void clear(bool isPrv);
public:
	
	
	enum NotifyEventName
	{
		S_ACCEPT,
		S_RECV,
		S_CLOSE,
		S_CONNECTERROR,
		S_ERROR,
		S_SENDEND,
	};
	struct shareBuff {
		unsigned int len;
		unsigned char* buff;
	};
	std::map<std::string, SocketItem*> pool;
	
	std::map<std::string, shareBuff*> shareBuffPool;
public:
	void clear() {
		clear(true);
	}
	virtual void init();
	virtual void onExit() {}
	SocketManage();
	~SocketManage();
	bool startServer(int port, int listNum);
	std::string connect(std::string ip, int port);
	void close(std::string key);
	bool send(std::string key, void* p, const unsigned long len);
	bool notifyEvent(std::string key, NotifyEventName eventType,void *p,int len);
	bool eraseShare(std::string key);
	std::string addSharePool(const unsigned char* buff, const unsigned int len);
	inline bool isExist(std::string key) {
		return shareBuffPool.find(key) != shareBuffPool.end();
	}
	inline unsigned char* getShareData(std::string key, unsigned int& len) {
		auto iter = shareBuffPool.find(key);
		len = 0;
		if (iter == shareBuffPool.end())
			return NULL;
		len = iter->second->len;
		return iter->second->buff;
	}
};

