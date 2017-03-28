#ifndef _DB_MYSQL_DBCONNECTION_H
#define _DB_MYSQL_DBCONNECTION_H

#include <memory>
#include "DBConnection.h"

class CMySQLDBConnection : public CDBConnection
{
public:
	typedef enum DataType 
	{
		NUM_DATA_TYPE = 1,		/** ö�٣�NUM����*/
		STRING_DATA_TYPE = 2,	/** ö�٣�VARCHAR2����*/
		DATE_DATA_TYPE = 3,		/**ö��,DATE����*/
		BLOB_DATA_TYPE = 4	/**ö�٣�CBLOB����*/
	}DataType;

	CMySQLDBConnection(const CDBProperties& property);
	virtual ~CMySQLDBConnection();
	//��ʼ�����ݿ����ӣ��û������룬�����ȵ�
	virtual void init();
	//����ִ��SQL
	virtual void setSQL(const std::string& sql);
	virtual void setSQL(const char* sql);
	//�����󶨣���int����
	//�������󶨵�ֵ
	virtual void bindInt(const int attrID, std::string& value);
	virtual void bindString(const int attrID, std::string& value);
	virtual void bindBlob(const int attrID, std::string& value);
	virtual void bindDate(const int attrID, std::string& value);
	//��ѯSQLִ��
	virtual void executeQuery();
	virtual void executeUpdate();
	virtual void executeProducure();
	//˳�����
	virtual void begin();
	virtual void commit();
	virtual void rollback();
	//������Ч���ж�
	virtual void connect();
	virtual bool isConnected();
	virtual void closeConnection();
	//�����ȡ
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
	sql::Driver* _pDriver; //Driver����Ҫ�Լ��ͷ�
	std::unique_ptr<sql::Connection> _pConn;
	std::unique_ptr<sql::PreparedStatement> _pPreparedStmt;
	std::unique_ptr<sql::ResultSet> _pResultSet;
};
#endif
