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
