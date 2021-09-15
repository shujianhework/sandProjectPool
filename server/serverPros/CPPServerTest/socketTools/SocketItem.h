#pragma once
#include "../base/SObject.h"
#include <string>
#include <vector>

class SocketItem :public SObject {
	unsigned char nextmaxlen;//std::vector �´���������buff���������ѹ�������ڴ�
	unsigned char yasuolenque;//ѹ����ȴ������ÿ��socket send һ�� �ۼ�+1,
	std::vector<SObject*> tempSendBuffs;//��ʱ�����б�
	SObject* recvBuffs;
	std::vector<SObject*> useSendBuffs;//�����б� ��ǰʹ���б�
public:
	std::string m_ip;
	int m_port;
	int m_state;
	std::string m_sockKey;
	std::string m_recyclingStr;
	
	
	SocketItem(std::string ip, int port);
	SocketItem();
	~SocketItem();

	//�Ѿ���������Ϣ�ķ���˳�� �п��ܵ�������������һֱ�޷�����
	//write socketManage�ⲿ�߼�д�����ݽ�����ʱ���棨luaЭ������ )
	//get (idx > 0) socket �ܹ���ȡ��ʱ����÷��͸�socket  ( idx == 0 ) socket �յ���Ϣ��ʱ�����������׷����Ϻ��ٴ���ȥ�ڴ� ��������ְ���
	//onRecv socket �յ���Ϣ��ʱ�� �������ݵ�idx = 0
	//clearbuff() idx > 0 ������͵����ݻ��� �������� >>>
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