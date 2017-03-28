#include "DBConnection.h"
#include "DBProperties.h"

CDBConnection::CDBConnection(const CDBProperties& property):_CDBProperty(property), _iRowCount(0), _iFieldCount(0)
{
}

CDBConnection:: ~CDBConnection()
{
	
}

const unsigned int CDBConnection::getFieldCount() const
{
	return _iFieldCount;
}

const std::string CDBConnection::getConnectionType() const
{
	return _strDBType;
}