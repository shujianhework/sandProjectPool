#include "ProtocolManagement.h"
#define MAXSocketProtocolDataModelPTR (300*1024)
#include "zlibManage.h"
#include "SHelperManage.h"
#include <iostream>
enum SocketProtocolExMsgFlg
{
	ZIP = 0,
	PASS = 1,
	DYPASS = 2,
	DYPASSLEN = 12,
	CYC = 15,
	CYCLEN = 16,
};
class SocketProtocolDataModel {//收发数据的模型

public:


	unsigned int protocolId;
	unsigned int len;
	//0--25 校验码  26 加密bool 27 压缩
	unsigned int exMsg;
	//static 
		unsigned char* p;

}ZEOR_SocketProtocolDataModel;
//unsigned char* SocketProtocolDataModel::p = NULL;
ProtocolManagement::~ProtocolManagement()
{
	/*delete SocketProtocolDataModel::p;
	SocketProtocolDataModel::p = NULL;*/
}

bool ProtocolManagement::encodePass(const char* ptr, const unsigned int len, std::string& ret, unsigned short& dykey1)
{
	if (len == 0)
		return false;
	char* ptr1 = new char[len + 16];
	memset(ptr1, 0, len + 16);
	unsigned int offset = 0;
	bool passret = GETINSTANCEMANAGE(SHelperManage)->passEncode((unsigned char*)ptr, len, dykey1, [&](char* p, unsigned int len2) {
		memcpy(&ptr1[offset], p, len2);
		offset += len2;
	});
	ptr1[offset] = 0;
	ret = std::string(ptr1, offset);
	delete ptr1;
	ptr1 = NULL;
	return passret;
}

bool ProtocolManagement::decodePass(const char* ptr, const unsigned int len, std::string& ret, unsigned short dykey)
{
	if (len == 0)
		return false;
	char* ptr1 = new char[(unsigned int)(len + 16)];
	memset(ptr1, 0, (unsigned int)(len + 16));
	unsigned int offset = 0;
	bool passret = GETINSTANCEMANAGE(SHelperManage)->passDecode((unsigned char*)ptr, len, dykey, [&](char* p, unsigned int len2) {
		memcpy(&ptr1[offset], p, len2);
		offset += len2;
		});
	ptr1[offset] = 0;
	ret = std::string(ptr1, offset);
	delete[] ptr1;
	ptr1 = NULL;
	return passret;
}

void ProtocolManagement::init(){
	passOrderIndex = 0;
	//SocketProtocolDataModel::p = new unsigned char[MAXSocketProtocolDataModelPTR];
}

void ProtocolManagement::setPassKey(std::string pass)
{
	unsigned int nowlen = pass.length();
	if (nowlen == 0) {
		return;
	}
	if (this->passkey.length() > 0) {
		return;
	}
	char* p = (char*)pass.c_str();
	if (nowlen < 5) {
		char arr[4] = "";
		std::string temp = "";
		for (size_t i = 0; i < nowlen; i++)
		{
			sprintf(arr, "%d", (p[i]+10248));
			if (arr[0] < 5)
				arr[0] = 0xf1;
			temp = temp + arr;
		}
		nowlen = temp.length();
		pass = temp;
		p = (char*)pass.c_str();
	}

	if (nowlen < 35) {

		pass = pass + "ProtocolManagement::setPassKey";
		nowlen = pass.length();
		p = (char*)pass.c_str();
		char arr[100] = "";

		for (int i = 0; i < nowlen/2; i++)
		{
			arr[i * 2] = p[i * 2 + 1];
			arr[i * 2 + 1] = p[i * 2];
		}
		pass = arr;
	}
	else if (nowlen > 256) {
		nowlen = 256;
		char arr[256] = "";

		for (int i = 0; i < nowlen / 2; i++)
		{
			arr[i * 2] = p[i * 2 + 1]+2;
			unsigned char c = p[i * 2];
			c = c - (c / 100);
			if (c == 0)
				c = 5;
			arr[i * 2 + 1] = c;
		}
		pass = arr;
	}
	this->passkey = pass;
	GETINSTANCEMANAGE(ProtocolManagement)->setPassKey(passkey);
}

