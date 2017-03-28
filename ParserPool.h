#ifndef _TOOLS_PARSER_POOL_H
#define _TOOLS_PARSER_POOL_H
#include <map>
#include <string>
class CParser;
class CParserPool 
{
public:
	CParserPool();
	~CParserPool();
	CParser* getParser();
private:
	std::map<std::string, CParser*> _mapParserPool;
};
#endif // !_TOOLS_PARSER_POOL_H
