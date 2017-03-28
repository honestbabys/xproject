#ifndef _LOG_LOGGER_FACTORY_H
#define _LOG_LOGGER_FACTORY_H

#include <string>

class CLogger;
class CProperties;

class CLoggerFactory 
{
public:
	static CLogger* createLogger(const std::string& loggerName, CProperties* property);
};
#endif // !_H_LOG_LOGGER_FACTORY_H

