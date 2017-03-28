#include "LayoutFactory.h"
#include "Layout.h"
#include "SimpleLayout.h"

std::shared_ptr<CLayout> CLayoutFactory::createLayout(const std::string& layoutname)
{
	std::shared_ptr <CLayout> pClayout = nullptr;
	if (!layoutname.compare("SimpleLayout"))
	{
		pClayout = std::shared_ptr<CLayout>(new CSimpleLayout);
	}
	return pClayout;
}