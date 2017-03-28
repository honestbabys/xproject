#include <sstream>
#include "cppconn\driver.h"
#include "cppconn\connection.h"
#include "cppconn\resultset.h"
#include "cppconn\prepared_statement.h"
#include "MySQLDBConnection.h"

CMySQLDBConnection::CMySQLDBConnection(const CDBProperties& property):CDBConnection(property), _pDriver(nullptr), _pConn(nullptr), _pPreparedStmt(nullptr), _pResultSet(nullptr)
{

}

CMySQLDBConnection:: ~CMySQLDBConnection()
{
	
}

void CMySQLDBConnection::init()
{
	try
	{
		_pDriver = get_driver_instance();
		//sql::Connection *con = _pDriver->connect(_CDBProperty.getServer(), _CDBProperty.getUser(), _CDBProperty.getPassword())
		_pConn = std::unique_ptr<sql::Connection>(_pDriver->connect(_CDBProperty.getServer(), _CDBProperty.getUser(), _CDBProperty.getPassword()));
		_pConn->setAutoCommit(0);
		_pConn->setSchema(_CDBProperty.getDatabase());
	}
	catch (const std::exception&)
	{

	}
}

void CMySQLDBConnection::setSQL(const std::string& sql)
{
	//直接赋值还是需要转移使用权啊，我的娘
	_pPreparedStmt = std::move(getPreparedStmt(sql));
}

void CMySQLDBConnection::setSQL(const char* sql)
{
	_pPreparedStmt = std::move(getPreparedStmt(std::string(sql)));
}

void CMySQLDBConnection::bindInt(const int attrID, std::string& value)
{
	bindValue(attrID, value, CMySQLDBConnection::NUM_DATA_TYPE);
}

void CMySQLDBConnection::bindString(const int attrID, std::string& value)
{
	bindValue(attrID, value, CMySQLDBConnection::STRING_DATA_TYPE);
}

void CMySQLDBConnection::bindBlob(const int attrID, std::string& value)
{
	bindValue(attrID, value, CMySQLDBConnection::BLOB_DATA_TYPE);
}

void CMySQLDBConnection::bindDate(const int attrID, std::string& value)
{
	bindValue(attrID, value, CMySQLDBConnection::DATE_DATA_TYPE);
}

void CMySQLDBConnection::executeQuery()
{
	try
	{
		_pResultSet = std::unique_ptr<sql::ResultSet>(_pPreparedStmt->executeQuery());
		_iFieldCount = _pResultSet->rowsCount();
	}
	catch (const std::exception&)
	{

	}
}

void CMySQLDBConnection::executeUpdate()
{
	_pPreparedStmt->executeUpdate();
}

void CMySQLDBConnection::executeProducure()
{
	//存过怎么执行
	_pPreparedStmt->executeUpdate();
}

void CMySQLDBConnection::begin()
{

}

void CMySQLDBConnection::commit()
{
	_pConn->commit();
}

void CMySQLDBConnection::rollback()
{
	_pConn->rollback();
}

void CMySQLDBConnection::connect()
{

}

bool CMySQLDBConnection::isConnected()
{
	return _pConn->isValid();
}

void CMySQLDBConnection::closeConnection()
{
	return _pConn->close();
}

bool CMySQLDBConnection::next()
{
	return _pResultSet->next();
}

bool CMySQLDBConnection::previous()
{
	return _pResultSet->previous();
}

const std::string CMySQLDBConnection::getFieldName(unsigned int index) const
{

}

const std::string CMySQLDBConnection::getString(const std::string& labelName) const
{
	return _pResultSet->getString(labelName).asStdString();
}

const std::string CMySQLDBConnection::getString(unsigned int index) const
{
	return _pResultSet->getString(index).asStdString();
}

const int CMySQLDBConnection::getInt(unsigned int index) const
{
	return _pResultSet->getInt(index);
}

const int CMySQLDBConnection::getInt(const std::string& labelName) const
{
	return _pResultSet->getInt(labelName);
}
std::unique_ptr<sql::PreparedStatement> CMySQLDBConnection::getPreparedStmt(const std::string& sql)
{
	if (_pConn != nullptr)
	{
		try
		{
			return std::unique_ptr<sql::PreparedStatement>(_pConn->prepareStatement(sql));
		}
		catch (const std::exception&)
		{

		}
	}
}

void CMySQLDBConnection::bindValue(int id, std::string val, DataType dtype)
{
	switch (dtype)
	{
		case CMySQLDBConnection::NUM_DATA_TYPE:
		{
			_pPreparedStmt->setInt(id, atoi(val.c_str()));
			break;
		}
		case CMySQLDBConnection::STRING_DATA_TYPE:
		{
			_pPreparedStmt->setString(id, val);
			break;
		}
		case CMySQLDBConnection::DATE_DATA_TYPE:
		{
			_pPreparedStmt->setDateTime(id, val);
			break;
		}
		case CMySQLDBConnection::BLOB_DATA_TYPE:
		{
			std::istringstream istr(val);
			_pPreparedStmt->setBlob(id, &istr);
			break;
		}
		default:
		{
			_pPreparedStmt->setString(id, val);
			break;
		}
	}
}