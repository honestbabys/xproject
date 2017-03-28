#ifndef _DB_CONNECTION_FACTORY_H
#define _DB_CONNECTION_FACTORY_H

//����ģʽʵ��
class CConnectionFactory 
{
public:
	static CConnectionFactory* getInstance();
	static CConnectionFactory* _instance;
	static void close();
	CDBConnection* getDBConnection(const CDBProperties& property);
private:
	//˽�л����죬��������������
	CConnectionFactory();
	CConnectionFactory(const CConnectionFactory& copy);
	virtual ~CConnectionFactory() {};
};
#endif