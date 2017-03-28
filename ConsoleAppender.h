#ifndef _LOG_CONSOLE_APPENDER_H
#define _LOG_CONSOLE_APPENDER_H
#include "Appender.h"

class CConsoleAppender :public CAppender 
{
public:
	virtual void append(const std::string& msg);
};
#endif // !_LOG_CONSOLE_APPENDER_H

