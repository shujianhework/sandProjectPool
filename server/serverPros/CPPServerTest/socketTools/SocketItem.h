#pragma once
#include "../base/SObject.h"
#include <string>
#include <vector>

class SocketItem :public SObject {
	unsigned char nextmaxlen;//std::vector 下次期望发送buff最大数量，压缩空闲内存
	unsigned char yasuolenque;//压缩冷却计数，每次socket send 一次 累计+1,
	std::vector<SObject*> tempSendBuffs;//临时发送列表
	SObject* recvBuffs;
	std::vector<SObject*> useSendBuffs;//发送列表 当前使用列表
public:
	std::string m_ip;
	int m_port;
	int m_state;
	std::string m_sockKey;
	std::string m_recyclingStr;
	
	
	SocketItem(std::string ip, int port);
	SocketItem();
	~SocketItem();

	//已经扰乱了消息的发送顺序 有可能导致数组后边数据一直无法发送
	//write socketManage外部逻辑写入数据进入临时缓存（lua协议数据 )
	//get (idx > 0) socket 能够读取的时候调用发送给socket  ( idx == 0 ) socket 收到消息的时候想这个缓存追加完毕后再次拉去内存 ，解决被分包，
	//onRecv socket 收到消息的时候 推送数据到idx = 0
	//clearbuff() idx > 0 清除发送的数据缓存 额外数据 >>>
	bool local2socket(unsigned char* p, unsigned int len, bool isShare);
	inline bool write(unsigned char* p, unsigned int len, bool isShare) {
		return local2socket(p,len,isShare);
	}
	//bool swapAppend();
	unsigned char* getBuffsIdxData(int idx, unsigned int& len);
	inline unsigned char* get(int idx, unsigned int& len) {
		return getBuffsIdxData(idx, len);
	}
	bool resetRecvBuff(unsigned char* buff, unsigned int len);
	void onRecv(unsigned char* p, unsigned int len);
	void clearBuff(int idx);
	void swapSendVector();
	void close();
	void onClose();
};