#ifndef _COMMON_SUPER_TIME_H
#define _COMMON_SUPER_TIME_H

#include <string>

class CSuperTime
{
public:
	enum DateType
	{
		Y,
		MO,
		D,
		H,
		MI,
		S,
		MS
	};
	CSuperTime();
	CSuperTime(const std::string& strTime);
	CSuperTime(const std::string& strTime, const int iMicroSecond);
	virtual ~CSuperTime();
	CSuperTime& operator =(CSuperTime &);
	CSuperTime& format();
	CSuperTime& format(const std::string& strTime);
	CSuperTime& format(const std::string& strTime, const int iMicroSecond);
	std::string toString();
	std::string toStringMS(); 
	CSuperTime& refresh();
	int getRunDateId();
	int getRunTimeId();
	int getDateId();
	int getTimeId();
	std::string toYYYYMMDD();
	std::string toYYYYMMDDHHMMSS();
	std::string toYYYYMMDDHHMMSSMM();
	int getMicroSecond();
	int getSecond();
	int getMinute();
	int getDay();
	int getMon();
	int getYear();
	//重载双目运算符时使用友元的形式实现，避免ob=ob+100是被支持的，而ob=100+ob就是不被允许的这种问题出现
private:
	void getTm(struct tm& pointtime);
	bool isNegative(const int iNum);
	void clean();
	void arrange(const int iArrangeType);//iArrangeType == 0 ,正常时间,iArrangeType == 1,差值
	bool isBissextile(const int iYear); //是否闰年
	//函数设计的有问题
	int dayToYeah(int &iDay); //不需要返回值了，通过引用直接更改
	int dayToMonth(const int iYear, int&Day);
	int yearToDay(const int iYear, const int iTranType);
	int monthToDay30(const int iMonth);
	int monthToDay(const int iMonth, const int iYear);
	//注意返回引用的坑，特意返回引用做左值
	std::string& trim(std::string& stringcSource);

private:
	int _iYear;
	int _iMonth;
	int _iDay;
	int _iHour;
	int _iMinute;
	int _iSecond;
	int _iMicroSecond;
};
#endif