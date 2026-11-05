#pragma once

#include "clsDate.h"

class clsPeriod
{
private:
	clsDate StartDate;
	clsDate EndDate;

public:

	clsPeriod(clsDate StartDate, clsDate EndDate)
	{
		this->StartDate = StartDate;
		this->EndDate = EndDate;
	}

	void SetStartDate(clsDate StartDate)
	{
		this->StartDate = StartDate;
	}

	clsDate GetStartDate()
	{
		return StartDate;
	}

	void SetEndDate(clsDate EndDate)
	{
		this->EndDate = EndDate;
	}

	clsDate GetEndDate()
	{
		return EndDate;
	}

	static bool ArePeriodsOverlap(clsPeriod Period1, clsPeriod Period2)
	{
		//In this code if one of those inner two functions returned true the outer function will return false
		//means they are not overlap otherwith they overlap, 
		//because we check if period2 end date before period1 start date or period1 end date before period2 start date
		//to say periods doesnot overlap, rather than check 6 conditions to say periods is overlap.

		//Compare dates function will return -1 if date1 before date2 and 0 if equal and 1 if date1 after date2,
		//and "before" item in compare dates enum is equal -1 and so on.

		return clsDate::CompareDates(Period2.EndDate, Period1.StartDate) == clsDate::enDateCompare::Before ||
			clsDate::CompareDates(Period1.EndDate, Period2.StartDate) == clsDate::enDateCompare::Before ? false : true;
	}

	bool ArePeriodsOverlap(clsPeriod Period2)
	{
		return ArePeriodsOverlap(*this, Period2);
	}

	void Print()
	{
		cout << "Period Start: ";
		StartDate.Print();

		cout << "Period End: ";
		EndDate.Print();
	}

};

