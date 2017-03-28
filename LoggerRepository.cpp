#include "LoggerRepository.h"
#include "LoggerFactory.h"
#include "ScopedLock.h"
#include "Properties.h"

CLoggerRepository* CLoggerRepository::_instance = nullptr;

//double check 需要屏蔽编译器优化 稍后补充
CLoggerRepository* CLoggerRepository::getInstance()
{
	if (_instance == nullptr)
	{
		CSocpedLock lock();
		if (_instance == nullptr)
		{
			_instance = new CLoggerRepository;
		}
	}
	return _instance;
}


CLogger *CLoggerRepository::getLogger(const std::string& loggerName)
{
	CSocpedLock lock();
	CLogger* pClogger = nullptr;
	try
	{
		std::map<std::string, CLogger*>::iterator iterRepository;
		if ((iterRepository=_mapRepository.find(loggerName)) != _mapRepository.end())
		{
			return (*iterRepository).second;
		}
		else
		{
			pClogger = CLoggerFactory::createLogger(loggerName,_pCproperties);
			_mapRepository.insert(std::map<std::string, CLogger*>::value_type(loggerName, pClogger));
			return pClogger;
		}
	}
	catch (const std::exception&)
	{
		if (pClogger != nullptr)
		{
			delete pClogger;
			pClogger = nullptr;
		}
		throw;
	}
}

void CLoggerRepository::configure(const std::string& configurePath, const std::string& logPath)
{
	try
	{
		_pCproperties = new CProperties(configurePath);
		_pCproperties->loadProperties();
		_strConfigureFilePath = configurePath;
	}
	catch (const std::exception&)
	{
		if (_pCproperties != nullptr)
		{
			delete _pCproperties;
			_pCproperties = nullptr;
		}
		throw;
	}

}

void CLoggerRepository::refresh()
{

}

void CLoggerRepository::close()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}

CLoggerRepository::~CLoggerRepository()
{
	std::map<std::string, CLogger*>::iterator iterRepository;
	for (iterRepository= _mapRepository.begin(); iterRepository<_mapRepository.end(); iterRepository++)
	{
		if ((*iterRepository).second != nullptr)
		{
			delete (*iterRepository).second;
			(*iterRepository).second = nullptr;
		}
		_mapRepository.clear();
	}
}