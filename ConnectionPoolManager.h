#ifndef _DB_CONNECTION_POOL_MANAGER_H
#define _DB_CONNECTION_POOL_MANAGER_H
#include <string>
#include <map>
class CDBConnection;
class CConnectionPool;
class CDBProperties;

class CDBConnectionPoolManager
{
public:
	CDBConnectionPoolManager();
	~CDBConnectionPoolManager();

	CDBConnection* getDBConnection(const std::string& dbAlias);
	void loadDBProperty(const std::string& configPath, const std::string& alias);
	void close();

private:
	CDBConnectionPoolManager(const CDBConnectionPoolManager& copy);
	const CDBConnectionPoolManager& operator=(const CDBConnectionPoolManager& copy);
private:
	std::map<std::string, CDBProperties> _mapDBProperties;
	std::map<std::string, std::unique_ptr<CConnectionPool>> _mapPool;
	//std::map<std::string, CConnectionPool*> _mapPool;
	std::string _strAlias;
};
#endif
