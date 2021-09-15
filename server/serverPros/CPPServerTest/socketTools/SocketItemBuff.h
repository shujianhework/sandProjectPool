#pragma once
#include "../base/SObject.h"
//����SHARE  DELAYED_DELETE ����������ܺ������
#define SOCKETITEMBUFFDATASTACKSIZE 48
class SocketItemBuff :public SObject {
public:
	enum SocketBuffType
	{
		UNDEFINE = 0,
		SHARE,//����
		DELAYED_DELETE,//��ʱ��������
		SEND_DELETE,//���ͺ�ɾ��
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
		char m_delayed_delete[SOCKETITEMBUFFDATASTACKSIZE];//RecyclingCenterManage �����key
		char m_share_data[SOCKETITEMBUFFDATASTACKSIZE];//G_Data�е�key
		struct {
			unsigned int len;
			unsigned char buff[SOCKETITEMBUFFDATASTACKSIZE - sizeof(unsigned int)];
		}m_mini_data;//mini���ݲ�����new �ռ�
	}m_data;
	SocketItemBuff();
	virtual ~SocketItemBuff();
	bool clear();
	bool append(unsigned char* p, unsigned int len);//�������ݺ�ֱ��������
	bool resetRecvBuff(unsigned char *p,unsigned int len);
	bool sendData(unsigned char* p, unsigned int len, bool isShare);
	const unsigned char* getdata(unsigned int& len);
	inline bool isEmpty() {
		return UNDEFINE == m_sbt;
	}
};