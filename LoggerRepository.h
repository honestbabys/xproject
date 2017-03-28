#ifndef _LOG_LOGGER_REPOSITORY_H
#define _LOG_LOGGER_REPOSITORY_H

#include <string>
#include <map>
class CLogger;
class CProperties;

class CLoggerRepository 
{
public:
	static CLoggerRepository* getInstance();
	static CLoggerRepository* _instance;

	CLogger *getLogger(const std::string& loggerName);
	void configure(const std::string& configurePath, const std::string& logPath);
	void refresh();
	void close();

private:
	//单例模式，私有化构造函数、拷贝构造，析构函数。
	CLoggerRepository();
	CLoggerRepository(const CLoggerRepository& copy);
	virtual ~CLoggerRepository();

private:
	std::map<std::string, CLogger*> _mapRepository;
	CProperties *_pCproperties;
	std::string _strConfigureFilePath;
};
#endif // !_LOG_LOGGER_REPOSITORY_H
