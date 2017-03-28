#include <sstream>
#include "Level.h"
#include "Exception.h"

bool CLevel::isLevelOk(LevelType level) 
{
	short index = static_cast<int>(level);
	if (index <0 || index >4)
	{
		return false;
	}
	return true;
}
void CLevel::setLevel(int level)
{
	if (level != DEBUG && level != INFO &&
		level != WARN && level != LERROR &&
		level != FATAL)
	{
		std::ostringstream os;
		os << "未知日志级别，当前日志级别为";
		os << level;
		throw CException(3001, os.str().c_str());
	}
	_level = static_cast <LevelType>(level);
}

std::string CLevel::getLevelName(LevelType level) 
{
	const std::string name[] = { "DEBUG","INFO","WARN","ERROR","FATAL" };
	short index = static_cast<int>(level);
	if (index <0 || index >4 )
	{
		return std::string("UNKOWN");
	}
	else 
	{
		return name[index];
	}

}

int CLevel::getLevelValue(const std::string& strLevel)
{
	const std::string name[] = { "DEBUG","INFO","WARN","ERROR","FATAL" };
	for (size_t i = 0; i < sizeof(name)/sizeof(name[0]); i++)
	{
		if (!strLevel.compare(name[i]))
		{
			return i;
		}
	}
	return -1;
}