#ifndef _LOG_LOGGER_H
#define _LOG_LOGGER_H
#include <string>
#include <vector>
#include <memory>
#include "Level.h"

class CAppender;

class CLogger {
public:
	CLogger(const std::string& name);
	~CLogger();

	void debug(const std::string& msg);
	void info(const std::string& msg);
	void warn(const std::string& msg);
	void error(const std::string& msg);
	void fatal(const std::string& msg);

	void debug(const char* format, ...);
	void info(const char* format, ...);
	void warn(const char* format, ...);
	void error(const char* format, ...);
	void fatal(const char* format, ...);

	void addAppender(std::unique_ptr<CAppender> appender) { _vecAppender.push_back(std::move(appender)); };
private:
	void appendAll(CLevel::LevelType levelType, const std::string& msg);
	std::string getTime();
	std::string _strName;
	std::vector<std::unique_ptr<CAppender>> _vecAppender;
};
#endif // !_LOGGER_H

