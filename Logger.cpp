#include "Logger.h"
#include "LogEvent.h"
#include "SuperString.h"
#include "Appender.h"

CLogger::CLogger(const std::string& name) :_strName(name) {

}

CLogger::~CLogger() {

}

void CLogger::debug(const std::string& msg)
{
	appendAll(CLevel::DEBUG, msg);
}

void CLogger::info(const std::string& msg)
{
	appendAll(CLevel::INFO, msg);
}

void CLogger::warn(const std::string& msg)
{
	appendAll(CLevel::WARN, msg);
}

void CLogger::error(const std::string& msg)
{
	appendAll(CLevel::ERROR, msg);
}

void CLogger::fatal(const std::string& msg)
{
	appendAll(CLevel::FATAL, msg);
}

void CLogger::debug(const char* format, ...)
{
	va_list va;
	__crt_va_start(va, format);
	debug(CSuperString::vstrprintf(format,va));
	__crt_va_end(va);
}

void CLogger::info(const char* format, ...)
{
	va_list va;
	__crt_va_start(va, format);
	info(CSuperString::vstrprintf(format, va));
	__crt_va_end(va);
}

void CLogger::warn(const char* format, ...)
{
	va_list va;
	__crt_va_start(va, format);
	warn(CSuperString::vstrprintf(format, va));
	__crt_va_end(va);
}

void CLogger::error(const char* format, ...)
{
	va_list va;
	__crt_va_start(va, format);
	error(CSuperString::vstrprintf(format, va));
	__crt_va_end(va);
}

void CLogger::fatal(const char* format, ...)
{
	va_list va;
	__crt_va_start(va, format);
	fatal(CSuperString::vstrprintf(format, va));
	__crt_va_end(va);
}

void CLogger::appendAll(CLevel::LevelType levelType, const std::string& msg)
{
	CLogEvent event(getTime(), levelType, _strName, msg);
	
	for (auto iterAppender = _vecAppender.begin(); iterAppender!=_vecAppender.end(); iterAppender++)
	{
		(*iterAppender).get()->doAppend(event);
	}
	
	/*
	for (std::vector<CAppender* >::const_iterator iterAppender = _vecAppender.begin(); iterAppender <_vecAppender.end(); iterAppender++)
	{
	(*iterAppender)->doAppend(event);
	}
	*/


}