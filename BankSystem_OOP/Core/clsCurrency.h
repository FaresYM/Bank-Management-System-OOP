#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include "fstream"

using namespace std;

class clsCurrency
{
private:

	static inline const string _FileName = "Databases/Currencies.txt";

	enum enMode {EmptyMode = 0, UpdateMode = 1};

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
	{
		vector <string> Currency = clsString::SplitString(Line, Separator);
		
		return clsCurrency(enMode::UpdateMode, Currency[0], Currency[1], Currency[2], stof(Currency[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
	{
		string Line;

		Line += Currency.Country() + Separator;
		Line += Currency.CurrencyCode() + Separator;
		Line += Currency.CurrencyName() + Separator;
		Line += to_string(Currency.Rate());

		return Line;
	}

	static vector <clsCurrency> _LoadCurrencyDateFromFile()
	{
		fstream MyFile;
		vector <clsCurrency> vCurrencies;

		MyFile.open(_FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return vCurrencies;
	}

	static void _SaveCurrencyDateToFile(vector <clsCurrency> vCurrencies)
	{
		fstream MyFile;

		MyFile.open(_FileName, ios::out);

		if (MyFile.is_open())
		{
			for (clsCurrency &Currency : vCurrencies)
			{
				string Line = _ConvertCurrencyObjectToLine(Currency);

				MyFile << Line << endl;
			}

			MyFile.close();
		}
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencies = _LoadCurrencyDateFromFile();

		string TargetCurrency = clsString::UpperAllString(CurrencyCode());

		for (clsCurrency &Currency : vCurrencies)
		{
			if (Currency.CurrencyCode() == TargetCurrency)
			{
				Currency = *this;
				break;
			}
		}
		
		_SaveCurrencyDateToFile(vCurrencies);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static bool IsCurrencyExisted(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	float Rate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCountry(string Country)
	{
		fstream MyFile;
		string TargetCountry = clsString::UpperAllString(Country);

		MyFile.open(_FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.Country()) == TargetCountry)
				{
					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();

		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		fstream MyFile;
		string TargetCurrencyCode = clsString::UpperAllString(CurrencyCode);

		MyFile.open(_FileName, ios::in);
	
		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.CurrencyCode()) == TargetCurrencyCode)
				{
					MyFile.close();

					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDateFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return float(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return float(AmountInUSD * Currency2.Rate());
	}
};

