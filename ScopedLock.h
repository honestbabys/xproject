#ifndef _COMMON_SCOPEDLOCK_H
#define _COMMON_SCOPEDLOCK_H
#include "NonCopyable.h"

class CSocpedLock :public CNonCopyable
{
public:
	//是否应该构造个参数出来，让外部调用时传入个互斥量
	CSocpedLock();
	~CSocpedLock();

private:
	CSocpedLock(const CSocpedLock& copy);
	int Lock();
	int UnLock();
	int TryLock();

private:
#ifdef Linux
	pthread_mutex_t _mutex;
	pthread_mutexattr_t _mutexAttr;
#endif

};

#endif // !_COMMON_SCOPEDLOCK_H

