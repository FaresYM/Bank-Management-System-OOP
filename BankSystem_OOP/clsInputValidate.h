#pragma once

#include <iostream>
#include <string>
#include <limits>

#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
public:

	template <typename T1, typename T2, typename T3>
	static bool IsNumberBetween(T1 Number, T2 From, T3 To)
	{
		return (Number >= From && Number <= To) ? true : false;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if (clsDate::CompareDates(From, To) == clsDate::enDateCompare::After)
			clsDate::SwapDates(From, To);

		return (clsDate::CompareDates(From, Date) == clsDate::enDateCompare::Before
			&& clsDate::CompareDates(Date, To) == clsDate::enDateCompare::Before) ? true : false;
	}

	template <typename T>
	static T ReadNumber(string ErrorMessage = "Invalid Number, Enter Again ")
	{
		T Num;

		while (!(cin >> Num))
		{

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << ErrorMessage;
		}
		
		return Num;
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter Again ") { return ReadNumber<short>(ErrorMessage); }
	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter Again ") { return ReadNumber<int>(ErrorMessage); }
	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter Again ") { return ReadNumber<float>(ErrorMessage); }
	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter Again ") { return ReadNumber<double>(ErrorMessage); }

	template <typename T>
	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again: ")
	{
		T Num = ReadNumber<T>();

		while (!IsNumberBetween(Num, From, To))
		{
			cout << ErrorMessage;
			Num = ReadNumber<T>();
		}
		
		return Num;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again: ")
	{
		return ReadNumberBetween<short>(From, To, ErrorMessage);
	}

	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again: ")
	{
		return ReadNumberBetween<int>(From, To, ErrorMessage);
	}

	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again: ")
	{
		return ReadNumberBetween<float>(From, To, ErrorMessage);
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again: ")
	{
		return ReadNumberBetween<double>(From, To, ErrorMessage);
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date.Year < 1 || Date.Year > 9999)
			return false;

		if (Date.Month > 12 || Date.Month < 1)
			return false;

		if (Date.Day > clsDate::NumberOfDaysInMonth(Date.Month, Date.Year) || Date.Day < 1)
			return false;

		return true;
	}

	static char ReadChar()
	{
		char Char;

		cin >> Char;

		return Char;
	}

	static char ReadChar(string Message)
	{
		char Char;

		cout << Message;
		cin >> Char;

		return Char;
	}

	static string ReadString()
	{
		string String;

		getline(cin >> ws, String);

		return String;
	}

	static string ReadString(string Message)
	{
		cout << Message;
		string String;
		getline(cin >> ws, String);

		return String;
	}

};

