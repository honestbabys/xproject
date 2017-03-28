#include <iostream>
#include "ConsoleAppender.h"

void CConsoleAppender::append(const std::string& msg)
{
	std::cout << msg << std::endl;
}