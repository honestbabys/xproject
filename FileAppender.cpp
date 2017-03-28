#include <sstream>
#include <fstream>
#include "FileAppender.h"
#include "Exception.h"
#include "Macroes.h"
#include "SuperTime.h"

CFileAppender::CFileAppender(const std::string& filePath, const std::string& fileName)
{
	_strFilePrex = filePath + fileName;
}

CFileAppender:: ~CFileAppender()
{
	close();
}

//如果保证是单例调用，还需要加锁？不用吧
void CFileAppender::append(const std::string& msg)
{
	try
	{
		refresh();
		_ofstream << msg;
		_ofstream.flush();
	}
	catch (...)
	{
		DEBUG("CFileAppender::append异常");
		throw CException(4001,"CFileAppender::append异常");
	}

}

void CFileAppender::refresh()
{
	CSuperTime tmp;
	if (_iDateID != tmp.getDateId())
	{
		close();
		open();
	}
}

void CFileAppender::open()
{
	try
	{
		CSuperTime tmp;
		_iDateID = tmp.getDateId();
		std::ostringstream os;
		//构造log文件名
		os << _strFilePrex << static_cast<int>(_iDateID / 10000) << "-" << static_cast<int>((_iDateID % 10000) / 100) << "-"
			<< static_cast<int>(_iDateID % 10000) << ".log";
		//打开文件句柄
		_ofstream.open(os.str().c_str(), std::ios::app);
	}
	catch (...)
	{
		DEBUG("CFileAppender::open()异常");
		throw CException(3003, "CFileAppender::open()异常");
	}
}

void CFileAppender::close()
{
	try
	{
		_ofstream.close();
	}
	catch (...)
	{
		DEBUG("CFileAppender::close()异常");
		throw CException(3002, "CFileAppender::close()异常");
	}
}