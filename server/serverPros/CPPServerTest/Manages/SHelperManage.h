#pragma once
#include "../InstanceManages.h"
#include <functional>
class SHelperManage : INSTANCEITEM
{
	unsigned long tempLong;
	unsigned char* tempBuff;
	unsigned long tempBuffLen;
public:
	void init() {

	}
	SHelperManage():tempBuff(NULL),tempBuffLen(0),tempLong(0) {
		INSTANCECPPMAKE(SHelperManage);
	}
	~SHelperManage();
	void setTempLong(unsigned long value) {
		tempLong = value;
	}
	unsigned long getTempLong() {
		return tempLong;
	}
	unsigned int isTempLongBit(unsigned int bit);
	bool setTempLongBit(unsigned int bit, bool flg);
	bool getTempLongBitLen(unsigned int bit, unsigned int len, unsigned int& ret);	
	bool setTempLongBitLen(unsigned int bit, unsigned int len, const unsigned int value);
	bool setPassKey(std::string key);
	bool passDecode(unsigned char *p,unsigned int len, const unsigned short mod, std::function<void(char *,unsigned int)> back);//º”√‹
	bool passEncode(unsigned char* p, unsigned int len,unsigned short &mod, std::function<void(char*, unsigned int)> back);//Ω‚√‹
	std::string showbin();	
};
