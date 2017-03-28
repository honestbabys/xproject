#include <sstream>
#include "SimpleLayout.h"
#include "LogEvent.h"
#include "Level.h"

std::string CSimpleLayout::format(const CLogEvent& logevent)
{
	std::string tmp;
	tmp.append(logevent.getTime());
	tmp.append(" ");
	tmp.append(CLevel::getLevelName(logevent.getLevel()));
	tmp.append(" [");
	tmp.append(logevent.getName());
	tmp.append(" ]");
	tmp.append(" ");
	tmp.append(logevent.getMsg());
	tmp.append("\n");
	return tmp;
}