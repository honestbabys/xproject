#ifndef _LOG_LOGEVENT_H
#define _LOG_LOGEVENT_H
#include "Level.h"
class  CLogEvent
{
public:
	CLogEvent(const std::string& time, CLevel::LevelType level, const std::string& name, const std::string& msg) :
		_strTime(time), _level(level), _strName(name), _strMsg(msg) {};
	~CLogEvent() {};

	std::string getTime() const 
	{
		return _strTime;
	}

	std::string getName() const 
	{
		return _strName;
	}

	std::string getMsg() const
	{
		return _strMsg;
	}

	CLevel::LevelType getLevel() const
	{
		return _level;
	}

private:
	std::string _strTime;
	CLevel::LevelType _level;
	std::string _strName;
	std::string _strMsg;
};
#endif // !_LOG_LOGEVENT_H

