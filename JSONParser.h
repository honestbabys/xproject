#ifndef _TOOLS_JSON_PARSER_H
#define _TOOLS_JSON_PARSER_H
#include<string>
#include "Parser.h"

class CJSONParser: public CParser
{
public:
	CJSONParser();
	virtual ~CJSONParser();
	virtual void deSerialize(const std::string& request);
	virtual std::string& serialize(const CParser& parser);
private:
};
#endif
