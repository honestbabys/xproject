#ifndef _COMMON_RUNTIME_PARA_H
#define _COMMON_RUNTIME_PARA_H
#include <map>
#include <string>
class CRuntimePara
{
public:
	CRuntimePara();
	virtual ~CRuntimePara();
	CRuntimePara(const CRuntimePara& copy);
	const CRuntimePara& operator=(const CRuntimePara& copy);
	void assign(const std::map<std::string, std::string>& mapPara);
	void setString(const std::string& key, const std::string& val);
	void setInt(const std::string&key, int val);
	const std::string& getString(const std::string& key, const std::string& defalutVal);
	const std::string& getString(const std::string& key);
	int getInt(const std::string& key, const int defaultVal);
	int getInt(const std::string& key);
	void debug();
private:
	std::map<std::string, std::string> _mapPara;
};
#endif
