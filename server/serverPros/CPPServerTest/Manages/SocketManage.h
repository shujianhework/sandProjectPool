#pragma once
#include "../InstanceManages.h"
#include "../socketTools/SocketItem.h"
#include <iostream>

//发送buff分三级
// 
//1 共享Manage创建好之后根据外部数据配置而形成相对固定 策划配置数据而形成  GM 后台配置等... 推送到其他服务器或客户端使用 G_Data[key] = SObject 方式保存
//2 临时共享数据 配置或模板而形成针对特性数据 GM 后台配置特定区域数据等一系列 创建后定时生存周期后销毁 参数传入 h后自动销毁
//3 特有数据  玩家战力表之类的数据 放入socket后清空该buff

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

