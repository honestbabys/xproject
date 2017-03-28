#ifndef _COMMON_EXCEPTION_H_
#define _COMMON_EXCEPTION_H_

#include <string>

class CException
{
public:
	CException(const int iErrno, const char* errMsg)
	{
		_iErrno = iErrno;
		_cErrMsg = new char[strlen(errMsg) + 1];
		strncpy(_cErrMsg, errMsg, strlen(errMsg));
	}

	virtual ~CException() 
	{
		if (_cErrMsg != NULL)
		{
			delete[]_cErrMsg;
			_cErrMsg = NULL;
		}
	}

	int errCode() const 
	{
		return _iErrno;
	}

	const char* what() const 
	{
		return _cErrMsg;
	}

private:
	char *_cErrMsg;
	int _iErrno;
};
#endif