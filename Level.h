#ifndef _LOG_LEVEL_H
#define _LOG_LEVEL_H
#include <string>

class CLevel {
public:
	enum LevelType
	{
		DEBUG = 0,
		INFO = 1,
		WARN = 2,
		ERROR = 3,
		FATAL = 4
	};

	bool isLevelOk(LevelType level);
	void setLevel(int level);
	static std::string getLevelName(LevelType level);
	static int getLevelValue(const std::string& strLevel);
private:
	LevelType _level;
};
#endif // !_LOG_LEVEL_H

