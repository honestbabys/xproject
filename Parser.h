#ifndef _TOOLS_PARSER_H
#define _TOOLS_PARSER_H 
#include <string>
class CParser
{
public:
	CParser() {};
	virtual ~CParser() {};
	virtual void deSerialize(const std::string& request) = 0; //�����л�
	virtual std::string& serialize(const CParser& parser) = 0; //���л�
};
#endif // _TOOLS_PARSER_H
