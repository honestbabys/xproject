#include "ParserFactory.h"
#include "XMLParser.h"
#include "JSONParser.h"
#include "ScopedLock.h"

CParserFactory* CParserFactory::_instance = nullptr;

CParserFactory* CParserFactory::getInstance()
{
	if (_instance == nullptr)
	{
		CSocpedLock lock();
		if (_instance == nullptr)
		{
			_instance = new CParserFactory;
		}
	}
	return _instance;
}

void CParserFactory::close()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}

CParser* CParserFactory::createParser(const std::string& type)
{
	CParser* parser = nullptr;
	if (type.compare("XML") == 0)
	{
		parser = new CXMLParser();
	} 
	else if(type.compare("JSON") == 0)
	{
		parser = new CJSONParser();
	}
	return parser;
}