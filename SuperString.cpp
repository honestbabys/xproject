#include <memory>  
#include <sstream>
#include "SuperString.h"
#include "Macroes.h"
#include "Exception.h"

/*将参数配置转换为vector形式保存*/
std::vector<std::string> CSuperString::getTokenList(const std::string& msg, const std::string& token)
{
	std::vector<std::string> slist;
	std::string tmp = msg;
	int ipos = 0;
	DEBUG("Token msg = %s, token = %s ", msg.c_str(), token.c_str());
	while (ipos != std::string::npos)
	{
		ipos = tmp.find(token);
		if (ipos != std::string::npos)
		{
			slist.push_back(tmp.substr(0, ipos));
		}
		tmp = tmp.substr(ipos + token.length(), tmp.length() - token.length() - ipos);
	}
	if (tmp.length() >0 )
	{
		slist.push_back(tmp);
	}
	return slist;
}

/*将参数配置转换为map形式保存*/
std::map<std::string, std::string> CSuperString::getTokenMap(const std::string&msg, const std::string&token1, const std::string& token2)
{
	std::map<std::string, std::string> smap;
	std::vector<std::string> list = getTokenList(msg, token1);
	try
	{
		std::vector<std::string>::iterator iterlist;
		for (iterlist = list.begin(); iterlist != list.end(); iterlist++);
		{
			DEBUG("content = %s ", (*iterlist).c_str());
			std::vector<std::string> vectmp = getTokenList((*iterlist), token2);
			if (vectmp.size() !=2)
			{
				std::string strErrMsg = "参数：" + *iterlist + "配置错误";
				DEBUG(strErrMsg.c_str());
				throw CException(4001, strErrMsg.c_str());
			}
			smap[vectmp[0]] = vectmp[1];
		}
	}
	catch (CException& e)
	{
		throw CException(e.errCode(), e.what());
	}
}

std::string CSuperString::vstrprintf(const char* format, va_list args)
{
	int isize = 1024;
	char *buffer = new char[isize];
	while (true)
	{
		int n = vsnprintf(buffer, sizeof(buffer), format, args);
		if (n > -1 && n < isize)
		{
			std::string s(buffer);
			delete[] buffer;
			buffer = nullptr;
			return s;
		}
		if ( n>-1) //重新分配大小
		{
			isize = n + 1;
		}
		else
		{
			isize *= 2;
		}
		delete[] buffer;
		buffer = nullptr;
		buffer = new char[isize];
	}
}

std::string CSuperString::xprintf(const char* format, ...)
{
	std::string strTmp;
	va_list va;
#ifdef Linux
	va_start(va, format);
	va_end(va);
#endif
	__crt_va_start(va, format);
	__crt_va_end(va);
	return strTmp;
}

std::string CSuperString::uperCase(const std::string& s)
{
	char* buf = new char[s.length()];
	memset(buf, 0, sizeof(buf));
	s.copy(buf, s.length());
	for (int i=0; i<s.length(); i++)
	{
		buf[i] = toupper(buf[i]);
	}
	std::string r(buf, s.length());
	delete[] buf;
	buf = nullptr;
	return r;
}

std::string CSuperString::lowCase(const std::string& s)
{
	char* buf = new char[s.length()];
	memset(buf, 0, s.length());
	for (int i=0; i<s.length();i++)
	{
		buf[i] = tolower(buf[i]);
	}
	std::string r(buf, s.length());
	return r;
}

std::vector<std::string> CSuperString::getBrackets(const std::string& s)
{
	std::vector<std::string> ret;
	std::string strtmp(s);
	int lt, gt;
	while (strtmp.length() >0)
	{
		lt = strtmp.find_first_of("<");
		gt = strtmp.find_last_of(">");
		ret.push_back(strtmp.substr(lt + 1, gt - lt - 1));
		strtmp = strtmp.substr(gt + 1);
	}
	return ret;
}

int CSuperString::toInt(const std::string& s)
{
	int iret = atoi(s.c_str());
	return iret;
}

void CSuperString::toUpper(std::string& strOrig)
{
	if (strOrig.length()>0)
	{
		char* ptmp = new char[strOrig.length() + 1];
		strncpy(ptmp, strOrig.c_str(), strOrig.length());
		for (int i=0; i<strOrig.length(); i++)
		{
			if (ptmp[i]>96 && ptmp[i]<123)
			{
				ptmp -= 32;
			}
		}
		strOrig = std::string(ptmp);
		delete[] ptmp;
		ptmp = nullptr;
	}
}


void CSuperString::toLower(std::string& strOrig)
{
	if (strOrig.length() > 0)
	{
		char* ptmp = new char[strOrig.length() + 1];
		strncpy(ptmp, strOrig.c_str(), strOrig.length());
		for (int i = 0; i < strOrig.length(); i++)
		{
			if (ptmp[i] > 64 && ptmp[i] < 91)
			{
				ptmp += 32;
			}
		}
		strOrig = std::string(ptmp);
		delete[] ptmp;
		ptmp = nullptr;
	}
}

bool CSuperString::compareIgnoreCase(const std::string& first, const std::string& second)
{
	std::string strFirst = first;
	std::string strSecond = second;
	toUpper(strFirst);
	toUpper(strSecond);
	if (strFirst.compare(strSecond) ==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string CSuperString::toString(int m)
{
	std::ostringstream os;
	os << m;
	return os.str();
}