//protocolId len exMsg 
//解密段落 。。。
unsigned int ProtocolManagement::decode(std::string key,unsigned char* p1, const unsigned int size,int& errFlg)
{
	unsigned int ret = size;
	std::vector<ProtocolItem*> tempItems = {};
	const unsigned int miniBuffSize = sizeof(SocketProtocolDataModel) - 4;
	while (true) {
		if (ret < miniBuffSize) {
			goto lockinsert;
		}
		SocketProtocolDataModel* SPD = (SocketProtocolDataModel*)p1;
		if (SPD->protocolId > 0 && (SPD->len >= 0 && SPD->len < MAXSocketProtocolDataModelPTR)) {
			if (SPD->len == 0) {
				if (SPD->exMsg != 0) {
					errFlg = 1;
					goto lockinsert;
				}
				tempItems.push_back(new ProtocolItem(key, SPD->protocolId));
				ret = ret - miniBuffSize;
				p1 += miniBuffSize;
				continue;
			}
			//无法校验 ，后续成熟直接抛弃，现在兼容
			else if (SPD->exMsg == 0) {

				if (ret < SPD->len)
					goto lockinsert;

				tempItems.push_back(new ProtocolItem(key, SPD->protocolId,&p1[miniBuffSize],SPD->len));
				ret = ret - miniBuffSize - SPD->len;
				p1 += SPD->len;
				p1 += miniBuffSize;
				continue;
			}
			else {
				
				//校验数据是否压缩1 加密2 收尾字符是否正常
				if(ret < SPD->len)
					goto lockinsert;

				
				//先解密 再解压
				unsigned int dypass = 0;
				unsigned int cyc = 0;
				SHelperManage* sm = GETINSTANCEMANAGE(SHelperManage);
				sm->setTempLong(SPD->exMsg);
				int isPass = sm->isTempLongBit(SocketProtocolExMsgFlg::PASS);
				int isZip = sm->isTempLongBit(SocketProtocolExMsgFlg::ZIP);
				sm->getTempLongBitLen(SocketProtocolExMsgFlg::DYPASS, SocketProtocolExMsgFlg::DYPASSLEN, dypass);
				sm->getTempLongBitLen(SocketProtocolExMsgFlg::CYC, SocketProtocolExMsgFlg::CYCLEN, cyc);
				if (cyc > 0) {
					const char* srcDataAddr = (char*)&p1[miniBuffSize];
					unsigned int dataLen = SPD->len;
					unsigned int cyc1 = dataLen;
					for (int i = 0; i < dataLen; i++) {
						cyc1 = cyc1 + srcDataAddr[i];
						if (cyc1 < 300)
							cyc1 = 300;
						cyc1 = cyc1 - srcDataAddr[i + dataLen - 2];
						if (cyc1 > 0xffffD) {
							cyc1 = 359;
						}
					}
					if (cyc1 != cyc)//数据不合法
					{
						ret = ret - miniBuffSize - SPD->len;
						p1 += SPD->len;
						p1 += miniBuffSize;
						continue;
					}	
				}
				std::string str = "";
				if (isPass == 1) {
					if (decodePass((char*)&p1[miniBuffSize], SPD->len, str, dypass) == false) {//不合法先跳过，后边直接断开链接
						ret = ret - miniBuffSize - SPD->len;
						p1 += SPD->len;
						p1 += miniBuffSize;
						continue;
					}
				}
				else {
					str = std::string((char*)&p1[miniBuffSize], SPD->len);
				}
				if (isZip == 1) {
					std::string ladata = "";
					if (zlibManage::DecompressString(str.c_str(), str.size(), ladata) != 0) {//不合法先跳过
						str = ladata;
					}
				}
				//以上暂时不考虑
				tempItems.push_back(new ProtocolItem(key, SPD->protocolId, (unsigned char*)str.c_str(), str.size()));
				ret = ret - miniBuffSize - SPD->len;
				p1 += SPD->len;
				p1 += miniBuffSize;
				continue;
			}
		}
		else {
			//消息无效
			errFlg = 2;
			goto lockinsert;
		}
	}
lockinsert:
	if (tempItems.size() < 0) {
		return ret;
	}
	std::mutex mt;
	mt.lock();
	for (int i = 0; i < tempItems.size(); i++) {
		this->pool.push(tempItems[i]);
	}
	tempItems.clear();
	mt.unlock();
	return ret;
	
}

