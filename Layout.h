#ifndef _LOG_LAYOUT_H
#define _LOG_LAYOUT_H
#include <string>
class CLogEvent;
class CLayout 
{
public:
	virtual ~CLayout() {};
	virtual std::string format(const CLogEvent& logevent) = 0;
};
#endif // !_LOG_LAYOUT_H

