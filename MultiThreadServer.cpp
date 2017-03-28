#include "MultiThreadServer.h"
#include "RuntimePara.h"
const static int BACKLOG = 100;
const static int MAXQUEUE = 5000;
void* taskQueue[MAXQUEUE];
int _iHeader = 0; //���ͷ
int _iTail = 0; //���βλ��

pthread_mutex_t queueMutex;
pthread_cond_t queueCond;

static void* doRequest(void* request)
{
	pthread_detach(pthread_self());

}

//����У����д���������ȫ�������ڶ�����
static int enqueue(void* request)
{
	pthread_mutex_lock(&queueMutex);
	int iNext = _iTail + 1;
	if (iNext >= MAXQUEUE)
	{
		iNext = 0;
	}
	if (iNext == _iHeader)
	{

	}
	else
	{
		taskQueue[_iTail] = request;
		_iTail = iNext;
		pthread_cond_signal(&queueCond);
	}
	pthread_mutex_unlock(&queueMutex);
}

/*ȡ������Ϣ������ȡ��֮�������Ӧ���߼�����*/
static void* dequeue(void* request)
{
	pthread_mutex_lock(&queueMutex);
	while (_iHeader == _iTail) //��
	{
		pthread_cond_wait(&queueCond, &queueMutex);
	}
	void *request = taskQueue[_iHeader++];
	if (_iHeader >= MAXQUEUE) //����ȡ��
	{
		_iHeader = 0;
	}
	pthread_mutex_unlock(&queueMutex);
	return request;
}

CMultiThreadServer::CMultiThreadServer()
{

}

CMultiThreadServer::~CMultiThreadServer()
{

}

void CMultiThreadServer::init(CRuntimePara& runPara)
{
	_iPort = runPara.getInt("SERVERPORT");
	_iMaxCon = runPara.getInt("MAXCONCURRENCE", 10);
	pthread_t *pid = new pthread_t[_iMaxCon];
	pthread_mutex_init(&queueMutex, nullptr);
	pthread_cond_init(&queueCond, nullptr);
	for (auto i=0; i<_iMaxCon; i++)
	{
		int iret = pthread_create(&_ptid[i], NULL, (void*(*)(void*))doRequest, (void*)&_pThread[i]);
		if (iret != 0) //�����߳�ʧ��
		{
			//�쳣�׳�
		}
		else
		{
			//log
		}
	}

}

void CMultiThreadServer::setObject(void* pObject)
{

}

void* CMultiThreadServer::getObject()
{


}

void CMultiThreadServer::prepare()
{

}

void CMultiThreadServer::run()
{

}

void CMultiThreadServer::safeExit()
{

}