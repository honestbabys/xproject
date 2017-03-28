#include <fstream>
#include <iostream>
#include "Properties.h"
#include "Exception.h"

CProperties::CProperties(const std::string fileName):_strFileName(fileName)
{

}

CProperties::CProperties(const CProperties& copy) 
{
	_strFileName = copy._strFileName;
}

CProperties& CProperties::operator =(const CProperties& copy)
{
	if (this == &copy)
	{
		return *this;
	}
	_strFileName = copy._strFileName;
	return *this;
}

CProperties::~CProperties()
{

}

/*加载配置文件方法*/
void CProperties::loadProperties()
{
	char buf[MAX_LINE];
	memset(buf, 0, sizeof(buf));
	std::ifstream infile (_strFileName.c_str());
	//异常
	if (!infile)
	{
		throw;
	}

	std::string strSectionName;
	/*配置文件示例如下
	[1]
	MAXCONNECTION=300
	SERVER=INASTEST
	USER=INAS
	PASSWORD=SU5BUw==
	DATABASE=esri
	DBTYPE=ORACLE
	TESTSQL=select DUMMY from dual where 0=1
	DBALIAS=ORA
	*/
	while (!infile.eof())
	{
		infile.getline(buf, MAX_LINE);
		std::string tmp(buf);
		if (tmp.empty())
		{
			continue;
		}
		else if (tmp.at(0) == static_cast<char>('#'))
		{
			continue;
		}
		else if (tmp.find("[") != std::string::npos && tmp.find("]") != std::string::npos)
		{
			int ileft = tmp.find("[");
			int iright = tmp.find("]");
			strSectionName = tmp.substr(ileft + 1, iright - ileft - 1);
		}
		else
		{
			int ipos = tmp.find("=");
			if (ipos != std::string::npos)
			{
				std::map<std::string, std::map<std::string, std::string> >::iterator iterSection;
				if ((iterSection = _mapSection.find(strSectionName)) != _mapSection.end()) //找到了，直接将数据插入map中
				{
					(*iterSection).second.insert(std::map<std::string, std::string>::value_type(tmp.substr(0, ipos), tmp.substr(ipos + 1, tmp.length() - ipos - 1)));
				}
				else
				{
					std::map<std::string, std::string> mapContent;
					mapContent.insert(std::map<std::string, std::string>::value_type(tmp.substr(0, ipos), tmp.substr(ipos + 1, tmp.length() - ipos - 1)));
					_mapSection.insert(std::map<std::string, std::map<std::string, std::string> >::value_type(strSectionName, mapContent));
				}
			}
		}	
	}
}

/*打印配置文件内容*/
void CProperties::printProperties()
{
	std::map<std::string, std::map<std::string, std::string> >::iterator iter;
	for (iter= _mapSection.begin(); iter!= _mapSection.end(); iter++)
	{
		std::cout << "[" << (*iter).first << "]" << std::endl;
		std::map<std::string, std::string>::iterator iterContent;
		for (iterContent=(*iter).second.begin(); iterContent!=(*iter).second.end(); iterContent++)
		{
			std::cout << (*iterContent).first << "=" << (*iterContent).second << std::endl;
		}
		std::cout << std::endl;
	}
}

std::string CProperties::getValue(const std::string& sectionName, const std::string& key)
{
	std::map<std::string, std::map<std::string, std::string> >::iterator iterSection;
	if ((iterSection=_mapSection.find(sectionName)) != _mapSection.end())
	{
		std::map<std::string, std::string>::iterator iterContent;
		if ((iterContent=(*iterSection).second.find(key)) != (*iterSection).second.end())
		{
			return (*iterContent).second;
		} 
		else
		{
			//key不存在，抛出异常
			throw;
		}
	}
	else
	{
		//抛出异常，section不存在
		throw;
	}
}

std::string CProperties::getValue(const std::string& sectionName, const std::string& key, const std::string& defaultContent)
{
	std::map<std::string, std::map<std::string, std::string> >::iterator iterSection;
	if ((iterSection = _mapSection.find(sectionName)) != _mapSection.end())
	{
		std::map<std::string, std::string>::iterator iterContent;
		if ((iterContent = (*iterSection).second.find(key)) != (*iterSection).second.end())
		{
			return (*iterContent).second;
		}
		else
		{
			//key不存在，返回默认值
			return defaultContent;
		}
	}
	else
	{
		//抛出异常，section不存在
		throw;
	}
}

int CProperties::getSectionCount()
{
	return _mapSection.size();
}

std::map<std::string, std::string>* CProperties::getSectionUnit(const std::string& sectionName)
{
	std::map<std::string, std::map<std::string, std::string> >::iterator iterSection;
	if ((iterSection = _mapSection.find(sectionName)) != _mapSection.end())
	{
		return &(*iterSection).second;
	}
	else
	{
		throw CException(5001, "key does not exsit");
	}
}