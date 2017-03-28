#ifndef _COMMON_SUPER_STRING_H
#define _COMMON_SUPER_STRING_H

#include <string>
#include <vector>
#include <map>

class CSuperString 
{
public:
	static std::vector<std::string>getTokenList(const std::string& msg, const std::string& token);
	static std::map<std::string, std::string>getTokenMap(const std::string&msg, const std::string&token1, const std::string& token2);
	static std::string vstrprintf(const char* format, va_list args);
	static std::string xprintf(const char* format, ...);
	static std::string uperCase(const std::string& s);
	static std::string lowCase(const std::string& s);
	static std::vector<std::string> getBrackets(const std::string& s);
	static int toInt(const std::string& s);
	static void toUpper(std::string& strOrig);
	static void toLower(std::string& strOrig);
	static bool compareIgnoreCase(const std::string& first, const std::string& second);
	static std::string toString(int m);
private:

};
#endif
