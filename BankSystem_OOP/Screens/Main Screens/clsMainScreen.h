#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClients.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegister.h"
#include "clsCurrencyExchangeScreen.h"
#include "Global.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum enMainMenuOptions {
		enShowClientsList = 1, enAddNewClient = 2, enDeleteClient = 3, enUpdateClientInfo = 4,
		enFindClient = 5, enTransactions = 6, enManageUsers = 7, enLoginRegister = 8, enCurrencyExchange = 9, enExit = 10
	};

	static short _ReadMainMenuOption()
	{
		short Option;

		cout << "\t\t\t\t Choose what do you want to do? [1 to 10]? ";
		Option = clsInputValidate::ReadNumberBetween(1, 10, "\t\t\t\t Choose what do you want to do? [1 to 10]? ");

		return Option;
	}

	static void _PerformMainMenuOption(enMainMenuOptions Options)
	{
		switch (Options)
		{
		case enMainMenuOptions::enShowClientsList:
		{
			_ShowClientsListScreen();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enAddNewClient:
		{
			_ShowAddNewClientScreen();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enDeleteClient:
		{
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enUpdateClientInfo:
		{
			_ShowUpdateClientInfoScreen();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enFindClient:
		{
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enTransactions:
		{
			_ShowTransactionsMenu();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enManageUsers:
		{
			_ShowManageUsersMenu();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enLoginRegister:
		{
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enCurrencyExchange:
		{
			_ShowCurrencyExchangeScreen();
			_GoBackToMainMenu();
			break;
		}
		case enMainMenuOptions::enExit:
		{
			system("cls");
			_Logout();
			break;
		}
		}
	}

	static void _GoBackToMainMenu()
	{
		cout << endl << endl;
		cout << "Press any key to go back to Main Menu...";
		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowClientsListScreen()
	{
		clsClientListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientInfoScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientInfoScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenu()
	{
		clsTransactionsScreen::ShowTransactionsMenu();
	}

	static void _ShowManageUsersMenu()
	{
		clsManageUsersScreen::ShowManageUsersMenu();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegister::ShowLoginRegisterListScreen();
	}

	static void _ShowCurrencyExchangeScreen()
	{
		clsCurrencyExchangeScreen::ShowCurrencyExchangeMenu();
	}

	static void _Logout()
	{
		CurrentUser = clsUsers::Find("", "");
	}

public:


	static void ShowMainMenu()
	{
		clsScreen::_DrawScreenHeader("\t\tMain Screen");

		cout << "\t\t\t\t=========================================================\n";
		cout << "\t\t\t\t\t\t" << "         " << "Main Menu" << "               " << endl;
		cout << "\t\t\t\t=========================================================\n";

		cout << "\t\t\t\t\t" << "[1] Show Clients List." << endl;
		cout << "\t\t\t\t\t" << "[2] Add New Client." << endl;
		cout << "\t\t\t\t\t" << "[3] Delete Client." << endl;
		cout << "\t\t\t\t\t" << "[4] Update Client Info." << endl;
		cout << "\t\t\t\t\t" << "[5] Find Client." << endl;
		cout << "\t\t\t\t\t" << "[6] Transactions." << endl;
		cout << "\t\t\t\t\t" << "[7] Manage Users." << endl;
		cout << "\t\t\t\t\t" << "[8] Login Register." << endl;
		cout << "\t\t\t\t\t" << "[9] CurrencyExchange." << endl;
		cout << "\t\t\t\t\t" << "[10] Logout." << endl;
		cout << "\t\t\t\t=========================================================\n";
		_PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}
};

