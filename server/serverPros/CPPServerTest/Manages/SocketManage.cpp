#include "SocketManage.h"
#include "../platform/PlatformBrid.h"
#include <vector>
#include <functional>
#define downcast(bev_f) (&(bev_f)->bev.bev)
//#define BEV_LOCK(b) do {						\
//		struct bufferevent_private *locking =  BEV_UPCAST(b);	\
//		EVLOCK_LOCK(locking->lock, 0);				\
//	} while (0)
//
///** Internal: Release the lock (if any) on a bufferevent */
//#define BEV_UNLOCK(b) do {						\
//		struct bufferevent_private *locking =  BEV_UPCAST(b);	\
//		EVLOCK_UNLOCK(locking->lock, 0);			\
//	} while (0)

#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif
#ifdef _WIN32
#pragma comment(lib,"ws2_32.lib")
#endif
#include "../thirdPartyLibrarys/libeventsrc/event-internal.h"
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#pragma comment(lib,"libevent")
#pragma comment(lib,"libevent_core")
#pragma comment(lib,"libevent_extras")
#include "RecyclingCenterManage.h"
//class ServerAccept :public SocketManage::SocketItem {
//};
struct g_libEvents {
	struct event_base* base;
};
g_libEvents* g_libevents = NULL;
SocketManage::SocketManage(){
#ifdef _WIN32
	INSTANCECPPMAKE(SocketManage);
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#else
#endif
	g_libevents = new g_libEvents();
	g_libevents->base = event_base_new();
	shareBuffPool.clear();
}
SocketManage::~SocketManage() {
	event_base_free(g_libevents->base);
#ifdef _WIN32
	WSACleanup();
	std::mutex mt;
	mt.lock();
	for (auto item = shareBuffPool.begin(); item != shareBuffPool.end(); item++)
	{
		auto sharebuff = item->second;
		unsigned int len = sharebuff->len;
		if(len > 0){
			delete sharebuff->buff;
			sharebuff->buff = NULL;
		}
	}
	shareBuffPool.clear();
	mt.unlock();

#else
#endif
	
}
void SocketManage::init() {
	
	clear(true);
}
void SocketManage::clear(bool isPrv) {

	std::vector<std::string> keys;
	std::mutex mt;
	mt.lock();
	for (auto iter = pool.begin(); iter != pool.end(); iter++) {
		keys.push_back(iter->first);
	}
	for (int i = 0; i < keys.size(); i++)
	{
		auto iter = pool.find(keys[i]);

		RecyclingCenterManage* rcm = GETINSTANCEMANAGE(RecyclingCenterManage);
		std::string rkey = rcm->push(iter->second, 3);
		iter->second->close();
		if (rkey == "") {
			delete iter->second;
			iter->second = NULL;
		}
		else
			iter->second->m_recyclingStr = rkey;
		
		pool.erase(keys[i]);
	}
	mt.unlock();
	if (pool.size() > 0) {
		clear(true);
	}
	pool.clear();
}
static void conn_eventcb(struct bufferevent* bev, short events, void* user_data)
{
	SocketItem* si = (SocketItem*)user_data;
	std::string str = "connection close";
	if (events & BEV_EVENT_EOF) {
		
		
		str = "Connection closed.";
	}
	else if (events & BEV_EVENT_ERROR) {
		str = "Got an error on the connection: %s";
	}
	
	GETINSTANCEMANAGE(SocketManage)->notifyEvent(si->m_sockKey, SocketManage::NotifyEventName::S_CONNECTERROR, (void*)str.c_str(), str.length());
	
	bufferevent_free(bev);
}
#include "ProtocolManagement.h"
static unsigned int socketData2ProtocolData(std::string key,unsigned char *ptr,const unsigned int len,int &errFlg) {
	//解包逻辑
	errFlg = 0;
	return GETINSTANCEMANAGE(ProtocolManagement)->decode(key,ptr,len,errFlg);
}
static void conn_readcb(struct bufferevent* bev, void* ctx) {

	//获取输入缓存
	struct evbuffer* pInput = bufferevent_get_input(bev);
	//获取输入缓存数据的长度
	int nLen = evbuffer_get_length(pInput);
	//获取数据的地址
	const char* pBody = (const char*)evbuffer_pullup(pInput, nLen);
	SocketItem* si = (SocketItem*)ctx;
	int errFlg = 0;
	if (nLen > 0) {
		si->onRecv((unsigned char*)pBody, (unsigned int)nLen);
		unsigned int curBuffLen = 0;
		unsigned char *p1 = si->get(0, curBuffLen);
		//这个地方需要处理沾包
		if (curBuffLen > 0) {
			unsigned int surplusLen = socketData2ProtocolData(si->m_sockKey, p1, curBuffLen,errFlg);
			if (errFlg == 0 && surplusLen < curBuffLen ) {
				if (surplusLen == 0) {
					p1 = NULL;
				}
				else {
					p1 = &p1[curBuffLen - surplusLen];
				}
				if (si->resetRecvBuff(p1, surplusLen) == false) {
					//应该想法子提示，或者通知对方
				}
			}
			else if(errFlg != 0){
				//封装一个消息 两秒后断开
				throw "error";
			}
		}
	}
}

