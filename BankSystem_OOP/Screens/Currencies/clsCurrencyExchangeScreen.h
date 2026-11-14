#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchange {enCurrenciesList = 1, enFindCurrency = 2, enUpdateRate = 3, enCurrencyCalculator = 4, enMainMenu = 5};

	static short _ReadCurrencyExchangeMenuOption()
	{
		cout << "\t\t\t\tChoose what do you want to do ? [1 to 5] ? ";
		short Option = clsInputValidate::ReadNumberBetween(1, 5, "\t\t\t\tChoose what do you want to do? [1 to 5]? ");

		return Option;
	}

	static void _PerformCurrencyExchangeMenuOption(enCurrencyExchange Option)
	{
		switch (Option)
		{
		case enCurrencyExchange::enCurrenciesList:
		{
			_ShowCurrenciesListScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchange::enFindCurrency:
		{
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchange::enUpdateRate:
		{
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchange::enCurrencyCalculator:
		{
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenu();
			break;
		}
		case enCurrencyExchange::enMainMenu:
		{

		}
		}
	}

	static void _GoBackToCurrencyExchangeMenu()
	{
		cout << endl << endl;
		cout << "Press any key to go back to Currency Exchange Menu...";
		system("pause > nul");
		ShowCurrencyExchangeMenu();
	}

	static void _ShowCurrenciesListScreen()
	{
		//system("cls");
		//cout << "\nCurrencies List Screen will be here...\n";

		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		//system("cls");
		//cout << "\nFind Currency Screen will be here...\n";

		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		//system("cls");
		//cout << "\nUpdate Rate Screen will be here...\n";

		clsUpdateRateScreen::ShowUpdateRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		//system("cls");
		//cout << "\nCurrency Calculator Screen will be here...\n";
	
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

public:

	static void ShowCurrencyExchangeMenu()
	{
		if (!clsScreen::CheckAccessRight(clsUsers::enCurrencyExchange))
		{
			return; //This will exit the function and it will not continue.
		}

		clsScreen::_DrawScreenHeader("      " "Currency Exchange Main Screen");

		cout << "\t\t\t\t=========================================================\n";
		cout << "\t\t\t\t\t" << "       " << "Currency Exchange Main Menu" << "       " << endl;
		cout << "\t\t\t\t=========================================================\n";

		cout << "\t\t\t\t\t" << "[1] Currencies List." << endl;
		cout << "\t\t\t\t\t" << "[2] Find Currency." << endl;
		cout << "\t\t\t\t\t" << "[3] Update Rate." << endl;
		cout << "\t\t\t\t\t" << "[4] Currency Calculator." << endl;
		cout << "\t\t\t\t\t" << "[5] Main Menu." << endl;
		cout << "\t\t\t\t=========================================================\n";

		_PerformCurrencyExchangeMenuOption(enCurrencyExchange(_ReadCurrencyExchangeMenuOption()));
	}
};

