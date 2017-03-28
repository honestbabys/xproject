#ifndef _LOG_APPENDER_H
#define _LOG_APPENDER_H

#include <memory>
#include "LogEvent.h"
class CLayout;
class CLevel;

class CAppender
{
public:
	CAppender() :_pLayout(nullptr), _pLevel(nullptr) {};
	virtual ~CAppender() {};

	virtual void doAppend(CLogEvent& logevent);
	virtual void setLevel(std::shared_ptr<CLevel> level);
	virtual void setLayOut(std::shared_ptr<CLayout> layout);

	virtual void open() { };
	virtual void close() {  };
private:
	std::shared_ptr<CLayout> _pLayout; //没有*号，没有*号。。。
	std::shared_ptr<CLevel> _pLevel;
	virtual void append(const std::string& msg) = 0;
};


#endif // !_LOG_APPENDER_H

