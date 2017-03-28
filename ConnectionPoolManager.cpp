#include "ConnectionPoolManager.h"
#include "DBConnection.h"
#include "DBProperties.h"
#include "ScopedLock.h"
#include "ConnectionPool.h"
#include "Exception.h"
#include "Properties.h"
#include "SuperString.h"
#include "RuntimePara.h"

CDBConnectionPoolManager::CDBConnectionPoolManager()
{

}

CDBConnectionPoolManager::~CDBConnectionPoolManager()
{

}

void CDBConnectionPoolManager::loadDBProperty(const std::string& configPath, const std::string& alias)
{
	_strAlias = alias;
	CProperties *pCproperty = new CProperties(configPath);
	pCproperty->loadProperties();
	for (auto i = 0; i < pCproperty->getSectionCount(); i++)
	{
		std::map<std::string, std::string> *mapSectionUnit = pCproperty->getSectionUnit(CSuperString::toString(i));
		CDBProperties dbProperty;
		CRuntimePara runPara;
		for (auto iter=(*mapSectionUnit).begin(); iter!=(*mapSectionUnit).end(); iter++)
		{
			runPara.setString((*iter).first, (*iter).second);
		}
		dbProperty.setMaxConnection(runPara.getInt("MAXCONNECTION"));
		dbProperty.setServer(runPara.getString("SERVER"));
		dbProperty.setPort(runPara.getString("PORT"));
		dbProperty.setUser(runPara.getString("USER"));
		dbProperty.setPassword(runPara.getString("PASSWORD"));
		dbProperty.setDatabase(runPara.getString("DATABASE"));
		dbProperty.setDBType(runPara.getString("DBTYPE"));
		dbProperty.setTestSQL(runPara.getString("TESTSQL"));
		_mapDBProperties.insert(std::map<std::string, CDBProperties>::value_type(runPara.getString("DBALIAS"), dbProperty));
	}
}

CDBConnection* CDBConnectionPoolManager::getDBConnection(const std::string& dbAlias)
{
	CSocpedLock lock();
	std::map<std::string, std::unique_ptr<CConnectionPool> >::iterator iterPool;
	//std::map<std::string, CConnectionPool*>::iterator iterPool;
	//find好像不能直接使用auto推倒类型
	std::map<std::string, CDBProperties>::iterator iterProperty;
	if ((iterProperty = _mapDBProperties.find(dbAlias)) != _mapDBProperties.end())
	{
		if ((iterPool=_mapPool.find(dbAlias)) != _mapPool.end())
		{
			return (*iterPool).second->getDBConnection();
		}
		else
		{
			CConnectionPool *pConnPool = new CConnectionPool((*iterProperty).second);
			_mapPool.insert(std::map<std::string, std::unique_ptr<CConnectionPool>>::value_type(_strAlias, std::unique_ptr<CConnectionPool>(pConnPool)));
			return pConnPool->getDBConnection();
		}
	}
	else
	{
		throw CException(60001, "db alias does not exist");
	}
}

void CDBConnectionPoolManager::close()
{
	for (auto iter=_mapPool.begin(); iter!= _mapPool.end(); iter++)
	{
		(*iter).second->closeAll();
	}
}