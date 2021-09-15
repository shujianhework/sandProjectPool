#include "SocketItemBuff.h"
#include "../Manages/RecyclingCenterManage.h"
#include "../Manages/SocketManage.h"
#include <cstddef>
#include <string.h>

SocketItemBuff::SocketItemBuff() {
	m_buffdir = NODIR;
	m_sbt = UNDEFINE;
	memset(m_data.m_share_data, 0, sizeof(m_data));
}
SocketItemBuff::~SocketItemBuff() {
	switch (m_sbt)
	{
	case SocketItemBuff::UNDEFINE:
		break;
	case SocketItemBuff::SHARE:
	{
		if (strlen(this->m_data.m_share_data) > 0) {
			//GETINSTANCEMANAGE(SocketManage)->eraseShare(m_data.m_share_data);
		}
	}
		break;
	case SocketItemBuff::DELAYED_DELETE:
	{
		if (strlen(this->m_data.m_delayed_delete) > 0) {
			//GETINSTANCEMANAGE(RecyclingCenterManage)->erase(this->m_data.m_delayed_delete);
		}
	}
		break;
	case SocketItemBuff::SEND_DELETE:
		if (this->m_data.m_send_delete.len > 0) {
			delete this->m_data.m_send_delete.buff;
			memset(m_data.m_share_data, 0, sizeof(m_data));
		}
		break;
	default:
		break;
	}
}
//recv 只允许 new char 
bool SocketItemBuff::append(unsigned char* buff, unsigned int len)
{
	if (this->m_buffdir == SENDER || buff == NULL) {
		return false;
	}
	m_buffdir = RECV;
	int orgin = 0;
	if (m_sbt == SEND_DELETE) {
		orgin = m_data.m_send_delete.len;
		//缓存内存不足的时候 重新申请内存，并添加内容转移过来
		if ((orgin + len) >= m_data.m_send_delete.maxlen) {
			int maxlen = (orgin + len) + 512;
			if (maxlen > 300 * 1024) {
				//应该提示
			}
			unsigned char* p = new unsigned char[maxlen];
			if (p == NULL) {
				//内存获取失败
				return false;
			}
			memcpy(p, m_data.m_send_delete.buff, orgin);
			delete m_data.m_send_delete.buff;
			m_data.m_send_delete.buff = p;
			m_data.m_send_delete.maxlen = maxlen;
		}
		memcpy(&m_data.m_send_delete.buff[orgin], buff, len);
	}
}
bool SocketItemBuff::resetRecvBuff(unsigned char* buff, unsigned int len)
{
	if (this->m_buffdir == SENDER ) {
		return false;
	}
	m_buffdir = RECV;

	if (len == 0) {
		if (m_data.m_send_delete.maxlen == 0) {
			m_data.m_send_delete.buff = new unsigned char[64];
		}
		m_data.m_send_delete.buff[0] = 0;
		m_data.m_send_delete.len = 0;
		return true;
	}
	if (m_data.m_send_delete.maxlen / 2 < len && m_data.m_send_delete.maxlen > len) {
		std::mutex mt;
		memcpy(m_data.m_send_delete.buff, buff, len);
		m_data.m_send_delete.len = len;
		mt.unlock();
		return true;
	}
	unsigned char* p = new unsigned char[len];
	if (p == NULL)
		return false;
	std::mutex mt;
	memset(p, 0, len);
	memcpy(p, buff, len);
	delete m_data.m_send_delete.buff;
	m_data.m_send_delete.buff = p;
	m_data.m_send_delete.maxlen = len;
	m_data.m_send_delete.len = len;
	mt.unlock();
	return true;
}
bool SocketItemBuff::sendData(unsigned char* p, unsigned int len, bool isShare)
{
	if(RECV == m_buffdir)
		return false;

	if (len < (SOCKETITEMBUFFDATASTACKSIZE - sizeof(len)) && isShare == false) {
		
		m_sbt = MINI_DATA;
		m_buffdir = SENDER;
		memcpy(m_data.m_mini_data.buff, p, len);
		m_data.m_mini_data.len = len;
		return true;
	}
	
	if (isShare == false) {

		m_sbt = SEND_DELETE;
		if (m_data.m_send_delete.maxlen < len) {
			if (m_data.m_send_delete.buff != NULL) {
				int maxlen = len + 100;
				unsigned char* p = new unsigned char[maxlen];
				if (p == NULL)
					return false;
				m_data.m_send_delete.maxlen = maxlen;
				delete m_data.m_send_delete.buff;
				m_data.m_send_delete.buff = p;
			}
		}
		memcpy(m_data.m_send_delete.buff, p, len);
		m_data.m_send_delete.len = len;
		m_buffdir = SENDER;
		return true;
	}

	else if(strlen((char*)p) <= SOCKETITEMBUFFDATASTACKSIZE ) {
		std::string key = (char*)p;
		if (GETINSTANCEMANAGE(RecyclingCenterManage)->isExist(key)) {
			m_sbt = DELAYED_DELETE;
			memcpy(m_data.m_delayed_delete, p, len);
			m_buffdir = SENDER;
			return true;
		}
		else if (GETINSTANCEMANAGE(SocketManage)->isExist(key)) {
			m_sbt = SHARE;
			memcpy(m_data.m_share_data, p, len);
			m_buffdir = SENDER;
			return true;
		}
	}
	return false;
}
const unsigned char* SocketItemBuff::getdata(unsigned int& len)
{
	len = 0;
	if(NODIR == m_buffdir)
		return nullptr;

	
	if (RECV == m_buffdir) {
		len = m_data.m_send_delete.len;
		return m_data.m_send_delete.buff;
	}
	unsigned char* p1 = NULL;
	switch (m_sbt)
	{
	case SocketItemBuff::UNDEFINE:
		return NULL;
	case SocketItemBuff::SHARE: {
		return GETINSTANCEMANAGE(SocketManage)->getShareData(m_data.m_share_data, len);
	}
	case SocketItemBuff::DELAYED_DELETE:
	{
		if (GETINSTANCEMANAGE(RecyclingCenterManage)->peekCountItem(m_data.m_delayed_delete, p1, len))
			return p1;
	}break;
	case SocketItemBuff::SEND_DELETE:
	{
		len = m_data.m_send_delete.len;
		return m_data.m_send_delete.buff;
	}
	case SocketItemBuff::MINI_DATA:
		len = m_data.m_mini_data.len;
		return m_data.m_mini_data.buff;
	}
	return NULL;

}
bool SocketItemBuff::clear() {

	if (m_sbt == SocketBuffType::SEND_DELETE && m_buffdir == SENDER) {

		if (m_data.m_send_delete.buff != NULL) {
			delete m_data.m_send_delete.buff;
			memset(m_data.m_share_data, 0, sizeof(m_data));
		}
		m_sbt = SocketBuffType::UNDEFINE;
		return true;
	}
	else if (m_sbt == SocketBuffType::UNDEFINE) {
		return true;
	}
	else if (m_buffdir == SENDER) {
		return true;
	}
	return false;

}
