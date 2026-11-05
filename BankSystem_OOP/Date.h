#pragma once
#pragma warning (disable : 4996)

#include <iostream>
#include "String.h"
#include <iomanip>

using namespace std;

namespace Date
{
	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	struct stDate
	{
		short Day;
		short Month;
		short Year;
	};

	struct stPeriod
	{
		stDate StartDate;
		stDate EndDate;
	};
	
	stDate IncreaseDateByOneDay(stDate Date);
	
	short Read_Date(string Message)
	{
		short Date = 0;

		cout << Message;
		cin >> Date;

		cout << endl;

		return Date;
	}

	stDate ReadFullDate()
	{
		stDate Date;

		Date.Day = Read_Date("Please enter a day? ");
		Date.Month = Read_Date("Please enter a month? ");
		Date.Year = Read_Date("Please enter a year? ");
		cout << endl;

		return Date;
	}

	stPeriod ReadPeriod()
	{
		stPeriod Period;

		cout << "\nEnter start date: \n";
		Period.StartDate = ReadFullDate();

		cout << "\nEnter end date: \n";
		Period.EndDate = ReadFullDate();

		return Period;
	}

	bool IsLeapYear(short Year)
	{
		return (Year % 400 == 0) ? true : (Year % 4 == 0) and (Year % 100 != 0) ? true : false;
	}

	short NumberOfDaysInMonth(short Month, short Year)
	{
		return Month < 1 || Month > 12 ? 0 : Month == 2 ? IsLeapYear(Year) ? 29 : 28 :
			Month == 4 or Month == 6 or Month == 9 or Month == 11 ? 30 : 31;
	}

