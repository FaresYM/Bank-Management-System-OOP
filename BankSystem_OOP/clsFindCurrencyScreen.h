#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "____________________________________" << endl;
		cout << "Country    : " << Currency.Country() << endl;
		cout << "Code       : " << Currency.CurrencyCode() << endl;
		cout << "Name       : " << Currency.CurrencyName() << endl;
		cout << "Rate(1$) = : " << Currency.Rate() << endl;
		cout << "____________________________________" << endl;
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency is found :)\n";
			_PrintCurrencyCard(Currency);
		}
		else
		{
			cout << "\nCurrency is not found :)\n";
			_PrintCurrencyCard(Currency);
		}
	}
public:

	static void ShowFindCurrencyScreen()
	{
		clsScreen::_DrawScreenHeader("\t" "  " "Find Currency Screen");

		cout << "\nFind By: [1] Code or [2] Country ? ";
		short Choice = clsInputValidate::ReadNumberBetween(1, 2, "\nFind By: [1] Code or [2] Country ? ");

		switch (Choice)
		{
		case 1:
		{
			string CurrencyCode = clsInputValidate::ReadString("\nPlease enter CurrencyCode: ");
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
			break;
		}
		case 2:
		{
			string Country = clsInputValidate::ReadString("\nPlease enter Country Name: ");
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResults(Currency);
			break;
		}
		}
		
	}
};

