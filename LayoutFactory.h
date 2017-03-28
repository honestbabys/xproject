#ifndef _LOG_LAYOUT_FACTORY_H
#define _LOG_LAYOUT_FACTORY_H

#include <string>
#include <memory>
class CLayout;

class CLayoutFactory 
{
public:
	static std::shared_ptr<CLayout> createLayout(const std::string& layoutname);
};
#endif // !_LOG_LAYOUT_FACTORY_H