	short DayOfWeekOrder(stDate Date)
	{
		short a, y, m;

		a = (14 - Date.Month) / 12;
		y = Date.Year - a;
		m = Date.Month + (12 * a) - 2;

		return (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;

		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;

		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
	{
		//The Inner ternary operator beside it is its true and its false is the outer false
		//The Middle ternary operator beside it is its true and its false is the middle false
		//The Outer ternary operator besite it is its true and its false is the inner false
		return (Date1.Year < Date2.Year) ? true : (Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month) ? true :
			(Date1.Month == Date2.Month) ? (Date1.Day < Date2.Day) ? true : false : false : false;
	}

	bool IsDate1EqualDate2(stDate Date1, stDate Date2)
	{
		return Date1.Day == Date2.Day && Date1.Month == Date2.Month && Date1.Year == Date2.Year ? true : false;
	}

	bool IsDate1AfterDate2(stDate Date1, stDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
	}

	enDateCompare CompareDates(stDate Date1, stDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;
		else if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;
		
		return enDateCompare::After;
	}

	bool IsItLastMonthInYear(short Month)
	{
		return Month == 12;
	}

	bool IsItLastDayInMonth(stDate Date)
	{
		return Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year);
	}

	short TotalDaysFromTheBeginningOfTheYear_Method1(stDate Date)
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

	short TotalDaysFromTheBeginningOfTheYear_Method2(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (int i = 1; i < Month; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	bool IsEndOfWeek(stDate Date)
	{
		return Date::DayOfWeekOrder(Date) ? true : false;
	}

	bool IsWeekEnd(stDate Date)
	{
		short Order = Date::DayOfWeekOrder(Date);

		return Order == 5 || Order == 6 ? true : false;
	}

	bool IsBusinessDay(stDate Date)
	{
		short Order = DayOfWeekOrder(Date);

		return Order == 0 || Order == 1 || Order == 2 || Order == 3 || Order == 4 ? true : false;
	}

	bool ArePeriodsOverlap(stPeriod Period1, stPeriod Period2)
	{
		/*In this code if one of those inner two functions returned true the outer function will return false
		means they are not overlap otherwith they overlap,
		because we check if period2 end date before period1 start date or period1 end date before period2 start date
		to say periods doesnot overlap, rather than check 6 conditions to say periods is overlap.*/
		
		/*Compare dates function will return -1 if date1 before date2 and 0 if equal and 1 if date1 after date2,
		and "before" item in compare dates enum is equal -1 and so on.*/

		return CompareDates(Period2.EndDate, Period1.StartDate) == enDateCompare::Before ||
			CompareDates(Period1.EndDate, Period2.StartDate) == enDateCompare::Before? false : true;
	}

	bool IsDateWithinPeriod(stDate Date, stPeriod Period)
	{
		return !(CompareDates(Date, Period.StartDate) == enDateCompare::Before ||
			CompareDates(Date, Period.EndDate) == enDateCompare::After);
	}
	
	bool IsValidDate(stDate Date)
	{
		if (Date.Year < 1 || Date.Year > 9999)
			return false;

		if (Date.Month > 12 || Date.Month < 1)
			return false;

		if (Date.Day > NumberOfDaysInMonth(Date.Month, Date.Year) || Date.Day < 1)
			return false;

		return true;
	}

	short DaysUntilTheEndOfWeek(stDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilTheEndOfYear(stDate Date)
	{
		short Year = IsLeapYear(Date.Year) ? 366 : 365;

		return Year - TotalDaysFromTheBeginningOfTheYear_Method1(Date);
	}
	
	short ActualVacationDays(stDate DateFrom, stDate DateTo)
	{
		short DaysCount = 0;
		
		while (!IsDate1EqualDate2(DateFrom, DateTo))
		{
			if (!IsWeekEnd(DateFrom))
				DaysCount++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return DaysCount;
	}
	
	stDate VacationReturnDate(stDate DateFrom, short VacationDays)
	{
		stDate ReturnDate = DateFrom;

		while (VacationDays != 0)
		{
			if (IsBusinessDay(ReturnDate))
				VacationDays--;

			ReturnDate = IncreaseDateByOneDay(ReturnDate);
		}

		return ReturnDate;
	}

	void SwapDate(stDate& Date1, stDate& Date2)
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
	
	string DayShortName(stDate Date)
	{
		short Order = DayOfWeekOrder(Date);

		return Order == 0 ? "Sun" : Order == 1 ? "Mon" : Order == 2 ? "Tue" : Order == 3 ? "Wed" :
			Order == 4 ? "Thu" : Order == 5 ? "Fri" : "Sat";
	}

	string MonthShortName(short MonthNumber)
	{
		string Months[12] = { "Jan", "Feb", "Mar",
		"Apr", "May", "Jun",
		"Jul", "Aug", "Sep",
		"Oct", "Nov", "Dec"
		};
		return (Months[MonthNumber - 1]);
	}
	
	stDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
	{
		stDate Date;
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

	int GetDifferenceDays(stDate Date1, stDate Date2, bool IncludeEndDate = false)
	{
		if (IsDate1AfterDate2(Date1, Date2))
		{
			SwapDate(Date1, Date2);
		}

		short TotalDaysInDate1 = TotalDaysFromTheBeginningOfTheYear_Method1(Date1);
		short TotalDaysInDate2 = TotalDaysFromTheBeginningOfTheYear_Method1(Date2);

		while (Date2.Year > Date1.Year)
		{
			TotalDaysInDate2 += IsLeapYear(Date2.Year) ? 366 : 365;

			Date2.Year--;
		}

		short Days = TotalDaysInDate2 - TotalDaysInDate1;

		return IncludeEndDate ? ++Days : Days;
	}

	int PeriodLength(stPeriod Period, bool IncludeEndDate = false)
	{
		return GetDifferenceDays(Period.StartDate, Period.EndDate, IncludeEndDate);
	}

	int CountOverlapDays(stPeriod Period1, stPeriod Period2)
	{
		int Period1Length = PeriodLength(Period1, true);
		int Period2Length = PeriodLength(Period2, true);
		int OverlapDays = 0;

		if (!ArePeriodsOverlap(Period1, Period2))
			return 0;

		if (Period1Length < Period2Length)
		{
			while (IsDate1BeforeDate2(Period1.StartDate, Period1.EndDate))
			{
				if (IsDateWithinPeriod(Period1.StartDate, Period2))
					OverlapDays++;

				Period1.StartDate = IncreaseDateByOneDay(Period1.StartDate);
			}
		}
		else
		{
			while (IsDate1BeforeDate2(Period2.StartDate,
				Period2.EndDate))
			{
				if (IsDateWithinPeriod(Period2.StartDate, Period1))
					OverlapDays++;

				Period2.StartDate = IncreaseDateByOneDay(Period2.StartDate);
			}
		}
		return OverlapDays;
	}

	void PrintMonthCalendar(short Month, short Year)
	{
		int NumberOfDays = NumberOfDaysInMonth(Month, Year);
		int current = DayOfWeekOrder(1, Month, Year);

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

	void PrintYearCalendar(int Year)
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

	stDate StringToDate(string DateString, string Separator)
	{
		Date::stDate Date;

		vector <string> vString = MyStringLib::SplitString(DateString, Separator);

		try
		{
			Date.Day = stoi(vString[0]);
			Date.Month = stoi(vString[1]);
			Date.Year = stoi(vString[2]);
		}
		catch (...)
		{
			return stDate{ 0, 0, 0 };
		}

		return Date;
	}

	string DateToString(stDate Date)
	{
		if (!IsValidDate(Date))
			return "InvalidDate!";

		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string FormatDate(stDate Date, string FormatDate = "dd/mm/yyyy")
	{
		string Formated_Date = "";

		Formated_Date = MyStringLib::ReplaceWord(FormatDate, "dd", to_string(Date.Day));
		Formated_Date = MyStringLib::ReplaceWord(Formated_Date, "mm", to_string(Date.Month));
		Formated_Date = MyStringLib::ReplaceWord(Formated_Date, "yyyy", to_string(Date.Year));

		return Formated_Date;
	}

	stDate GetSystemDate()
	{
		stDate Date;

		time_t t = time(0);
		tm* now = localtime(&t);

		Date.Day = now->tm_mday;
		Date.Month = now->tm_mon + 1;
		Date.Year = now->tm_year + 1900;

		return Date;
	}

	stDate IncreaseDateByOneDay(stDate Date)
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

	stDate IncreaseDateByXDays(stDate Date, short Day)
	{
		while (Day > 0)
		{
			Date = IncreaseDateByOneDay(Date);

			Day--;
		}

		return Date;
	}

	stDate IncreaseDateByOneWeek(stDate Date)
	{
		for(short i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	stDate IncreaseDateByXWeeks(stDate Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	stDate IncreaseDateByOneMonth(stDate Date)
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

	stDate IncreaseDateByXMonth(stDate Date, short Month)
	{
		for (short i = 1; i <= Month ; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	stDate IncreaseDateByOneYear(stDate Date)
	{
		Date.Year++;

		short MaxDays = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > MaxDays)
		{
			Date.Day = MaxDays;
		}

		return Date;
	}

	stDate IncreaseDateByXYears(stDate Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	stDate IncreaseDateByOneDecade(stDate Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	stDate IncreaseDateByXDecades(stDate Date, short Decades)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}

	stDate IncreaseDateByOneCentury(stDate Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}
	
	stDate IncreaseDateByOneMillennium(stDate Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = IncreaseDateByOneCentury(Date);
		}

		return Date;
	}
	 
	stDate DecreaseDateByOneDay(stDate Date)
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
	   
	stDate DecreaseDateByXDays(stDate Date, short Day)
	{
		while (Day > 0)
		{
			Date = DecreaseDateByOneDay(Date);

			Day--;
		}

		return Date;
	}
		   
	stDate DecreaseDateByOneWeek(stDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	stDate DecreaseDateByXWeeks(stDate Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}
		   
	stDate DecreaseDateByOneMonth(stDate Date)
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
		   
	stDate DecreaseDateByXMonth(stDate Date, short Month)
	{
		for (short i = 1; i <= Month; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}
		   
	stDate DecreaseDateByOneYear(stDate Date)
	{
		Date.Year--;

		short MaxDays = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > MaxDays)
		{
			Date.Day = MaxDays;
		}

		return Date;
	}
		   
	stDate DecreaseDateByXYears(stDate Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}
		   
	stDate DecreaseDateByOneDecade(stDate Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}
		   
	stDate DecreaseDateByXDecades(stDate Date, short Decades)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}

	stDate DecreaseDateByOneCentury(stDate Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}
		   
	stDate DecreaseDateByOneMillennium(stDate Date)
	{
		for (short i = 1; i <= 10; i++)
		{
			Date = DecreaseDateByOneCentury(Date);
		}

		return Date;
	}

}
