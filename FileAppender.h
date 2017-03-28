#ifndef _LOG_FILE_APPENDER_H
#define _LOG_FILE_APPENDER_H

#include <string>
#include <fstream>
#include "Appender.h"

class CFileAppender :public CAppender
{
public:
	CFileAppender(const std::string& filePath, const std::string& fileName);
	virtual ~CFileAppender();
	virtual void append(const std::string& msg);

private:
	void refresh();
	void open();
	void close();

private:
	std::string _strFilePrex;
	std::ofstream _ofstream;
	int _iDateID;
};
#endif // !_LOG_FILE_APPENDER_H

