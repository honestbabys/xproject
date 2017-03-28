#ifndef _SERVER_SOCKET_SERVER_H_
#define _SERVER_SOCKET_SERVER_H_
#include <string>
#include "Server.h"

class CSocketServer :public CServer
{
public:
	CSocketServer(const int port);
	virtual ~CSocketServer();
	void init();
	void run();

private:
	struct event_base* createEventBase();
	void eventDispatch();

private:
	struct event_base* _pEventBaseHandle;
	int _iPort;
	std::string _strIp;
};

#endif
