#ifndef _DB_CONNECTION_FACTORY_H
#define _DB_CONNECTION_FACTORY_H

//单例模式实现
class CConnectionFactory 
{
public:
	static CConnectionFactory* getInstance();
	static CConnectionFactory* _instance;
	static void close();
	CDBConnection* getDBConnection(const CDBProperties& property);
private:
	//私有化构造，拷贝，析构函数
	CConnectionFactory();
	CConnectionFactory(const CConnectionFactory& copy);
	virtual ~CConnectionFactory() {};
};
#endif