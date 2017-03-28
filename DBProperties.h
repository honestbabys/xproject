#ifndef _DB_DBPROPERTIES_H
#define _DB_DBPROPERTIES_H
#include <string>

class CDBProperties
{
public:
	CDBProperties();
	~CDBProperties();
	
	const int getMaxConnection() const;
	void setMaxConnection(const int iMaxconn);

	const std::string getServer() const; //const成员函数，并且函数返回值为const，不允许修改
	void setServer(const std::string& serverName);

	const std::string getUser() const;
	void setUser(const std::string& userName);

	const void setPort(const std::string port);
	const std::string& getPort() const;

	const std::string getPassword() const;
	void setPassword(const std::string& password);

	const std::string getDatabase() const;
	void setDatabase(const std::string& databaseName);

	const std::string getDBType() const;
	void setDBType(const std::string& dbtype);

	const std::string getTestSQL() const;
	void setTestSQL(const std::string& testsql);

	const int getNLS_LANG() const;
	void setNLS_LANG(const int lang = 0);

private:
	//最大连接数
	int _iMaxConnection;
	//数据库别名
	std::string _strServerName;
	//用户名
	std::string _strUserName;
	//密码
	std::string _strPassword;
	//数据库实例
	std::string _strDatabase;
	//数据库类型
	std::string _strDBtype;
	//测试语句
	std::string _strTestSQL;
	//语言设置
	int _iNLS_LANG;
	//端口号
	std::string _strPort;
};
#endif