unsigned char* ProtocolManagement::encode(unsigned int protocolId,unsigned char* src, const unsigned int srclen, unsigned int& objlen)
{
	objlen = 0;
	if (protocolId == 0) {
		return NULL;
	}
	static unsigned char* tempBuff = new unsigned char[MAXSocketProtocolDataModelPTR];
	SocketProtocolDataModel* SPM = (SocketProtocolDataModel*)tempBuff;
	SPM->protocolId = protocolId;
	SPM->len = srclen;
	SPM->exMsg = 0;

	if (src == NULL)
	{
		if(srclen > 0){
			objlen = 1;
			return NULL;
		}
		objlen = 12;
		return tempBuff;		
	}
	unsigned char* tempBuffData = &tempBuff[sizeof(SocketProtocolDataModel)-4];
	std::string compress = "";
	if (srclen > 1024) {
		if (zlibManage::CompressString((char*)src, srclen, compress, -1) == 0) {
			if (compress.size() >= srclen){
				compress = "";
			}
		}
	}
	SHelperManage* sm = GETINSTANCEMANAGE(SHelperManage);
	sm->setTempLong(0);
	//压缩标记
	if (compress.size() > 0) {
		memcpy(tempBuffData, compress.c_str(), compress.size());
		sm->setTempLongBit(SocketProtocolExMsgFlg::ZIP, 1);
	}
	else {
		memcpy(tempBuffData, src, srclen);
		tempBuffData[srclen] = 0;
		sm->setTempLongBit(SocketProtocolExMsgFlg::ZIP, 0);
	}
	//加密标记
	std::string passdata = "";
	unsigned short dypass = 0;
	if (this->passkey.size() > 0 && this->encodePass((char*)tempBuffData, srclen, passdata, dypass)) {
		sm->setTempLongBit(SocketProtocolExMsgFlg::PASS, 1);
		sm->setTempLongBitLen(SocketProtocolExMsgFlg::DYPASS, SocketProtocolExMsgFlg::DYPASSLEN, dypass);
	}
	else {
		sm->setTempLongBit(SocketProtocolExMsgFlg::PASS, 0);
		sm->setTempLongBitLen(SocketProtocolExMsgFlg::DYPASS, SocketProtocolExMsgFlg::DYPASSLEN, 0);
		passdata = std::string((char*)tempBuffData, srclen);
	}
	const char* passaddr = passdata.c_str();
	unsigned int passaddrlen = passdata.length();
	unsigned int cyc = passaddrlen;
	for (int i = 0; i < passaddrlen; i++){
		cyc = cyc + passaddr[i];
		if (cyc < 300)
			cyc = 300;
		cyc = cyc - passaddr[i + passaddrlen - 2];
		if (cyc > 0xffffD) {
			cyc = 359;
		}
	}
	sm->setTempLongBitLen(SocketProtocolExMsgFlg::CYC, SocketProtocolExMsgFlg::CYCLEN, cyc);
	SPM->exMsg = sm->getTempLong();
	SPM->len = passdata.length();
	memcpy(tempBuffData, passdata.c_str(), passdata.length());
	objlen = sizeof(SocketProtocolDataModel) - 4 + passdata.length();
	return tempBuff;
}

ProtocolManagement::ProtocolItem::ProtocolItem(std::string key, unsigned int cmdid)
	: m_key(key),m_cmdId(cmdid),m_buff(NULL),m_len(0)
{

}

ProtocolManagement::ProtocolItem::ProtocolItem(std::string key, unsigned int cmdid, unsigned char* buff, unsigned int len)
	: m_key(key), m_cmdId(cmdid), m_buff(NULL), m_len(0)
{
	if (len > 0) {
		m_buff = new unsigned char[len];
		memcpy(m_buff, buff, len);
		m_len = len;
	}
}
