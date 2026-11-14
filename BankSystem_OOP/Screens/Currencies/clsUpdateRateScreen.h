#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateRateScreen : protected clsScreen
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

	static float _ReadRate()
	{
		cout << "\nEnter New Rate: ";
		float NewRate = clsInputValidate::ReadFloatNumber();
		
		return NewRate;
	}

public:

	static void ShowUpdateRateScreen()
	{
		clsScreen::_DrawScreenHeader("\t" "   " "Update Rate Screen");

		string CurrencyCode = clsInputValidate::ReadString("\nEnter Currency Code: ");

		while (!clsCurrency::IsCurrencyExisted(CurrencyCode))
		{
			cout << "\nCurrency is not found, Enter another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyCard(Currency);

		char Answer = clsInputValidate::ReadChar("\nAre you sure you want to update the rate of this currency? (Y/N)? ");

		if (toupper(Answer) == 'Y')
		{
			cout << "\nUpdate Currency Rate:\n";
			cout << "____________________" << endl << endl;

			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency rate updated successfully :)\n";

			_PrintCurrencyCard(Currency);
		}
	}
};

