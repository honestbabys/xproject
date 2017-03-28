#include "ScopedLock.h"

CSocpedLock::CSocpedLock()
{
#ifdef Linux
	pthread_mutexattr_init(&_mutexAttr);
	pthread_mutex_init(&_mutex, &_mutexAttr);
	Lock();
#endif
}

CSocpedLock::~CSocpedLock()
{
#ifdef Linux
	pthread_mutexattr_destory(&_mutexAttr);
	if (EBUSY == pthread_mutex_destory(&_mutex))
	{

	}
	UnLock();
#endif
}

int CSocpedLock::Lock()
{
#ifdef Linux
	return pthread_mutex_lock(&_mutex);
#endif
	return 0;
}

int CSocpedLock::UnLock()
{
#ifdef Linux
	return pthread_mutex_unlock(&_mutex);
#endif
	return 0;
}

int CSocpedLock::TryLock()
{
#ifdef Linux
	return pthread_mutex_trylock(&_mutex);
#endif
}