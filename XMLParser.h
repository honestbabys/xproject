#ifndef _TOOLS_XML_PARSER_H
#define _TOOLS_XML_PARSER_H
#include <map>
#include <string>
#include "Parser.h"
class CXMLParser :public CParser
{
public:
	CXMLParser();
	virtual ~CXMLParser();
	virtual void deSerialize(const std::string& request);
	virtual std::string& serialize(const CParser& parser);
private:
};
#endif
