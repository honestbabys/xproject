#include "DBProperties.h"
#include "Macroes.h"

CDBProperties::CDBProperties():_iMaxConnection(0),_iNLS_LANG(0){}

CDBProperties::~CDBProperties()
{
	DEBUG("CDBProperties dtor now ");
}

const int CDBProperties::getMaxConnection() const
{
	return _iMaxConnection;
}

void CDBProperties::setMaxConnection(const int iMaxconn)
{
	_iMaxConnection = iMaxconn;
}

const std::string CDBProperties::getServer() const
{
	return _strServerName;
}

void CDBProperties::setServer(const std::string& serverName)
{
	_strServerName = serverName;
}

const std::string CDBProperties::getUser() const
{
	return _strUserName;
}

void CDBProperties::setUser(const std::string& userName)
{
	_strUserName = userName;
}

const std::string CDBProperties::getPassword() const
{
	return _strPassword;
}

void CDBProperties::setPassword(const std::string& password) 
{
	_strPassword = password;
}

const std::string CDBProperties::getDatabase() const
{
	return _strDatabase;
}

void CDBProperties::setDatabase(const std::string& databaseName)
{
	_strDatabase = databaseName;
}

const std::string CDBProperties::getDBType() const
{
	return _strDBtype;
}

void CDBProperties::setDBType(const std::string& dbtype)
{
	_strDBtype = dbtype;
}

const std::string CDBProperties::getTestSQL() const
{
	return _strTestSQL;
}

void CDBProperties::setTestSQL(const std::string& testsql)
{
	_strTestSQL = testsql;
}

const int CDBProperties::getNLS_LANG() const
{
	return _iNLS_LANG;
}

void CDBProperties::setNLS_LANG(const int lang)
{
	_iNLS_LANG = lang;
}

const void CDBProperties::setPort(const std::string port)
{
	_strPort = port;
}

const std::string& CDBProperties::getPort() const 
{
	return _strPort;
}