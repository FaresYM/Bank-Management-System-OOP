#pragma once
#pragma warning (disable : 4996)

#include <iostream>
#include "Date.h"

using namespace std;

namespace Time
{

	time_t NumOfSecondsNow()
	{
		time_t Now = time(0);
		return Now;
	}

	time_t CurrentYear()
	{
		time_t Now = time(0);
		tm* Y = localtime(&Now);
		int Yr_Now = Y->tm_year + 1900;

		return Yr_Now;
	}

	time_t CurrentDayOfTheMonth()
	{
		time_t Day = time(0);
		tm* m_Day = localtime(&Day);

		return m_Day->tm_mday;
	}

	time_t CurrentDayOfTheWeek()
	{
		time_t Day = time(0);
		tm* w_Day = localtime(&Day);

		return w_Day->tm_wday;
	}

	time_t CurrentMonth()
	{
		time_t Now = time(0);
		tm* Mon_Now = localtime(&Now);

		Now = Mon_Now->tm_mon + 1;

		return Now;
	}

	time_t CurrentHour()
	{
		time_t Now = time(0);
		tm* Hr_Now = localtime(&Now);

		Now = Hr_Now->tm_hour;

		return Now;
	}

	time_t CurrentMinute()
	{
		time_t Min = time(0);
		tm* Min_Now = localtime(&Min);

		return Min_Now->tm_min;
	}

	time_t CurrentSecond()
	{
		time_t Sec = time(0);
		tm* Sec_Now = localtime(&Sec);

		return Sec_Now->tm_sec;
	}

	time_t NumOfDaysSince111()
	{
		time_t Now = 0;

		for (short i = 1; i < CurrentYear(); i++)
		{
			Now += Date::IsLeapYear(i) ? 366 : 365;
		}

		return Now;
	}

	time_t NumOfSecondsSince111()
	{
		const int SecondsInDay = 86400;

		return NumOfDaysSince111() * SecondsInDay;
	}

	time_t NumOfSecondsNow_2()
	{
		const short DaysBeforeMonth[] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
		time_t t = time(0);
		tm* Now = gmtime(&t);

		time_t Sec = 0;

		short Year = Now->tm_year + 1900;

		Sec = (Year - 1970) * 365;
		Sec += (Year - 1969) / 4;

		short Month = Now->tm_mon + 1;

		Sec += DaysBeforeMonth[Month];

		if (Month > 2 && Date::IsLeapYear(Year))
			Sec++;

		Sec += Now->tm_mday - 1;

		return Sec = ((Sec * 24 + Now->tm_hour) * 60 + Now->tm_min) * 60 + Now->tm_sec;
	}

}
