#include <string>
#include "AppenderFactory.h"
#include "LayoutFactory.h"
#include "Properties.h"
#include "Layout.h"
#include "Level.h"
#include "ConsoleAppender.h"
#include "FileAppender.h"

CAppender* CAppenderFactory::createAppender(const std::string& appenderName, CProperties* property)
{
	CAppender *pCAppender = nullptr;
	std::shared_ptr<CLevel> pCLever = nullptr;
	try
	{
		std::string strLayOutType = property->getValue(appenderName, "LAYOUTTYPE", "");
		std::shared_ptr<CLayout> pCLayOut = CLayoutFactory::createLayout(strLayOutType);
		std::string strLevel = property->getValue(appenderName, "LEVEL", "");
		pCLever = std::shared_ptr<CLevel>(new CLevel());
		pCLever->setLevel(CLevel::getLevelValue(strLevel));
		if (appenderName.compare("CONSOLEAPPENDER")==0)
		{
			pCAppender = new CConsoleAppender();
		}
		else if (appenderName.compare("FILEAPPENDER"))
		{
			std::string strFileName = property->getValue(appenderName,"FILENAME","");
			std::string strFilePath = property->getValue(appenderName, "FILEPATH", "");
			pCAppender = new CFileAppender(strFilePath, strFileName);
		}
		pCAppender->setLayOut(pCLayOut);
		pCAppender->setLevel(pCLever);
	}
	catch (const std::exception&)
	{
		//资源在智能指针中管理，不需要delete了
		throw;
	}
	return pCAppender;
}