static void conn_writecb (struct bufferevent* bev, void* ctx) {
	
	SocketItem* si = (SocketItem*)ctx;
	unsigned int len1 = 0;
	unsigned int len2 = 0;
	int idx = 0;
	while (idx++) {
		unsigned char *p = si->get(idx, len1);
		if (len1 == 0)
			break;
		bufferevent_write(bev, p, len1);
	}
	for (int i = 1; i < idx; i++)
	{
		si->clearBuff(idx);
	}
	si->swapSendVector();
}

static void listener_cb(struct evconnlistener* listener, evutil_socket_t fd,struct sockaddr* sa, int socklen, void* user_data)
{
	struct event_base* base = g_libevents->base;
	struct bufferevent* bev;

	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	struct sockaddr_in* sin = (sockaddr_in*)sa;
	std::string ip = "";
#ifdef WIN32
	char arr[100] = "";
	inet_ntop(AF_INET, (void*)&sin, arr, 100);
	ip = arr;
#else
	ip = inet_ntoa(sin->sin_addr);
#endif
	
	int port = ntohs(sin->sin_port);
	SocketItem *si = new SocketItem(ip,port);
	std::function<void(SocketItem*)>* pt;
	pt = (decltype(pt))user_data;
	(*pt)(si);
	bufferevent_setcb(bev, conn_readcb,conn_writecb, conn_eventcb,(void*)(si));
	bufferevent_enable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);


	//bufferevent_write(bev, MESSAGE, strlen(MESSAGE));
}

static int listenr_state = 0;
struct tempServerInfoThread {
	std::function<void( SocketItem*)> fun;
	int flags;
	evutil_socket_t fd;
};
static tempServerInfoThread tsit;
static void threadServerLoopThread() {
	struct evconnlistener* listener = evconnlistener_new(g_libevents->base, listener_cb, &(tsit.fun), tsit.flags, -1, tsit.fd);
	if (!listener)
	{

		evutil_closesocket(tsit.fd);
		evconnlistener_free(listener);
		listenr_state = 2;
		return;
	}
	listenr_state = 1;
	event_base_dispatch(g_libevents->base);
	evconnlistener_free(listener);
}
bool SocketManage::startServer(int port, int listNum)
{
	auto serverHandler = pool.find("server");
	if (serverHandler != pool.end()) {
		return true;
	}
	std::mutex mt;
	mt.lock();
	struct sockaddr_in sin = { 0 };
	if(g_libevents->base == NULL)
		g_libevents->base = event_base_new();
	if (!g_libevents->base) {
		mt.unlock();
		return false;
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	evutil_socket_t fd;
	int fdOn = 1;
	int fdKeepIdle = 60;
	int fdKeepInterval = 20;
	int fdKeepCount = 3;
	int family = sin.sin_family;
	int flags = LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE;
	int socktype = SOCK_STREAM | EVUTIL_SOCK_NONBLOCK;

	if (flags & LEV_OPT_CLOSE_ON_EXEC)
		socktype |= EVUTIL_SOCK_CLOEXEC;

	fd = evutil_socket_(family, socktype, 0);
	if (fd == -1) {
		mt.unlock();
		return false;
	}
#ifdef _WIN32
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char*)&fdOn, sizeof(fdOn)) < 0)
#else
	if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void*)&fdOn, sizeof(fdOn)) < 0)
#endif
	{
		mt.unlock();
		evutil_closesocket(fd);
		return false;
	}

#ifdef _WIN32
	if (setsockopt(fd, SOL_SOCKET, TCP_KEEPIDLE, (char*)&fdKeepIdle, sizeof(fdKeepIdle)) < 0)
#else
	if (setsockopt(fd, SOL_SOCKET, TCP_KEEPIDLE, (void*)&fdKeepIdle, sizeof(fdKeepIdle)) < 0)
#endif
	{
		mt.unlock();
		evutil_closesocket(fd);
		return false;
	}

