#ifndef _LOG_SIMPLE_LAYOUT_H
#define _LOG_SIMPLE_LAYOUT_H
#include "Layout.h"

class CSimpleLayout: public CLayout
{
public:
	virtual ~CSimpleLayout() {};
	virtual std::string format(const CLogEvent& logevent);
};
#endif // !_LOG_SIMPLE_LAYOUT_H

