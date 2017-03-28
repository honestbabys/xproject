#ifndef _DB_DBCONNECTION_H
#define _DB_DBCONNECTION_H

#include <string>
#include <memory>
#include "DBProperties.h"

class CDBProperties;

class CDBConnection 
{
public:
	CDBConnection(const CDBProperties& property);
	virtual ~CDBConnection();
	//��ʼ�����ݿ����ӣ��û������룬�����ȵ�
	virtual void init() = 0;
	//����ִ��SQL
	virtual void setSQL(const std::string& sql) = 0;
	virtual void setSQL(const char* sql) = 0;
	//�����󶨣���int����
	//�������󶨵�ֵ
	virtual void bindInt(const int attrID, std::string& value) = 0;
	virtual void bindString(const int attrID, std::string& value) = 0;
	virtual void bindBlob(const int attrID, std::string& value) = 0;
	virtual void bindDate(const int attrID, std::string& value) = 0;
	//��ѯSQLִ��
	virtual void executeQuery() = 0;
	virtual void executeUpdate() = 0;
	virtual void executeProducure() = 0;
	//˳�����
	virtual void begin() = 0;
	virtual void commit() = 0;
	virtual void rollback() = 0;
	//������Ч���ж�
	virtual void connect() = 0;
	virtual bool isConnected() = 0;
	virtual void closeConnection() = 0;
	//�����ȡ
	virtual bool next() = 0;
	virtual const std::string getFieldName(unsigned int index) const = 0 ;
	virtual const std::string getString(unsigned int index) const = 0;
	virtual const int getInt(unsigned int index) const = 0;
	const unsigned int getFieldCount() const;
	const std::string getConnectionType() const;
protected:
	CDBProperties _CDBProperty;
	unsigned int _iRowCount;
	unsigned int _iFieldCount;
	std::string _strDBType;
private:
	//��ֹ��������ֵ����ʵ��
	CDBConnection(const CDBConnection& copy);
	const CDBConnection& operator=(const CDBConnection& copy);	
};
#endif
