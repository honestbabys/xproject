#include "RedisDBConnection.h"
#include "Macroes.h"
#include "hircluster.h"
#include "RedisClusterResult.h"

CRedisDBConnection::CRedisDBConnection(const CDBProperties& property):CDBConnection(property), _pClusterHandle(nullptr)
{

}

CRedisDBConnection:: ~CRedisDBConnection()
{
	DEBUG("CRedisDBConnection dtor");
}

void CRedisDBConnection::init()
{

}

//设置执行SQL
void CRedisDBConnection::setSQL(const std::string& sql)
{
	_strCmd = sql;
}

void CRedisDBConnection::setSQL(const char* sql)
{
	_strCmd = std::string(sql);
}

void CRedisDBConnection::bindInt(const int attrID, std::string& value)
{

}

void CRedisDBConnection::bindString(const int attrID, std::string& value)
{

}

void CRedisDBConnection::bindBlob(const int attrID, std::string& value)
{

}

void CRedisDBConnection::bindDate(const int attrID, std::string& value)
{

}

void CRedisDBConnection::executeQuery()
{
	executeCmd(_strCmd.c_str());
}

void CRedisDBConnection::executeUpdate()
{
	executeCmd(_strCmd.c_str());
}

void CRedisDBConnection::executeProducure()
{
	executeCmd(_strCmd.c_str());
}

void CRedisDBConnection::begin()
{

}

void CRedisDBConnection::commit()
{

}

void CRedisDBConnection::rollback()
{

}

void CRedisDBConnection::connect()
{
	try
	{
		std::string strAddr = _CDBProperty.getServer() + ":" + _CDBProperty.getPort();
		_pClusterHandle = redisClusterConnect(strAddr.c_str(), HIRCLUSTER_FLAG_NULL);
		if ((_pClusterHandle == nullptr) || (_pClusterHandle->err))
		{
			if (_pClusterHandle)
			{
				redisClusterFree(_pClusterHandle);
				_pClusterHandle = nullptr;
			}
			else
			{
				//没句柄可以分配
			}
		}

	}
	catch (const std::exception&)
	{

	}
}

bool CRedisDBConnection::isConnected()
{
	CRedisClusterResult* redisResult = executeCmd("PING");
	if (strcmp(redisResult->getRedisClusterResult()->str, "PONG") == 0)
	{
		return true;
	}
	return false;
}

void CRedisDBConnection::closeConnection()
{
	try
	{
		redisClusterFree(_pClusterHandle);
		_pClusterHandle = nullptr;
	}
	catch (const std::exception&)
	{

	}
}

bool CRedisDBConnection::next()
{

}

const std::string CRedisDBConnection::getFieldName(unsigned int index) const
{

}

const std::string CRedisDBConnection::getString(unsigned int index) const
{

}

const int CRedisDBConnection::getInt(unsigned int index) const
{

}

void CRedisDBConnection::execute(redisClusterContext *cc, redisReply** reply, const char *format, va_list ap)
{
	*reply = (redisReply*)redisClustervCommand(cc, format, ap);
	if (*reply == NULL) 
	{
		//异常
	}
}

CRedisClusterResult* CRedisDBConnection::executeCmd(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	redisReply* reply = nullptr;
	execute(_pClusterHandle, &reply, format, ap);
	va_end(ap);
	return new CRedisClusterResult(reply);
}