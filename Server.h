#ifndef _SERVER_SERVER_H_
#define _SERVER_SERVER_H_
class CServer
{
public:
	CServer() {};
	virtual ~CServer() {};
	virtual void init() = 0; //完成服务器需要初始化的所有资源
	virtual void run() = 0; //服务器进行监听接收请求
private:
};
#endif
