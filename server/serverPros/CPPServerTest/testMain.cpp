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
	const char* p = "IT֮�� 8 �� 8 ����Ϣ ƻ�����ܸոչ������µġ���ͯ��ȫ�����ܣ�ּ������Զ�ͯ�ı��������˾ٲ�û�еõ��㷺֧�֣������⵽���� 4000 �����֯�Լ����˵Ĺ������ԡ�\
		9to5 Mac �����ƣ�ƻ�����ܲ� Sebastian Marineau - Mes �ı���¼��ʾ���µı�����ʩ��һЩ�ˡ�������Ӱ�족�����ù�˾��������ƻ�����û���˽�ļᶨ��ŵ����\
		IT֮����������ƻ����ǰ���绤�ƣ�������������û��豸�ϲ��Ҷ�ͯ��Ű��ͼƬ�Ĺ��߻�����������˽�ĺ��š�\
		��7x - grE �� ��̩\
		��Ϊ��ͯ�����ƻ���һ���֣�ƻ���� iPhone �������豸�϶��û���ͼ������ϴ���ɨ�裬�Դ�ʶ���û��Ƿ񱣴�������������ʧ�ٺ���Ű��ͯ����(NCMEC) ���ݿ���ƥ���ͼ�����ȷ�ϣ�ƻ����֪ͨ NCMEC ���������ʻ���";
	std::string key = sm->addSharePool((const unsigned char*)p, strlen(p));
	const char* p1 = "������ҿ������ص�һ�ǣ��ֲ���֮�������������ճ����ɡ�\
		˯������������������Ӧ��ҹ���˾�ʱ������Ҫ���������������ñ����䵥��\
		��Ϊ����\
		����Զ��֪������һ��˲�佫Ҫ��������ľ��ա�\
		�����Ȼ����Σ���ޱȣ������˶��Ƚ��ع��š�\
		��Ծ������һ������û�У�ȴ��������̤���������ߵ����̡�\
		��ܰ��ʾ���������֣���������Ƥ������������Ʒ���������Ѳ�Ҫ�����";
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
		std::cout << "ִ�гɹ�" << std::endl;
	}else
		std::cout << "ִ��error" << std::endl;
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