#ifndef _LOG_APPENDER_FACTORY_H
#define _LOG_APPENDER_FACTORY_H
#include <string>

class CAppender;
class CProperties;

class CAppenderFactory 
{
public:
	static CAppender* createAppender(const std::string& appenderName, CProperties* property);
};
#endif // !_LOG_APPENDER_FACTORY_H

