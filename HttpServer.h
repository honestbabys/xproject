/****************************************************************
* (C) Copyright QZtech All rights reserved.
* FILENAME:   HttpServer.h
* FUNCTION:   The Class CHttpServer declaration file
* AUTHOR:     honestbabys
* DATE:       2017-1-13
* VERSION:    1.0
* NOTES:      header file
****************************************************************/
#ifndef _SERVER_HTTP_SERVER_H_
#define _SERVER_HTTP_SERVER_H_

#include <string>
#include "Server.h"

static const struct table_entry
{
	const char *extension;
	const char *content_type;
}
content_type_table[] =
{
	{ "txt", "text/plain" },
	{ "c", "text/plain" },
	{ "h", "text/plain" },
	{ "html", "text/html" },
	{ "htm", "text/htm" },
	{ "css", "text/css" },
	{ "gif", "image/gif" },
	{ "jpg", "image/jpeg" },
	{ "jpeg", "image/jpeg" },
	{ "png", "image/png" },
	{ "pdf", "application/pdf" },
	{ "ps", "application/postsript" },
	{ NULL, NULL },
};

class CHttpServer : public CServer
{
public:
	CHttpServer(const int port);
	virtual ~ CHttpServer();
	void init();
	void run();

private:
	void decordRequest(const std::string& strRequest); //�ṩͳһ�����ӿ�
	struct event_base* createEventBase();
	struct evhttp* createEvHttp(struct event_base* pEventBase);
	void setHttpcb(int itype);
	void eventSocketBind(); //��socket
	void eventDispatch();

private:
	int _iPort; //�����˿ں�
	std::string _strIp; //����IP
	struct event_base* _pEventBaseHandle;//����ʹ������ָ���Ƿ����
	struct evhttp* _pEvHttpHandle;
};
#endif
