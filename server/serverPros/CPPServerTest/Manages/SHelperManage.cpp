#include "SHelperManage.h"
#include "../../../cryptopp850/aes.h"
#pragma comment(lib,"cryptlib.lib")
CryptoPP::AESEncryption aesEncryptor;
CryptoPP::AESDecryption aesDecryptor;
bool passKeyIsInit = false;
SHelperManage::~SHelperManage() {
	if (tempBuff != NULL) {
		delete tempBuff;
		tempBuff = NULL;
	}
	tempBuffLen = 0;
	tempLong = 0;
}
unsigned int SHelperManage::isTempLongBit(unsigned int bit)
{

		if (bit > 31) {
			return 2;
		}

		if (tempLong == 0)
			return 0;

		if (tempLong & (1 << bit)) {
			return 1;
		}
		return 0;
}

bool SHelperManage::setTempLongBit(unsigned int bit, bool flg)
{

	if (bit > 31) {
		return false;
	}
	if (flg) {
		tempLong |= (1 << bit);
	}
	else
		tempLong &= (~(1 << bit));
	return true;
}

bool SHelperManage::getTempLongBitLen(unsigned int bit, unsigned int len, unsigned int& ret)
{

	if ((bit + len) > 31) {
		return false;
	}
	if (len == 0) {
		ret = 0;
		return true;
	}
	unsigned long temp = tempLong;
	ret = 0;
	if (bit > 0)
		temp = temp >> bit;

	ret = 0;
	for (unsigned int i = 0; i < len; i++)
	{
		if (temp & (1 << i)) {
			//ret |= (1 << i);
			ret = (ret << 1) + 1;
		}
		else {
			
			ret = ret << 1;
		}
	}
	return true;
}

bool SHelperManage::setTempLongBitLen(unsigned int bit, unsigned int len, const unsigned int value)
{
	//怎么判断value是否超出bit len
	if ((bit + len) > 31) {
		return false;
	}
	if (len == 0) {
		return false;
	}
	if (value >= (1 << len)) {
		return false;
	}
	//怎么判断是否超出?
	for (unsigned int i = 0; i < len; i++)
	{
		if (value & (1 << (len - i - 1))) {
			tempLong |= (1 << (i+bit));
		}
		else {
			tempLong &= (~(1 << (i+bit)));
		}
	}
	return true;
}

bool SHelperManage::setPassKey(std::string key)
{
	
	aesEncryptor.SetKey((CryptoPP::byte*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	aesDecryptor.SetKey((CryptoPP::byte*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	passKeyIsInit = true;
	return false;
}

bool SHelperManage::passDecode(unsigned char* p, unsigned int len, const unsigned short mod, std::function<void(char*, unsigned int)> back)
{
	if(passKeyIsInit == false)
		return false;

	char arr[CryptoPP::AES::DEFAULT_KEYLENGTH] = "";
	int pos = 0;
	int relaysize = 0;
	int cpsize = 0;
	unsigned char inBlock[CryptoPP::AES::DEFAULT_KEYLENGTH];
	unsigned char outBlock[CryptoPP::AES::DEFAULT_KEYLENGTH];
	unsigned char xorBlock[CryptoPP::AES::DEFAULT_KEYLENGTH] = "";
	memset(xorBlock, 0, CryptoPP::AES::DEFAULT_KEYLENGTH);
	do
	{
		relaysize = len - pos;
		cpsize = relaysize > CryptoPP::AES::DEFAULT_KEYLENGTH ? CryptoPP::AES::DEFAULT_KEYLENGTH : relaysize;
		memset(inBlock, 0, CryptoPP::AES::DEFAULT_KEYLENGTH);
		memset(outBlock, 0, CryptoPP::AES::DEFAULT_KEYLENGTH);
		memcpy(inBlock, &p[pos], cpsize);
		aesDecryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock); //加密
		if ((pos + cpsize) >= len && mod > 0) {
			outBlock[mod] = 0;
			back((char*)outBlock, mod);
		}
		else {
			back((char*)outBlock, CryptoPP::AES::DEFAULT_KEYLENGTH);
		}
		pos += cpsize;
	} while (pos < len);
	return true;

}

bool SHelperManage::passEncode(unsigned char* p, unsigned int len, unsigned short& mod, std::function<void(char*, unsigned int)> back)
{
	if (passKeyIsInit == false)
		return false;

	char arr[CryptoPP::AES::DEFAULT_KEYLENGTH] = "";
	int pos = 0;
	int relaysize = 0;
	int cpsize = 0;
	mod = (len % CryptoPP::AES::DEFAULT_KEYLENGTH) + 1;
	unsigned char inBlock[CryptoPP::AES::DEFAULT_KEYLENGTH];
	unsigned char outBlock[CryptoPP::AES::DEFAULT_KEYLENGTH];
	unsigned char xorBlock[CryptoPP::AES::DEFAULT_KEYLENGTH] = "";
	memset(xorBlock, 0, CryptoPP::AES::DEFAULT_KEYLENGTH);
	do
	{
		relaysize = len - pos;
		cpsize = relaysize > CryptoPP::AES::DEFAULT_KEYLENGTH ? CryptoPP::AES::DEFAULT_KEYLENGTH : relaysize;
		memset(inBlock, 0, CryptoPP::AES::DEFAULT_KEYLENGTH);
		memset(outBlock, 0, CryptoPP::AES::DEFAULT_KEYLENGTH);
		memcpy(inBlock, &p[pos], cpsize);
		aesEncryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock); //加密
		back((char*)outBlock, CryptoPP::AES::DEFAULT_KEYLENGTH);
		pos += cpsize;
	} while (pos < len);
	return true;

}


std::string SHelperManage::showbin()
{

	char arr[50] = "";
	memset(arr, 0, 50);
	int bit = 0;
	for (int i = 0; i < 32; i++,bit++) {
		if (tempLong & (1 << i)) {
			arr[bit] = '1';
		}
		else {
			arr[bit] = '0';
		}
		if (i % 4 == 3)
		{
			bit++;
			arr[bit] = ',';
		}
	}
	return arr;

}