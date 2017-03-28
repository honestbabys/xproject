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
	//����˫Ŀ�����ʱʹ����Ԫ����ʽʵ�֣�����ob=ob+100�Ǳ�֧�ֵģ���ob=100+ob���ǲ�������������������
private:
	void getTm(struct tm& pointtime);
	bool isNegative(const int iNum);
	void clean();
	void arrange(const int iArrangeType);//iArrangeType == 0 ,����ʱ��,iArrangeType == 1,��ֵ
	bool isBissextile(const int iYear); //�Ƿ�����
	//������Ƶ�������
	int dayToYeah(int &iDay); //����Ҫ����ֵ�ˣ�ͨ������ֱ�Ӹ���
	int dayToMonth(const int iYear, int&Day);
	int yearToDay(const int iYear, const int iTranType);
	int monthToDay30(const int iMonth);
	int monthToDay(const int iMonth, const int iYear);
	//ע�ⷵ�����õĿӣ����ⷵ����������ֵ
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