#ifndef _SERVER_MULTITHREAD_SERVER_H
#define _SERVER_MULTITHREAD_SERVER_H
class CMultiThreadServer
{
public:
	typedef struct requestType
	{
		void* request;
		CRuntimePara para;
	}reqType;
	CMultiThreadServer();
	virtual ~CMultiThreadServer();
	virtual void init(CRuntimePara& runPara);
	virtual void setObject(void* pObject);
	virtual void* getObject();
	virtual void prepare();
	virtual void run();
	virtual void safeExit();
private:
	int _iPort; //端口号
	int _iMaxCon; //线程数
};
#endif