#ifdef _WIN32
	if (setsockopt(fd, SOL_SOCKET, TCP_KEEPINTVL, (char*)&fdKeepInterval, sizeof(fdKeepInterval)) < 0)
#else
	if (setsockopt(fd, SOL_SOCKET, TCP_KEEPINTVL, (void*)&fdKeepInterval, sizeof(fdKeepInterval)) < 0)
#endif
	{
		mt.unlock();
		evutil_closesocket(fd);
		return false;
	}

#ifdef _WIN32
	if (setsockopt(fd, SOL_SOCKET, TCP_KEEPCNT, (char*)&fdKeepCount, sizeof(fdKeepCount)) < 0)
#else
	if (setsockopt(fd, SOL_SOCKET, TCP_KEEPCNT, (void*)&fdKeepCount, sizeof(fdKeepCount)) < 0)
#endif
	{
		mt.unlock();
		evutil_closesocket(fd);
		return false;
	}

	if (flags & LEV_OPT_REUSEABLE) {
		if (evutil_make_listen_socket_reuseable(fd) < 0)
		{
			mt.unlock();
			evutil_closesocket(fd);
			return false;
		}
	}

	if (bind(fd, (struct sockaddr*)&sin,
		sizeof(sin)) < 0)
	{
		mt.unlock();
		evutil_closesocket(fd);
		return false;
	}

	
	int listenr_state = 0;
	std::function<void(SocketItem*)> fun = [](SocketItem* si) {
		char arr[100] = "";
		sprintf(arr, "accept_%s::%d", si->m_ip.c_str(), si->m_port);
		/*pool.insert(std::make_pair(arr, si));
		si->m_sockKey = arr;
		notifyEvent(arr, S_ACCEPT, NULL, 0);*/
	};
	listenr_state = 0;
	tsit.fd = fd;
	tsit.flags = flags;
	tsit.fun = fun;
	std::thread tr = std::thread(threadServerLoopThread);

	tr.detach();
	while (listenr_state == 0) {
		S_Sleep(6);
	}
	if (listenr_state == 2){
		mt.unlock();
		return false;
	}
	SocketItem *si = new SocketItem();
	si->m_sockKey = "server";
	pool.insert(std::make_pair("server", si));
	mt.unlock();
	return true;

}
std::string SocketManage::connect(std::string ip, int port) {
	return "";
}
bool SocketManage::notifyEvent(std::string key, NotifyEventName eventType, void* p, int len) {
	return true;
}

bool SocketManage::eraseShare(std::string key)
{
	auto item = shareBuffPool.find(key);
	if(item == shareBuffPool.end())
		return false;
	shareBuff *buff = item->second;
	if (buff != NULL)
		delete buff;
	shareBuffPool.erase(key);
	return true;

}
std::string SocketManage::addSharePool(const unsigned char* buff, const unsigned int len)
{
	if (len == 0 || buff == NULL)
		return "";
	//排除重复的buff
	for (auto item = shareBuffPool.begin(); item != this->shareBuffPool.end(); item++)
	{
		int len1 = item->second->len;
		if (len1 == len) {
			if (strcmp((char*)item->second->buff, (char*)buff) == 0)
				return item->first;
		}
	}
	char arr[40] = "";
	sprintf_s(arr, "SockBuff_%p", buff);
	std::string key = arr;
	const size_t sizeoflen = sizeof(len);
	unsigned char* p = new unsigned char[len+ sizeof(shareBuff)+1];
	if (p == NULL)
		return "";
	std::mutex mt;
	mt.lock();
	shareBuff* sbf = (shareBuff*)p;
	sbf->len = len;
	sbf->buff = &p[sizeof(shareBuff)];
	memcpy(sbf->buff, buff, len);
	sbf->buff[len] = 0;
	shareBuffPool.insert(std::make_pair(key, sbf));
	mt.unlock();
	return key;
}
void SocketManage::close(std::string key) {
	
	auto iter = pool.find(key);
	if (iter == pool.end())
		return;
	RecyclingCenterManage *rcm = GETINSTANCEMANAGE(RecyclingCenterManage);
	std::string rkey = rcm->push(iter->second, 10);
	iter->second->close();
	if (rkey == "") {
		delete iter->second;
		iter->second = NULL;
	}else
		iter->second->m_recyclingStr = rkey;
	pool.erase(key);

}
bool SocketManage::send(std::string key, void* p, const unsigned long len) {

	auto iter = pool.find(key);
	if (iter != pool.end()) {
		iter->second;
	}
	
	return false;
}