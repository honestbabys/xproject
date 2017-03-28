#ifndef _DB_REDIS_DBCONNECTION_H
#define _DB_REDIS_DBCONNECTION_H
#include "DBConnection.h"
class CRedisClusterResult;
class CRedisDBConnection :public CDBConnection 
{
public:
	CRedisDBConnection(const CDBProperties& property);
	virtual ~CRedisDBConnection();
	virtual void init();
	//设置执行SQL
	virtual void setSQL(const std::string& sql);
	virtual void setSQL(const char* sql);
	//参数绑定，绑定int类型
	//列名，绑定的值
	virtual void bindInt(const int attrID, std::string& value);
	virtual void bindString(const int attrID, std::string& value);
	virtual void bindBlob(const int attrID, std::string& value);
	virtual void bindDate(const int attrID, std::string& value);
	//查询SQL执行
	virtual void executeQuery();
	virtual void executeUpdate();
	virtual void executeProducure();
	//顺序控制
	virtual void begin();
	virtual void commit();
	virtual void rollback();
	//连接有效性判断
	virtual void connect();
	virtual bool isConnected();
	virtual void closeConnection();
	//结果获取
	virtual bool next();
	virtual const std::string getFieldName(unsigned int index) const;
	virtual const std::string getString(unsigned int index) const;
	virtual const int getInt(unsigned int index) const;
	CRedisClusterResult* executeCmd(const char *format, ...);
private:
	void execute(redisClusterContext *cc, redisReply** reply, const char *format, va_list ap);
private:
	redisClusterContext* _pClusterHandle;
	std::string _strCmd; 
};
#endif
