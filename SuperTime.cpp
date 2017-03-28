#include <string>
#include <vector>
#include <map>
#include <time.h>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include "SuperTime.h"
#include "SuperString.h"
#include "Exception.h"
#include "Macroes.h"

CSuperTime::CSuperTime():_iYear(0),_iMonth(0),_iDay(0),_iHour(0),_iMinute(0),_iSecond(0),_iMicroSecond(0)
{

}

CSuperTime::CSuperTime(const std::string& strTime) 
{
	format(strTime);
}

CSuperTime::CSuperTime(const std::string& strTime, const int iMicroSecond)
{
	format(strTime, iMicroSecond);
}

CSuperTime::~CSuperTime() 
{

}

CSuperTime& CSuperTime::operator =(CSuperTime& superTime)
{
	//自赋值检查
	if (this == &superTime)
	{
		return *this;
	}
	_iYear = superTime._iYear;
	_iMonth = superTime._iMonth;
	_iDay = superTime._iDay;
	_iHour = superTime._iHour;
	_iMinute = superTime._iMinute;
	_iSecond = superTime._iSecond;
	_iMicroSecond = superTime._iMicroSecond;
}

CSuperTime& CSuperTime::format()
{
	refresh();
	return *this;
}

CSuperTime& CSuperTime::format(const std::string& strTime)
{
	std::string strTime;
	int iDay = 0;
	std::string strCurVal = strTime;
	trim(strCurVal);
	std::map<std::string, int> mapMonth;
	mapMonth["Jan"] = 1;
	mapMonth["Feb"] = 2;
	mapMonth["Mar"] = 3;
	mapMonth["Apr"] = 4;
	mapMonth["May"] = 5;
	mapMonth["Jun"] = 6;
	mapMonth["Jul"] = 7;
	mapMonth["Aug"] = 8;
	mapMonth["Sep"] = 9;
	mapMonth["Oct"] = 10;
	mapMonth["Nov"] = 11;
	mapMonth["Dec"] = 12;
	mapMonth["1月"] = 1;
	mapMonth["2月"] = 2;
	mapMonth["3月"] = 3;
	mapMonth["4月"] = 4;
	mapMonth["5月"] = 5;
	mapMonth["6月"] = 6;
	mapMonth["7月"] = 7;
	mapMonth["8月"] = 8;
	mapMonth["9月"] = 9;
	mapMonth["10月"] = 10;
	mapMonth["11月"] = 11;
	mapMonth["12月"] = 12;

	std::map<std::string, int> mapDay;
	for (int i=1; i<=31; i++) 
	{
		std::string strTmpDay = CSuperString::toString(i) + "日";
		mapDay.insert(std::map<std::string, int>::value_type(strTmpDay, i));
	}

	if (strCurVal.length() <= 0) //没输如入时间，之间传回当前时间
	{
		refresh();
	}
	else
	{
		std::vector<std::string> vecTimePart;
		//期望时间格式如2015-11-19 18:21:00
		vecTimePart = CSuperString::getTokenList(strCurVal, " ");
		//2015-11-19
		std::vector<std::string>::iterator iterTimePart = vecTimePart.begin();
		std::vector<std::string> vecDate = CSuperString::getTokenList(*iterTimePart, "-");
		if (vecDate.size() != 3)
		{
			throw CException(5001, "日期格式错误");
		}
		_iYear = CSuperString::toInt(vecDate[0]);
		_iMonth = CSuperString::toInt(vecDate[1]);
		_iDay = CSuperString::toInt(vecDate[2]);

		++iterTimePart;
		// 18:21:00
		std::vector<std::string> vecTime = CSuperString::getTokenList(*iterTimePart, ":");
		_iHour = CSuperString::toInt(vecTime[0]);
		_iMinute = CSuperString::toInt(vecTime[1]);
		_iSecond = CSuperString::toInt(vecTime[2]);
		_iMicroSecond = 0;
		return *this;
	}
}

CSuperTime& CSuperTime::format(const std::string& strTime, const int iMicroSecond) 
{
	format(strTime);
	_iMicroSecond = iMicroSecond;
	return *this;
}

