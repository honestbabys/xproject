#ifndef _TOOLS_PARSER_H
#define _TOOLS_PARSER_H 
#include <string>
class CParser
{
public:
	CParser() {};
	virtual ~CParser() {};
	virtual void deSerialize(const std::string& request) = 0; //反序列化
	virtual std::string& serialize(const CParser& parser) = 0; //序列化
};
#endif // _TOOLS_PARSER_H
