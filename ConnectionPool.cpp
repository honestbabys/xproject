#include "ConnectionPool.h"
#include "ScopedLock.h"
#include "DBConnection.h"
#include "ConnectionFactory.h"
#include "Macroes.h"

CConnectionPool::CConnectionPool(const CDBProperties& property):_dbProperty(property)
{
	DEBUG("CConnectionPool ctor now");
}

CConnectionPool::~CConnectionPool()
{
	DEBUG("CConnectionPool dtor now");
}

CDBConnection* CConnectionPool::getDBConnection()
{
	CSocpedLock lock();
	CDBConnection *pConn = nullptr;
	bool bBadConnection = false;
	std::map<CDBConnection*, int>::iterator itercon;
	for (itercon= _mapConns.begin(); itercon != _mapConns.end(); itercon++)
	{
		if ((*itercon).second == 0)
		{
			if ((*itercon).first->isConnected())
			{
				pConn = (*itercon).first;
				(*itercon).second = 1; //使用状态
				return pConn;
			}
			else //未使用，却断开，无效链接
			{
				(*itercon).second = 2; //无效状态
				bBadConnection = true;
			}
		}
	}

	if (pConn == nullptr)
	{
		if (bBadConnection)
		{
			removeInvalidConnection();
			pConn = createNewConnection();
			_mapConns.insert(std::map<CDBConnection*, int>::value_type(pConn, 0));//0未使用，正常状态
		}
		else if (_dbProperty.getMaxConnection > _mapConns.size())
		{
			pConn = createNewConnection();
			_mapConns.insert(std::map<CDBConnection*, int>::value_type(pConn, 0));//0未使用，正常状态
		}
	}

	return pConn;

}

int CConnectionPool::reserve(int iReserve)
{
	int iRealAlloced = 0;
	if (iRealAlloced > _dbProperty.getMaxConnection())
	{
		iRealAlloced = _dbProperty.getMaxConnection();
	}
	else
	{
		iRealAlloced = iReserve;
	}
	CSocpedLock lock();
	for (int i = 0; i < iRealAlloced; i++)
	{
		CDBConnection *pConn = createNewConnection();
		registerConnection(pConn);
	}
}

void CConnectionPool::registerConnection(CDBConnection* conn)
{
	_mapConns.insert(std::map<CDBConnection*, int>::value_type(conn, 0));
}

void CConnectionPool::releaseConnection(CDBConnection* conn)
{
	CSocpedLock lock();
	std::map<CDBConnection*, int>::iterator iterConn;
	if ((iterConn = _mapConns.find(conn)) != _mapConns.end())
	{
		//dbConnection中得提供关闭连接方法
		(*iterConn).first->closeConnection();
		(*iterConn).second = 0;
	}
}

void CConnectionPool::closeConnection(CDBConnection* conn)
{
	CSocpedLock lock();
	std::map<CDBConnection*, int>::iterator iterConn;
	if ((iterConn= _mapConns.find(conn)) != _mapConns.end())
	{
		//dbConnection中得提供关闭连接方法
		(*iterConn).first->closeConnection();
		if ((*iterConn).first != nullptr)
		{
			delete (*iterConn).first;
			//(*iterConn).first = nullptr;
		}
		_mapConns.erase(iterConn);
	}
}

void CConnectionPool::closeAll()
{
	CSocpedLock lock();
	std::map<CDBConnection*, int>::iterator iterConn;
	for (iterConn = _mapConns.begin(); iterConn != _mapConns.end(); iterConn++)
	{
		(*iterConn).first->closeConnection();
		if ((*iterConn).first != nullptr)
		{
			delete (*iterConn).first;
			//(*iterConn).first = nullptr;
		}
	}
	_mapConns.clear();
}

int CConnectionPool::removeInvalidConnection()
{
	CSocpedLock lock();
	std::map<CDBConnection*, int>::iterator iterConn;
	for (iterConn = _mapConns.begin(); iterConn != _mapConns.end(); iterConn++)
	{
		if ((*iterConn).second == 2)
		{
			if ((*iterConn).first != nullptr)
			{
				delete (*iterConn).first;
				//(*iterConn).first = nullptr;
			}
			_mapConns.erase(iterConn);
		}
	}
}

CDBConnection* CConnectionPool::createNewConnection()
{
	CDBConnection* conn  = CConnectionFactory::getInstance()->getDBConnection(_dbProperty);
	return conn;
}
