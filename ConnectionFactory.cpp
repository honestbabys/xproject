#include "ConnectionFactory.h"
#include "DBConnection.h"
#include "DBProperties.h"
#include "ScopedLock.h"
#include "MySQLDBConnection.h"
#include "RedisDBConnection.h"

CConnectionFactory* CConnectionFactory::_instance = nullptr;

CConnectionFactory* CConnectionFactory::getInstance()
{
	if (_instance == nullptr)
	{
		CSocpedLock lock();
		if (_instance == nullptr)
		{
			_instance = new CConnectionFactory;
		}
	}
	return _instance;
}

void CConnectionFactory::close()
{
	if (_instance != nullptr)
	{
		delete _instance; 
		_instance = nullptr;
	}
}

CDBConnection* CConnectionFactory::getDBConnection(const CDBProperties& property)
{
	try
	{
		CDBConnection *pCDBConn = nullptr;
		if (property.getDBType().compare("MYSQL") == 0)
		{
			pCDBConn = new CMySQLDBConnection(property);
		}
		else if (property.getDBType().compare("REDIS") == 0)
		{
			pCDBConn = new CRedisDBConnection(property);
		}

		pCDBConn->init();
		pCDBConn->connect();
		return pCDBConn;
	}
	catch (const std::exception&)
	{

	}
}