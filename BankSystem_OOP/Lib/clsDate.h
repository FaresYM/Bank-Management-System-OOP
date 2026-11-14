#pragma warning(disable : 4996)
#pragma once

#include <iostream>
#include <string>
#include "clsString.h"

using namespace std;

class clsDate
{
private:
	short _Day;
	short _Month;
	short _Year;

public:

	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;

	}

	clsDate(string Date)
	{
		vector <string> vDate;

		vDate = clsString::SplitString(Date, "/");

		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DayOrderInYear, short Year)
	{
		clsDate Date = GetDateFromDayOrderInYear(DayOrderInYear, Year);

		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}

	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}

	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear()
	{
		return _Year;
	}

	_declspec(property(get = GetDay, put = SetDay)) short Day;
	_declspec(property(get = GetMonth, put = SetMonth)) short Month;
	_declspec(property(get = GetYear, put = SetYear)) short Year;

	static clsDate GetSystemDate()
	{
		clsDate Date;

		time_t t = time(0);
		tm* now = localtime(&t);

		Date.Day = now->tm_mday;
		Date.Month = now->tm_mon + 1;
		Date.Year = now->tm_year + 1900;

		return Date;
	}

	static string GetSystemDateTimeString()
	{
		//System Datetime String
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	void Print()
	{
		cout << DateToString() << endl;
	}

	static bool IsLeapYear(short Year)
	{
		return (Year % 400 == 0) ? true : (Year % 4 == 0) and (Year % 100 != 0) ? true : false;
	}

	bool IsLeapYear()
	{
		IsLeapYear(_Year);
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{
		return Month < 1 || Month > 12 ? 0 : Month == 2 ? IsLeapYear(Year) ? 29 : 28 :
			Month == 4 or Month == 6 or Month == 9 or Month == 11 ? 30 : 31;
	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Month, _Year);
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		short a, y, m;

		a = (14 - Date.Month) / 12;
		y = Date.Year - a;
		m = Date.Month + (12 * a) - 2;

		return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		//The Inner ternary operator beside it is its true and its false is the outer false
		//The Middle ternary operator beside it is its true and its false is the middle false
		//The Outer ternary operator besite it is its true and its false is the inner false
		return (Date1.Year < Date2.Year) ? true : (Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month) ? true :
			(Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) ? true : false : false : false;
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return Date1.Day == Date2.Day && Date1.Month == Date2.Month && Date1.Year == Date2.Year ? true : false;
	}

	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;
		else if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		return enDateCompare::After;
	}

	enDateCompare CompareDates(clsDate Date2)
	{
		CompareDates(*this, Date2);
	}

	static bool IsItLastMonthInYear(short Month)
	{
		return Month == 12;
	}

	bool IsItLastMonthInYear()
	{
		return IsItLastMonthInYear(_Month);
	}

	static bool IsItLastDayInMonth(clsDate Date)
	{
		return Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year);
	}

	bool IsItLastDayInMonth()
	{
		return IsItLastDayInMonth(*this);
	}

	static short TotalDaysFromTheBeginningOfTheYear(clsDate Date)
	{
		short TotalDays = 0;
		short Month = 1;

		while (true)
		{
			if (Month == Date.Month)
				break;

			TotalDays += NumberOfDaysInMonth(Month, Date.Year);

			Month++;
		}

		TotalDays += Date.Day;

		return TotalDays;
	}

	short TotalDaysFromTheBeginningOfTheYear()
	{
		TotalDaysFromTheBeginningOfTheYear(*this);
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date) ? true : false;
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short Order = DayOfWeekOrder(Date);

		return Order == 5 || Order == 6 ? true : false;
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		short Order = DayOfWeekOrder(Date);

		return Order == 0 || Order == 1 || Order == 2 || Order == 3 || Order == 4 ? true : false;
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date.Year < 1 || Date.Year > 9999)
			return false;

		if (Date.Month > 12 || Date.Month < 1)
			return false;

		if (Date.Day > NumberOfDaysInMonth(Date.Month, Date.Year) || Date.Day < 1)
			return false;

		return true;
	}

	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		return NumberOfDaysInMonth(Date.Month, Date.Year) - Date.Day + 1;
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		short Year = IsLeapYear(Date.Year) ? 366 : 365;

		return Year - TotalDaysFromTheBeginningOfTheYear(Date) + 1;
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short ActualBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;

		while (!IsDate1EqualDate2(DateFrom, DateTo))
		{
			if (!IsWeekEnd(DateFrom))
				DaysCount++;

			DateFrom = AddOneDay(DateFrom);
		}
		return DaysCount;
	}

	static short ActualVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		return ActualBusinessDays(DateFrom, DateTo);
	}

	static clsDate VacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		clsDate ReturnDate = DateFrom;

		while (VacationDays != 0)
		{
			if (IsBusinessDay(ReturnDate))
				VacationDays--;

			ReturnDate = AddOneDay(ReturnDate);
		}

		return ReturnDate;
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		short Temp;

		Temp = Date1.Day;
		Date1.Day = Date2.Day;
		Date2.Day = Temp;

		Temp = Date1.Month;
		Date1.Month = Date2.Month;
		Date2.Month = Temp;

		Temp = Date1.Year;
		Date1.Year = Date2.Year;
		Date2.Year = Temp;
	}

	static string DayShortName(clsDate Date)
	{
		short Order = DayOfWeekOrder(Date);

		return Order == 0 ? "Sun" : Order == 1 ? "Mon" : Order == 2 ? "Tue" : Order == 3 ? "Wed" :
			Order == 4 ? "Thu" : Order == 5 ? "Fri" : "Sat";
	}

	string DayShortName()
	{
		return DayShortName(*this);
	}

	static string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
		"Apr", "May", "Jun",
		"Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec"
		};
		return (Months[MonthNumber - 1]);
	}

	string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
	{
		clsDate Date;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Year);

			if (DayOrderInYear > MonthDays)
			{
				DayOrderInYear -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = DayOrderInYear;
				break;
			}

			MonthDays = NumberOfDaysInMonth(Date.Month, Year);
		}


		return Date;
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDate = false)
	{
		if (IsDate1AfterDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
		}

		short TotalDaysInDate1 = TotalDaysFromTheBeginningOfTheYear(Date1);
		short TotalDaysInDate2 = TotalDaysFromTheBeginningOfTheYear(Date2);

		while (Date2.Year > Date1.Year)
		{
			TotalDaysInDate2 += IsLeapYear(Date2.Year) ? 366 : 365;

			Date2.Year--;
		}

		short Days = TotalDaysInDate2 - TotalDaysInDate1;

		return IncludeEndDate ? ++Days : Days;
	}

	int GetDifferenceInDays(clsDate Date2)
	{
		return GetDifferenceInDays(*this, Date2);
	}

	static int CalculateMyAgeInDays(clsDate DateOfBirth)
	{
		clsDate Today = GetSystemDate();

		return GetDifferenceInDays(DateOfBirth, Today, true);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays = NumberOfDaysInMonth(Month, Year);
		int current = DayOfWeekOrder(clsDate(1, Month, Year));

		printf("\n _______________%s_______________\n\n", MonthShortName(Month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		int i;

		for (i = 0; i < current; i++)
			printf("     ");

		for (int j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			i++;

			if (i == 7)
			{
				i = 0;
				printf("\n");
			}
		}
		printf("\n _________________________________\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}

	static void PrintYearCalendar(int Year)
	{
		printf("\n _________________________________\n\n");
		printf(" Calendar - %d\n", Year);
		printf(" _________________________________\n");

		for (int i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}

		return;
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static clsDate StringToDate(string S, string Separator = "/")
	{
		clsDate Date;

		vector <string> vDate = clsString::SplitString(S, Separator);

		try
		{
			Date.Day = stoi(vDate[0]);
			Date.Month = stoi(vDate[1]);
			Date.Year = stoi(vDate[2]);
		}
		catch (...)
		{
			return clsDate{ 0, 0, 0 };
		}

		return Date;
	}

	static string DateToString(clsDate Date)
	{
		if (!IsValidDate(Date))
			return "InvalidDate!";

		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static clsDate AddOneDay(clsDate& Date)
	{

		if (IsItLastDayInMonth(Date) && IsItLastMonthInYear(Date.Month))
		{
			Date.Day = 1;
			Date.Month = 1;
			Date.Year++;
		}
		else if (IsItLastDayInMonth(Date))
		{
			Date.Day = 1;
			Date.Month++;
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void AddOneDay()
	{
		AddOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate & Date, short Days)
	{
		while (Days > 0)
		{
			Date = AddOneDay(Date);

			Days--;
		}

		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(clsDate& Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short MaxDay = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > MaxDay)
		{
			Date.Day = MaxDay;
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(clsDate& Date, short Months)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(*this, Months);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;

		short MaxDays = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > MaxDays)
		{
			Date.Day = MaxDays;
		}

		return Date;
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(clsDate& Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(clsDate& Date, short Decades)
	{
		for (short i = 1; i <= Decades; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}

	void IncreaseDateByXDecades(short Decades)
	{
		IncreaseDateByXDecades(*this, Decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = IncreaseDateByOneCentury(Date);
		}

		return Date;
	}

	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}

	static clsDate SubtractOneDay(clsDate & Date)
	{
		if (Date.Day == 1 && Date.Month == 1)
		{
			Date.Year--;
			Date.Month = 12;
			Date.Day = 31;
		}
		else if (Date.Day == 1)
		{
			Date.Month--;
			Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}

	void SubtractOneDay()
	{
		SubtractOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate & Date, short Days)
	{
		while (Days > 0)
		{
			Date = SubtractOneDay(Date);
			
			Days--;
		}

		return Date;
	}

	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate & Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = SubtractOneDay(Date);
		}

		return Date;
	}

	void DecreaseDateByOneWeek(short Day)
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate & Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate & Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
		}

		short MaxDay = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > MaxDay)
		{
			Date.Day = MaxDay;
		}

		return Date;
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate & Date, short Months)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate & Date)
	{
		Date.Year--;

		short MaxDays = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > MaxDays)
		{
			Date.Day = MaxDays;
		}

		return Date;
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate& Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate& Date, short Decades)
	{
		for (short i = 1; i <= Decades; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}

	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = DecreaseDateByOneCentury(Date);
		}

		return Date;
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

};

