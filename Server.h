#ifndef _SERVER_SERVER_H_
#define _SERVER_SERVER_H_
class CServer
{
public:
	CServer() {};
	virtual ~CServer() {};
	virtual void init() = 0; //��ɷ�������Ҫ��ʼ����������Դ
	virtual void run() = 0; //���������м�����������
private:
};
#endif
