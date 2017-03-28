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

	const std::string getServer() const; //const��Ա���������Һ�������ֵΪconst���������޸�
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
	//���������
	int _iMaxConnection;
	//���ݿ����
	std::string _strServerName;
	//�û���
	std::string _strUserName;
	//����
	std::string _strPassword;
	//���ݿ�ʵ��
	std::string _strDatabase;
	//���ݿ�����
	std::string _strDBtype;
	//�������
	std::string _strTestSQL;
	//��������
	int _iNLS_LANG;
	//�˿ں�
	std::string _strPort;
};
#endif