#include "testMain.h"
#include <Windows.h>
#include "InstanceManages.h"
#include "Manages/SocketManage.h"
#include "socketTools/SocketItem.h"
#include "socketTools/SocketItemBuff.h"
#include <zlib.h>
#include "Manages/zlibManage.h"
#include "Manages/SHelperManage.h"
#include "Manages/ProtocolManagement.h"
#include "../../cryptopp850/aes.h"

#include "Manages/LuaScriptManage.h"
#pragma comment(lib,"cryptlib.lib")
using namespace std;
void testSocket() {
	SocketManage* sm = GETINSTANCEMANAGE(SocketManage);
	const char* p = "IT之家 8 月 8 日消息 苹果本周刚刚公布了新的“儿童安全”功能，旨在扩大对儿童的保护。但此举并没有得到广泛支持，甚至遭到包括 4000 多家组织以及个人的公开反对。\
		9to5 Mac 报道称，苹果副总裁 Sebastian Marineau - Mes 的备忘录显示，新的保护措施让一些人“担心其影响”，但该公司将“保持苹果对用户隐私的坚定承诺”。\
		IT之家曾报道，苹果此前还辩护称，不相信这款在用户设备上查找儿童性虐待图片的工具会留下削弱隐私的后门。\
		：7x - grE · 中泰\
		作为儿童保护计划的一部分，苹果将 iPhone 和其他设备上对用户的图像进行上传和扫描，以此识别用户是否保存了与美国国家失踪和受虐儿童中心(NCMEC) 数据库中匹配的图像。如果确认，苹果将通知 NCMEC 并禁用其帐户。";
	std::string key = sm->addSharePool((const unsigned char*)p, strlen(p));
	const char* p1 = "当世界揭开它神秘的一角，恐怖随之溢出，诡异成了日常旋律。\
		睡梦中听到呼唤别轻易应答，夜深人静时尽量不要窥镜，出入电梯最好避免落单。\
		因为——\
		你永远不知道，下一个瞬间将要面对怎样的惊险。\
		世界忽然间变得危险无比，聪明人都稳健地苟着。\
		江跃开局连一条狗都没有，却阴差阳错踏上了逆行者的征程。\
		温馨提示：诡异入侵，披着玄幻皮的悬疑灵异作品，灵异书友不要错过。";
	std::string key1 = sm->addSharePool((const unsigned char*)p1, strlen(p1));

	SocketItemBuff sib;
	sib.sendData((unsigned char*)key.c_str(), key.length(), true);
	unsigned int plen = 0;
	const char* pp = (char*)sib.getdata(plen);
	std::cout << pp << std::endl;
	sib.sendData((unsigned char*)"2omlkfmsdjfosdkmfksdl", strlen("2omlkfmsdjfosdkmfksdl"), false);
	const char* pp1 = (char*)sib.getdata(plen);
	std::cout << pp1 << std::endl;
	sib.sendData((unsigned char*)key1.c_str(), key.length(), true);
	const char* pp2 = (char*)sib.getdata(plen);
	std::cout << pp2 << std::endl;
	sib.clear();
}
void testZip() {
	if (false) {
		//zlibManage::test1();
		return;
	}
	FILE* f = NULL;
	if (fopen_s(&f, "E:/testzip.txt", "rb") == 0) {
		std::cout << "fopen ok" << std::endl;
		if (f == NULL) {
			std::cout << "f == null" << std::endl;
			return;
		}
		fseek(f, 0, SEEK_END);
		long len = ftell(f);
		//long len = 16384+1;
		fseek(f, 0, SEEK_SET);
		char* p = new char[len+1];
		memset(p, 0, len + 1);
		unsigned int read = fread_s(p, len, sizeof(char), len, f);
		fclose(f);
		f = NULL;
		std::cout << "srclen = "<< len << std::endl;
		std::string str = "";
		int tempret = zlibManage::CompressString(p, len, str, -1);
		if (tempret == 0) {

			std::cout << "comlen = " << str.length() << std::endl;
			delete p;
			p = NULL;
			if (fopen_s(&f, "E:/testzip.zip", "wb") == 0) {
				std::cout << "fopen zip ok" << std::endl;
				if (f == NULL) {
					std::cout << "fopen zip f = null" << std::endl;
					return;
				}
				fwrite(str.c_str(), sizeof(char), str.size(), f);
				fclose(f);
				f = NULL;
				std::string str2 = "";
				if (zlibManage::DecompressString(str.c_str(), str.size(), str2) == 0) {
					std::cout << "decode len = " << str2.length() << std::endl;
					if (fopen_s(&f, "E:/testzip.unzip", "wb") == 0) {
						std::cout << "fopen unzip ok" << std::endl;
						if (f == NULL) {
							std::cout << "fopen unzip f = null" << std::endl;
							return;
						}
						fwrite(str2.c_str(), sizeof(char), str2.size(), f);
						fclose(f);
						f = NULL;
					}
				}
			}
		}
		else {

			delete p;
			p = NULL;
		}
		
	}
}
void testbin() {

	SHelperManage* sm = GETINSTANCEMANAGE(SHelperManage);
	sm->setTempLong(0);
	std::cout << sm->showbin() << std::endl;
	sm->setTempLongBit(3, true);
	sm->setTempLongBit(8, true);
	std::cout << sm->showbin() << std::endl;
	sm->setTempLongBitLen(10, 8, 126);
	std::cout << sm->showbin() << std::endl;
	sm->setTempLongBitLen(10, 8, 101);
	std::cout << sm->showbin() << std::endl;
	unsigned int temp = 0;
	sm->getTempLongBitLen(10, 8, temp);
	std::cout << temp << std::endl;
}
struct testItem {
	int a;
	double b;
	char arr[100];
	float f;
};
void testProtocolManage() {
	testItem ti = {12,14.56,"test this is a pb decode encodeAFA0",5140.89};
	auto pm = GETINSTANCEMANAGE(ProtocolManagement);
	pm->init();
	pm->setPassKey("People from Europe and the United States have been moving to the city, which is one of the United Arab Emirates. They say it is because the city follows a business as usual policy.");
	unsigned int bufflen = 0;
	char* p1 = ti.arr;
	std::cout << p1 << std::endl;
	unsigned char *buff = pm->encode(57892, (unsigned char*)p1, strlen(p1), bufflen);
	int errflg = 0;
	unsigned int ret =  pm->decode("sdfsd", buff, bufflen, errflg);
	std::cout << ret << std::endl;
	//pm->decode("sdf","",)
}
void testLua() {
	LuaScriptManage* LSM = GETINSTANCEMANAGE(LuaScriptManage);
	if (LSM->startFile("test.lua") && LSM->pcall(0)) {
		std::cout << "执行成功" << std::endl;
	}else
		std::cout << "执行error" << std::endl;
	return ;
}
int main(int argc, WCHAR* argv[]) 
{
	//SocketManage* sm = InstanceManages::getInstance()->getInstance<SocketManage>("SocketManage");
	//testbin();
	//testProtocolManage();
	testLua();
	InstanceManages::destroy();
	return 0;
}