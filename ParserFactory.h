#ifndef _TOOLS_PARSER_FACTORY
#define _TOOLS_PARSER_FACTORY
#include <string>
class CParser;
class CParserFactory
{
public:
	static CParserFactory* getInstance();
	static void close();
	CParser* createParser(const std::string& type);
public:
	static CParserFactory* _instance;
private:
	const CParserFactory& operator=(const CParserFactory& copy);
	CParserFactory(const CParserFactory& copy);
	CParserFactory();
	~CParserFactory() {};
};
#endif // !_TOOLS_PARSER_FACTORY