std::string CSuperTime::toString()
{
	char cRet[30] = { 0 };
	sprintf(cRet, "%d-%02d-%02d %02d:%02d:%02d", _iYear, _iMonth, _iDay, _iHour, _iMinute, _iSecond);
	return std::string(cRet);
}

std::string CSuperTime::toStringMS()
{
	char cRet[30] = { 0 };
	sprintf(cRet, "%d-%02d-%02d %02d:%02d:%02d %6d", _iYear, _iMonth, _iDay, _iHour, _iMinute, _iSecond,_iMicroSecond);
	return std::string(cRet);
}

#ifdef WIN32
static int gettimeofday(struct timeval* tp, void* tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#endif

CSuperTime& CSuperTime::refresh()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t currentTime = tv.tv_sec;
	struct tm nowTime;
#ifdef Linux
	localtime_r(&currentTime, &nowTime);
#endif 
	localtime_s(&nowTime, &currentTime);
	_iMicroSecond = tv.tv_usec;
	_iYear = nowTime.tm_year + 1900;
	_iMonth = nowTime.tm_mon + 1;
	_iDay = nowTime.tm_mday;
	_iHour = nowTime.tm_hour;
	_iMinute = nowTime.tm_min;
	_iSecond = nowTime.tm_sec;
	return *this; //注意，返回当前对象
}

int CSuperTime::getRunDateId()
{
	int iRet = 0;
	struct tm pointtime;
	getTm(pointtime);
	iRet = ((pointtime.tm_year + 1900) * 10000 + (pointtime.tm_mon + 1) * 100 + pointtime.tm_yday);
	return iRet;
}

int CSuperTime::getRunTimeId() 
{
	int iRet = 0;
	struct tm pointtime;
	getTm(pointtime);
	iRet = (pointtime.tm_hour*10000 + pointtime.tm_min*100 + pointtime.tm_sec);
	return iRet;
}

int CSuperTime::getDateId()
{
	int iRet = 0;
	iRet = _iYear * 10000 + _iMonth * 100 + _iDay;
	return iRet;
}

int CSuperTime::getTimeId()
{
	int iRet = 0;
	iRet = _iHour * 10000 + _iMinute * 100 + _iSecond;
	return iRet;
}

std::string CSuperTime::toYYYYMMDD()
{
	char cRet[30];
	sprintf(cRet, "%d%02d%02d", _iYear, _iMonth, _iDay);
	return std::string(cRet, strlen(cRet));
}

std::string CSuperTime::toYYYYMMDDHHMMSS()
{
	char cRet[30];
	sprintf(cRet, "%d%02d%02d%02d%02d%02d", _iYear, _iMonth, _iDay,_iHour,_iMinute,_iSecond);
	return std::string(cRet, strlen(cRet));
}

std::string CSuperTime::toYYYYMMDDHHMMSSMM()
{
	char cRet[30];
	sprintf(cRet, "%d%02d%02d%02d%02d%02d%02d", _iYear, _iMonth, _iDay, _iHour, _iMinute, _iSecond,_iMicroSecond);
	return std::string(cRet, strlen(cRet));
}

int CSuperTime::getMicroSecond()
{
	return _iMicroSecond;
}

int CSuperTime::getSecond()
{
	return _iSecond;
}

int CSuperTime::getMinute()
{
	return _iMinute;
}

int CSuperTime::getDay()
{
	return _iDay;
}

int CSuperTime::getMon()
{
	return _iMonth;
}

int CSuperTime::getYear()
{
	return _iYear;
}

void CSuperTime::getTm(struct tm& pointtime)
{
	time_t currentime;
	currentime = time(0);
#ifdef Linux
	localtime_r(&currenttime, &pointtime);
#endif
	localtime_s(&pointtime, &currentime);
}

bool CSuperTime::isNegative(const int iNum)
{
	if (iNum < 0)
	{
		return false;
	} 
	else
	{
		return true;
	}
}

void CSuperTime::clean()
{
	_iYear = 0;
	_iMonth = 0;
	_iDay = 0;
	_iHour = 0;
	_iMinute = 0;
	_iSecond = 0;
	_iMicroSecond = 0;
}

