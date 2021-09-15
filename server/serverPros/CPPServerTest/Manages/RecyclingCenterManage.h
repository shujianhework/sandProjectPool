#pragma once
#include "../InstanceManages.h"
#include "../platform/PlatformBrid.h"
#include <iostream>
//����ǻ��չ�����
//1 push ʱ��ָ����������Զ�ɾ�� (0 --- 3h) 0 ��ʾ��һ֡��ɾ��
//2 erase �����Ƴ����ٵȴ�ʱ�䵽��
//3 pop �ӹ������Ƴ�ָ��key������Լ�����
//4 �������˳���ʱ��ֱ��ɾ�����еĶ����ٵȴ�

class RecyclingCenterManage :INSTANCEITEM
{

	class RecyclingItem :public SObject {

		char key[15];//RecycAddr
		unsigned survivalTime;
	public:
		SObject* obj;
		RecyclingItem(std::string rkey, unsigned time);
		virtual bool sub(unsigned int value) {
			if (survivalTime == 0)
				return true;
			if(survivalTime > value){
				survivalTime -= value;
				return false;
			}
			survivalTime = 0;
			return true;
		}
	};
	std::map<std::string, RecyclingItem*> pool;
	void clear(bool);
public:
	struct RecyclingCountItem :public RecyclingItem {
		unsigned int cout;
	public:
		RecyclingCountItem(std::string rkey):RecyclingItem(rkey,1),addr(NULL),len(0) {
			cout = 1;
		}
		unsigned char* addr;
		unsigned int len;
		void retain() {
			cout++;
		}
		void release() {
			cout--;
		}
		virtual bool sub(unsigned int value) {
			return cout == 0;
		}
	};
	RecyclingCenterManage() {
		INSTANCECPPMAKE(RecyclingCenterManage);
	}
	void init();
	std::string push(SObject* obj,unsigned long time);
	std::string push(const char* addr, unsigned long len);
	bool erase(std::string key);
	bool pop(std::string key,SObject* &obj);
	bool pop(std::string key, unsigned char*& obj,unsigned int &len);
	bool peekCountItem(std::string key, unsigned char*& obj, unsigned int& len);
	bool swap(std::string key);
	inline void clear() {
		return clear(true);
	}
	inline bool isExist(std::string key) {
		return pool.find(key) != pool.end();
	}
};

