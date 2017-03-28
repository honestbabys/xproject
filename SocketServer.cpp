#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#ifndef WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

#include "SocketServer.h"
#include "Macroes.h"
#include "Exception.h"

static const char MESSAGE[] = "Hello, World!\n";
CSocketServer::CSocketServer(const int port):_iPort(port), _strIp(""), _pEventBaseHandle(NULL)
{

}

CSocketServer::~CSocketServer()
{
	if (_pEventBaseHandle != nullptr)
	{
		event_base_free(_pEventBaseHandle);
		_pEventBaseHandle = nullptr;
	}
}

static void connWriteCb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) == 0) 
	{
		DEBUG("flushed answer\n");
		bufferevent_free(bev);
	}
}
static void connReadCb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer* input = bufferevent_get_input(bev);
	if (evbuffer_get_length(input) == 0) 
	{

	}
	else
	{
		//怎么读，动态一直读
		size_t bufferevent_read(evbuffer, void *data, size_t size);
	}
	
}
static void connEventCb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF)
	{
		DEBUG("Connection closed.\n");
	}
	else if (events & BEV_EVENT_ERROR) 
	{
		DEBUG("Got an error on the connection: %s\n",
			strerror(errno));/*XXX win32*/
	}
	/* None of the other events can happen here,  since we haven't enabled
	* timeouts */
	bufferevent_free(bev);
}

/*当有连接建立时回调*/
static void listenerCb(struct evconnlistener *listener, evutil_socket_t fd,
	struct sockaddr *sa, int socklen, void *userData)
{
	struct event_base *pEventBase = static_cast<event_base*>(userData);
	struct bufferevent *pBuffevent = bufferevent_socket_new(pEventBase, fd, BEV_OPT_CLOSE_ON_FREE);
	if (pBuffevent == NULL)
	{
		DEBUG("Error constructing bufferevent!");
		event_base_loopbreak(pEventBase);
		throw CException(2002,"Error constructing bufferevent!");
	}
	//第二个参数注册读操作回调函数
	//第三个参数注册写回调函数
	//第四个参数代表event发生时回调函数
	bufferevent_setcb(pBuffevent, NULL, connWriteCb, connEventCb, NULL);
	bufferevent_enable(pBuffevent, EV_WRITE | EV_READ);
	//bufferevent_disable(pBuffevent, EV_READ); 

	bufferevent_write(pBuffevent, MESSAGE, strlen(MESSAGE));
}

static void signal_cb(evutil_socket_t sig, short events, void *user_data)
{
	struct event_base *base = (event_base *)user_data;
	struct timeval delay = { 2, 0 };

	printf("Caught an interrupt signal; exiting cleanly in two seconds.\n");

	event_base_loopexit(base, &delay);
}

void CSocketServer::init()
{
	_pEventBaseHandle = createEventBase();

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(_iPort);

	struct evconnlistener* pEvConnListener = evconnlistener_new_bind(_pEventBaseHandle, listenerCb, (void *)_pEventBaseHandle,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, -1,
		(struct sockaddr*)&sin,
		sizeof(sin));
	if (pEvConnListener == NULL)
	{
		DEBUG("Could not create a listener!");
		throw CException(2002, "Could not create a listener!");
	}


	struct event *signal_event = evsignal_new(_pEventBaseHandle, SIGINT, signal_cb, (void *)_pEventBaseHandle);

	if (!signal_event || event_add(signal_event, NULL) < 0) 
	{
		fprintf(stderr, "Could not create/add a signal event!\n");
	}

	
	printf("after event_base_dispatch called\n");
	evconnlistener_free(listener);

	event_free(signal_event);
	

	printf("done\n");
}

void CSocketServer::eventDispatch()
{
	event_base_dispatch(_pEventBaseHandle);
}

void CSocketServer::run() 
{
	eventDispatch()
}

struct event_base* CSocketServer::createEventBase()
{
	struct event_base* pEventBase = event_base_new(); //创建eventbase
	if (!pEventBase)
	{
		DEBUG("Couldn't create an event_base: exiting");
		throw CException(2001, "Couldn't create an event_base");
	}
	return pEventBase;
}