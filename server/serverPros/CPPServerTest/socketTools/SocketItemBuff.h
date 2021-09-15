#pragma once
#include "../base/SObject.h"
//除了SHARE  DELAYED_DELETE 不允许保存加密后的数据
#define SOCKETITEMBUFFDATASTACKSIZE 48
class SocketItemBuff :public SObject {
public:
	enum SocketBuffType
	{
		UNDEFINE = 0,
		SHARE,//共享
		DELAYED_DELETE,//临时共享数据
		SEND_DELETE,//发送后删除
		MINI_DATA,
	} m_sbt;
	enum SocketStreamDir {
		NODIR,
		RECV,
		SENDER
	}m_buffdir;
	union {
		struct {
			unsigned int len;
			unsigned int maxlen;
			unsigned char* buff;
		}m_send_delete;
		char m_delayed_delete[SOCKETITEMBUFFDATASTACKSIZE];//RecyclingCenterManage 里面的key
		char m_share_data[SOCKETITEMBUFFDATASTACKSIZE];//G_Data中的key
		struct {
			unsigned int len;
			unsigned char buff[SOCKETITEMBUFFDATASTACKSIZE - sizeof(unsigned int)];
		}m_mini_data;//mini数据不额外new 空间
	}m_data;
	SocketItemBuff();
	virtual ~SocketItemBuff();
	bool clear();
	bool append(unsigned char* p, unsigned int len);//接受数据后直接填充进来
	bool resetRecvBuff(unsigned char *p,unsigned int len);
	bool sendData(unsigned char* p, unsigned int len, bool isShare);
	const unsigned char* getdata(unsigned int& len);
	inline bool isEmpty() {
		return UNDEFINE == m_sbt;
	}
};