#ifndef _DB_MYSQL_DBCONNECTION_H
#define _DB_MYSQL_DBCONNECTION_H

#include <memory>
#include "DBConnection.h"

class CMySQLDBConnection : public CDBConnection
{
public:
	typedef enum DataType 
	{
		NUM_DATA_TYPE = 1,		/** 枚举，NUM类型*/
		STRING_DATA_TYPE = 2,	/** 枚举，VARCHAR2类型*/
		DATE_DATA_TYPE = 3,		/**枚举,DATE类型*/
		BLOB_DATA_TYPE = 4	/**枚举，CBLOB类型*/
	}DataType;

	CMySQLDBConnection(const CDBProperties& property);
	virtual ~CMySQLDBConnection();
	//初始化数据库连接，用户名密码，环境等等
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
	virtual bool previous();
	virtual const std::string getFieldName(unsigned int index) const;
	virtual const std::string getString(const std::string& labelName) const;
	virtual const std::string getString(unsigned int index) const;
	virtual const int getInt(unsigned int index) const;
	virtual const int getInt(const std::string& labelName) const;
	virtual std::istream* getBlob(unsigned int index);
	virtual std::istream* getBlob(const std::string& labelName);

private:
	std::unique_ptr<sql::PreparedStatement> getPreparedStmt(const std::string& sql);
	void bindValue(int id, std::string val, DataType dtype);
private:
	sql::Driver* _pDriver; //Driver不需要自己释放
	std::unique_ptr<sql::Connection> _pConn;
	std::unique_ptr<sql::PreparedStatement> _pPreparedStmt;
	std::unique_ptr<sql::ResultSet> _pResultSet;
};
#endif
