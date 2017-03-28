#include "Appender.h"
#include "Layout.h"
#include "Level.h"

void CAppender::doAppend(CLogEvent& logevent)
{
	if (_pLevel->isLevelOk(logevent.getLevel()))
	{
		std::string strLayout = _pLayout->format(logevent); //��̬����
		append(strLayout);//�����ܵ��ã�
	}
}

void CAppender::setLevel(std::shared_ptr<CLevel> level)
{
	_pLevel = level;
}

void CAppender::setLayOut(std::shared_ptr<CLayout> layout)
{
	_pLayout = layout;
}