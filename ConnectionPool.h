#ifndef _DB_CONNECTION_POOL_H
#define _DB_CONNECTION_POOL_H

#include <map>
#include "DBProperties.h"

class CDBConnection;

class CConnectionPool 
{
public:
	CConnectionPool(const CDBProperties& property);
	~CConnectionPool();

	CDBConnection* getDBConnection();
	int reserve(int iReserve);
	void registerConnection(CDBConnection* conn);
	void releaseConnection(CDBConnection* conn);
	void closeConnection(CDBConnection* conn);
	void closeAll();

private:
	int removeInvalidConnection();
	CDBConnection* createNewConnection();

private:
	std::map<CDBConnection*, int> _mapConns;
	CDBProperties _dbProperty;
};
#endif