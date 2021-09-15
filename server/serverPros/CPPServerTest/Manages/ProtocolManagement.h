#pragma once
#include "../base/SObject.h"
#include "../InstanceManages.h"
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
class ProtocolManagement :INSTANCEITEM
{
private:
	std::string passkey;
public:
	ProtocolManagement() {
		INSTANCECPPMAKE(ProtocolManagement);
		srand((unsigned int)time(NULL));
		passkey = "";
	}
	~ProtocolManagement();
	struct ProtocolItem {
		std::string m_key;
		unsigned int m_cmdId;
		unsigned int m_len;
		unsigned char* m_buff;
		ProtocolItem(std::string key, unsigned int cmdid);
		ProtocolItem(std::string key, unsigned int cmdid, unsigned char* buff, unsigned int len);
		~ProtocolItem() {
			if (m_buff != NULL)
				delete m_buff;
			m_buff = NULL;
		}
	};
	std::queue<ProtocolItem*> pool;
	unsigned int passOrderIndex;
	bool encodePass(const char* ptr, const unsigned int len, std::string& ret,unsigned short &dypass);
	bool decodePass(const char* ptr, const unsigned int len, std::string& ret,unsigned short dypass);
public:
	virtual void init();
	virtual void onExit() {}
	void setPassKey(std::string pass);
	void clear(std::string key) {
		std::mutex mt;
		mt.lock();
		while (pool.size() > 0) {
			auto pi = pool.front();
			if (pi != NULL) {
				delete pi;
				pi = NULL;
			}
		}
		mt.unlock();
		return;
	}
	unsigned int decode(std::string key, unsigned char *p1,const unsigned int size,int &errFlg);
	unsigned char* encode(unsigned int protocolId,unsigned char *src,const unsigned int srclen,unsigned int &objlen);
	inline bool getMsg(ProtocolItem *& item) {
		bool ret = false;
		if (pool.size() > 0) {
			std::mutex mt;
			mt.lock();
			if (pool.empty() == false) {
				item = pool.front();
				pool.pop();
				ret = true;
			}
			mt.unlock();
		}
		return ret;
	}
};

