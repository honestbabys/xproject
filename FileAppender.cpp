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

//�����֤�ǵ������ã�����Ҫ���������ð�
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
		DEBUG("CFileAppender::append�쳣");
		throw CException(4001,"CFileAppender::append�쳣");
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
		//����log�ļ���
		os << _strFilePrex << static_cast<int>(_iDateID / 10000) << "-" << static_cast<int>((_iDateID % 10000) / 100) << "-"
			<< static_cast<int>(_iDateID % 10000) << ".log";
		//���ļ����
		_ofstream.open(os.str().c_str(), std::ios::app);
	}
	catch (...)
	{
		DEBUG("CFileAppender::open()�쳣");
		throw CException(3003, "CFileAppender::open()�쳣");
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
		DEBUG("CFileAppender::close()�쳣");
		throw CException(3002, "CFileAppender::close()�쳣");
	}
}