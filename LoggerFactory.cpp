#include <vector>
#include "LoggerFactory.h"
#include "Properties.h"
#include "Logger.h"
#include "SuperString.h"
#include "AppenderFactory.h"
#include "Appender.h"

CLogger* CLoggerFactory::createLogger(const std::string& loggerName, CProperties* property)
{
	CLogger* plogger = nullptr;
	try
	{
		plogger = new CLogger(loggerName);
		std::vector <std::string> vecAppender;
		std::string strAppender = property->getValue("LOGGER", "APPENDERS", "");
		vecAppender = CSuperString::getTokenList(strAppender, ",");
		for (std::vector <std::string>::iterator iterAppender= vecAppender.begin(); iterAppender!=vecAppender.end(); iterAppender++)
		{
			CAppender *pCAppender = nullptr;
			try
			{
				pCAppender = CAppenderFactory::createAppender(*iterAppender, property);
				pCAppender->open();
				plogger->addAppender(std::unique_ptr<CAppender>(pCAppender));
			}
			catch (const std::exception&)
			{
				if (pCAppender != nullptr)
				{
					delete pCAppender;
					pCAppender = nullptr;
				}
				throw;
			}
		}
	}
	catch (const std::exception&)
	{
		if (plogger != nullptr)
		{
			delete plogger;
			plogger = nullptr;
		}
		throw;
	}
	return plogger;
}