//意图是什么？
void CSuperTime::arrange(const int iArrangeType)
{
	int itempDay = 0;
	switch (iArrangeType)
	{
	case 0:
		while (_iMicroSecond > 999999)
		{
			_iMicroSecond -= 1000000;
			++_iSecond;
		}
		while (_iMicroSecond < 0)
		{
			_iMicroSecond += 1000000;
			--_iSecond;
		}
		while (_iSecond > 59)
		{
			_iSecond -= 60;
			++_iMinute;
		}
		while (_iSecond < 0)
		{
			_iSecond += 60;
			--_iMinute;
		}
		while (_iMinute > 59)
		{
			_iMinute -= 60;
			++_iHour;
		}
		while (_iMinute < 0)
		{
			_iMinute += 60;
			--_iHour;
		}
		while (_iHour > 23)
		{
			_iHour -= 24;
			++_iDay;
		}
		while (_iHour < 0)
		{
			_iHour += 24;
			--_iDay;
		}
		itempDay += yearToDay(_iYear, 1);
		itempDay += monthToDay(_iMonth, _iYear);
		itempDay += _iDay;

		_iYear = dayToYeah(itempDay);
		_iMonth = dayToMonth(_iYear, itempDay);
		_iDay = itempDay;
		break;
	default:
		if (isNegative(_iDay))
		{
			while (_iMicroSecond > 999999)
			{
				_iMicroSecond -= 1000000;
				++_iSecond;
			}
			while (_iMicroSecond < 0)
			{
				_iMicroSecond += 1000000;
				--_iSecond;
			}
			while (_iSecond > 59)
			{
				_iSecond -= 60;
				++_iMinute;
			}
			while (_iSecond < 0)
			{
				_iSecond += 60;
				--_iMinute;
			}
			while (_iMinute > 59)
			{
				_iMinute -= 60;
				++_iHour;
			}
			while (_iMinute < 0)
			{
				_iMinute += 60;
				--_iHour;
			}
			while (_iHour > 23)
			{
				_iHour -= 24;
				++_iDay;
			}
			while (_iHour < 0)
			{
				_iHour += 24;
				--_iDay;
			}
			while (_iDay > 364)
			{
				_iDay -= 365;
				_iYear++;
			}
			while (_iDay > 29)
			{
				_iDay -= 30;
				_iMonth++;
			}
			while (_iMonth > 11)
			{
				_iMonth -= 12;
				_iYear++;
			}
		}
		else
		{
			_iSecond -= 86400;
			_iDay++;
			while (_iMicroSecond < -999999)
			{
				_iMicroSecond += 1000000;
				_iSecond--;
			}
			while (_iSecond < -59)
			{
				_iSecond += 60;
				_iMinute--;
			}
			while (_iMinute < -59)
			{
				_iMinute += 60;
				_iHour--;
			}
			while (_iHour < -23)
			{
				_iHour += 24;
				_iDay--;
			}
			while (_iDay < 364)
			{
				_iDay += 365;
				_iYear--;
			}
			while (_iDay < -29)
			{
				_iDay += 30;
				_iMonth--;
			}
			while (_iMonth < -11)
			{
				_iMonth += 12;
				_iYear--;
			}
		}
		break;
	}
}

bool CSuperTime::isBissextile(const int iYear)
{
	if ((iYear % 4) !=0)
	{
		return false;
	}
	else if ((iYear % 100) !=0)
	{
		return true;
	}
	else if ((iYear % 400) != 0)
	{
		return false;
	}
	else
	{
		return false;
	}
}
									
int CSuperTime::dayToYeah(int &iDay)
{
	int iRet = 1900;
	int iDayDiff = iDay;
	while (iDayDiff > isBissextile(iRet) + 365)
	{
		iDayDiff -= isBissextile(iRet) + 365;
		iRet++;
	}
	iDay = iDayDiff;
	return iRet;
}

