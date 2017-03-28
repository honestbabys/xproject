#include "RuntimePara.h"
#include "SuperString.h"
#include "Exception.h"
#include "Macroes.h"

CRuntimePara::CRuntimePara()
{

}

CRuntimePara::~CRuntimePara()
{
	debug();
}

CRuntimePara::CRuntimePara(const CRuntimePara& copy)
{
	_mapPara = copy._mapPara;
}

const CRuntimePara& CRuntimePara::operator=(const CRuntimePara& copy)
{
	//×Ô¸³Öµ¼ì²é
	if (this == &copy)
	{
		return *this;
	}
	_mapPara = copy._mapPara;
	return *this;
}

void CRuntimePara::assign(const std::map<std::string, std::string>& mapPara)
{
	for (auto iter= mapPara.begin(); iter!= mapPara.end(); iter++)
	{
		setString((*iter).first, (*iter).second);
	}
}

void CRuntimePara::setString(const std::string& key, const std::string& val)
{
	std::map<std::string, std::string>::iterator iter;
	if ((iter = _mapPara.find(key)) != _mapPara.end())
	{
		(*iter).second = val;
	}
	else
	{
		_mapPara.insert(std::map<std::string, std::string>::value_type(key, val));
	}
}

void CRuntimePara::setInt(const std::string&key, int val)
{
	std::map<std::string, std::string>::iterator iter;
	if ((iter = _mapPara.find(key)) != _mapPara.end())
	{
		(*iter).second = CSuperString::toString(val);
	}
	else
	{
		_mapPara.insert(std::map<std::string, std::string>::value_type(key, CSuperString::toString(val)));
	}
}

const std::string& CRuntimePara::getString(const std::string& key, const std::string& defaultVal)
{
	std::map<std::string, std::string>::iterator iter;
	if ((iter = _mapPara.find(key)) != _mapPara.end())
	{
		return (*iter).second;
	}
	else
	{
		return defaultVal;
	}
}

const std::string& CRuntimePara::getString(const std::string& key)
{
	std::map<std::string, std::string>::iterator iter;
	if ((iter = _mapPara.find(key)) != _mapPara.end())
	{
		return (*iter).second;
	}
	else
	{
		throw CException(70001, "key does not exist");
	}
}

int CRuntimePara::getInt(const std::string& key, const int defaultVal)
{
	std::map<std::string, std::string>::iterator iter;
	if ((iter = _mapPara.find(key)) != _mapPara.end())
	{
		return CSuperString::toInt((*iter).second);
	}
	else
	{
		return defaultVal;
	}
}

int CRuntimePara::getInt(const std::string& key)
{
	std::map<std::string, std::string>::iterator iter;
	if ((iter = _mapPara.find(key)) != _mapPara.end())
	{
		return CSuperString::toInt((*iter).second);
	}
	else
	{
		throw CException(70001, "key does not exist");
	}
}

void CRuntimePara::debug()
{
	for (const auto& iter: _mapPara)
	{
		DEBUG("key:%s<------------->value:%s", (*iter).first.to_str(), (*iter).second.to_str());
	}
}