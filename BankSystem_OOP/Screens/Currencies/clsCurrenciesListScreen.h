#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:
	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
		cout << "\t";
		cout << "| " << setw(35) << left << Currency.Country();
		cout << "| " << setw(15) << left << Currency.CurrencyCode();
		cout << "| " << setw(40) << left << Currency.CurrencyName();
		cout << "| " << setw(10) << left << Currency.Rate();
	}
public:

	static void ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string Header = "\t" " " "Currencies List Screen";
		string SubHeader = "\t" "     " "(" + to_string(vCurrencies.size()) + ")" + "Currency.\n";

		clsScreen::_DrawScreenHeader(Header, SubHeader);

		cout << "\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t";
		cout << "| " << left << setw(35) << "Country";
		cout << "| " << left << setw(15) << "Code";
		cout << "| " << left << setw(40) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << "\n\t_____________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		if (vCurrencies.size() == 0)
			cout << "\t\t\t\t\t" "   " "No currencies available in the system!\n";
		else
			for (clsCurrency &Currency : vCurrencies)
			{

				_PrintCurrencyRecordLine(Currency);
				cout << endl;
			}

		cout << "\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

	}
};