int CSuperTime::dayToMonth(const int iYear, int&Day)
{
	struct tm tmCurren;
	tmCurren.tm_mday = iDay;
	tmCurren.tm_mon = 1;//标准时间以0月开始,所以这里为了方便理解定为1.成为自然月
	if (tmCurren.tm_mday > 31) //2月 >31就说明是二月,tmCurren.tm_mon从1变为2,并且判断标准是上个月的最大天数
	{
		tmCurren.tm_mon++;
		tmCurren.tm_mday -= 31;
		if (tmCurren.tm_mday > 28 + isBissextile(iYear))//3月
		{
			tmCurren.tm_mon++;
			tmCurren.tm_mday -= 28 + isBissextile(iYear);
			if (tmCurren.tm_mday > 31) //4月
			{
				tmCurren.tm_mon++;
				tmCurren.tm_mday -= 31;
				if (tmCurren.tm_mday > 30) //5月
				{
					tmCurren.tm_mon++;
					tmCurren.tm_mday -= 30;
					if (tmCurren.tm_mday > 31) //6月
					{
						tmCurren.tm_mon++;
						tmCurren.tm_mday -= 31;
						if (tmCurren.tm_mday > 30) //7月
						{
							tmCurren.tm_mon++;
							tmCurren.tm_mday -= 30;
							if (tmCurren.tm_mday > 31) //8月
							{
								tmCurren.tm_mon++;
								tmCurren.tm_mday -= 31;
								if (tmCurren.tm_mday > 31) //9月
								{
									tmCurren.tm_mon++;
									tmCurren.tm_mday -= 31;
									if (tmCurren.tm_mday > 30) //10月
									{
										tmCurren.tm_mon++;
										tmCurren.tm_mday -= 30;
										if (tmCurren.tm_mday > 31) //11月
										{
											tmCurren.tm_mon++;
											tmCurren.tm_mday -= 31;
											if (tmCurren.tm_mday > 30) //12月
											{
												tmCurren.tm_mon++;
												tmCurren.tm_mday -= 30;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	iDay = tmCurren.tm_mday;
	return tmCurren.tm_mon;
}

int CSuperTime::yearToDay(const int iYear, const int iTranType)
{
	int iRet = 0;
	int iYearDiff = 0;
	iYearDiff = abs(iYear) - 1900 * iTranType;
	for (int i = 0; i < iYearDiff; i++)
	{
		iRet = iRet + isBissextile(1900 + i) * iTranType + 365;
	}
	return iRet * isNegative(iYear);
}

int CSuperTime::monthToDay30(const int iMonth)
{
	return 30 * iMonth;
}

int CSuperTime::monthToDay(const int iMonth, const int iYear)
{
	int iRet = 0;
	int iTemp = iMonth;//时间以1月开始,为自然月
	if ((iYear >= 1900) && (iMonth > 0))
	{
		do
		{
			switch (iTemp)
			{
			case 2://如果自然月为2月,表明包含1月的31天.下同.
				iRet += 31;
				break;
			case 3:
				iRet = iRet + 28 + isBissextile(iYear); //这里考虑闰年,闰年的情况由isBissextile()决定
				break;
			case 4:
				iRet += 31;
				break;
			case 5:
				iRet += 30;
				break;
			case 6:
				iRet += 31;
				break;
			case 7:
				iRet += 30;
				break;
			case 8:
				iRet += 31;
				break;
			case 9:
				iRet += 31;
				break;
			case 10:
				iRet += 30;
				break;
			case 11:
				iRet += 31;
				break;
			case 12:
				iRet += 30;
				break;
			case 1://如果是一月,则天数由Day决定,而月份不代表一定包含多少天,故什么也不做
				break;
			default:
				break;
			}

			iTemp--;
		} while (iTemp > 0);
	}
	else
	{
		iRet += monthToDay30(abs(iMonth));
	}
	return  iRet * isNegative(iMonth);
}

std::string& CSuperTime::trim(std::string& stringcSource)
{
	std::string strsplit = "\n\t";
	int iTemp = 0;
	while ((iTemp = stringcSource.find_last_of(strsplit) + 1) == (stringcSource.length()))
	{
		stringcSource.erase(iTemp);
	}
	stringcSource.erase(0, stringcSource.find_last_of(strsplit));
	return stringcSource;
}