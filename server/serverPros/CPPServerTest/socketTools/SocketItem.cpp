#include "SocketItem.h"
#include "SocketItemBuff.h"
#include <mutex>
SocketItem::SocketItem(std::string ip, int port) :m_state(0), m_ip(ip), m_port(port), m_recyclingStr(""), m_sockKey("") {
	nextmaxlen = 10;
	yasuolenque = 0;
	recvBuffs = NULL;
	useSendBuffs.clear();
	tempSendBuffs.clear();
}
SocketItem::SocketItem() : m_state(0) {
	m_ip = "";
	m_port = 0;
	m_recyclingStr = "";
	m_sockKey = "";
	nextmaxlen = 10;
	yasuolenque = 0;
	recvBuffs = NULL;
	useSendBuffs.clear();
	tempSendBuffs.clear();
}
SocketItem::~SocketItem() {
	m_state = -2;
	for(int i = 0;i < tempSendBuffs.size();i++)
	{
		SocketItemBuff* sib = (SocketItemBuff*)tempSendBuffs[i];
		if(sib != NULL)
			sib->clear();
	}
	tempSendBuffs.clear();
	for (int i = 0; i < useSendBuffs.size(); i++)
	{
		SocketItemBuff* sib = (SocketItemBuff*)useSendBuffs[i];
		if (sib != NULL)
			sib->clear();
	}
	useSendBuffs.clear();
}
//以后针对这个升级
bool SocketItem::local2socket(unsigned char* p, unsigned int len, bool isShare)
{

	if (m_state > 0) {
		SocketItemBuff* sib = new SocketItemBuff();
		sib->sendData(p, len, isShare);
		tempSendBuffs.push_back(sib);
		return true;
	}
	return false;
	
}
unsigned char* SocketItem::getBuffsIdxData(int idx, unsigned int& len)
{
	len = 0;
	if (m_state <= 0)
		return NULL;
	if (idx == 0)
	{
		return (unsigned char*)((SocketItemBuff*)recvBuffs)->getdata(len);
	}
	else if (idx <= useSendBuffs.size()) {
		return (unsigned char*)((SocketItemBuff*)useSendBuffs[idx-1])->getdata(len);
	}
	return NULL;
}
bool SocketItem::resetRecvBuff(unsigned char* buff, unsigned int len)
{
	if (m_state <= 0) {
		return ((SocketItemBuff*)recvBuffs)->resetRecvBuff(NULL, 0);
	}
	else {
		return ((SocketItemBuff*)recvBuffs)->resetRecvBuff(buff, len);
	}
	return false;
}
void SocketItem::onRecv(unsigned char* p, unsigned int len)
{
	if (m_state > 0) {
		if (recvBuffs == NULL)
			recvBuffs = new SocketItemBuff();
		SocketItemBuff* sib2 = (SocketItemBuff*)recvBuffs;
		sib2->append(p, len);
	}
}
void SocketItem::clearBuff(int idx)
{
	if (idx == 0) {
		SocketItemBuff* sib2 = (SocketItemBuff*)recvBuffs;
		sib2->clear();
	}
	else if (idx > 0 && (idx - 1) < useSendBuffs.size()) {
		SocketItemBuff* sib2 = (SocketItemBuff*)useSendBuffs[idx - 1];
		sib2->clear();
	}
	else if (idx == -1) {
		
		std::mutex mt;
		mt.lock();
		for (int i = 0; i < useSendBuffs.size(); i++) {
			SocketItemBuff* sib2 = (SocketItemBuff*)useSendBuffs[i];
			sib2->clear();
		}
		mt.unlock();
		//useSendBuffs.clear();
	}
}
void SocketItem::swapSendVector()
{
	if (tempSendBuffs.size() == 0) {
		return;
	}
	std::mutex mt;
	mt.lock();
	int size = useSendBuffs.size();
	if (useSendBuffs[size - 1] == NULL) {
		useSendBuffs.clear();
	}
	else {
		while (useSendBuffs.size() > 0) {
			SocketItemBuff* sib = (SocketItemBuff*)useSendBuffs[0];
			if (sib != NULL)
				break;
			useSendBuffs.erase(useSendBuffs.begin());

		}
	}
	for (int i = 0; i < tempSendBuffs.size(); i++) {
		useSendBuffs.push_back(tempSendBuffs[i]);
	}
	tempSendBuffs.clear();
	mt.unlock();
}
void SocketItem::close() {
}
void SocketItem::onClose() {
	clearBuff(-2);
	clearBuff(0);
}