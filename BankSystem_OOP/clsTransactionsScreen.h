#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithDrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

	enum enTransactionsMenu {enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, 
							 enTransfer = 4, enTransferLog = 5, enMainMenu = 6};

	static short _ReadTransactionsMenuOption()
	{
		short Option;

		cout << "\t\t\t\tChoose what do you want to do? [1 to 6]? ";
		Option = clsInputValidate::ReadNumberBetween(1, 6, "\t\t\t\tChoose what do you want to do? [1 to 6]? ");

		return Option;
	}

	static void _PerformTransactionsMenuOption(enTransactionsMenu Option)
	{
		switch (Option)
		{
		case enTransactionsMenu::enDeposit:
		{
			_ShowDepositScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactionsMenu::enWithdraw:
		{
			_ShowWithdrawScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactionsMenu::enTotalBalances:
		{
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactionsMenu::enTransfer:
		{
			_ShowTransferScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactionsMenu::enTransferLog:
		{
			_ShowTransferLogListScreen();
			_GoBackToTransactionsMenu();
			break;
		}
		case enTransactionsMenu::enMainMenu:
		{
			// --- (Circular Include Error Fix) ---
			// المشكلة: تعارض دائري بين كلاس العمليات وكلاس القائمة الرئيسية عند عمل تضمين لكل كلاس عند الآخر.
			// الحل الاحترافي: حذفنا استدعاء القائمة الرئيسية من هذا الملف نهائياً.
			// نكتفي بطرق المكان هنا فارغ وبمجرد انتهاء الفانكشن
			// يتم فتح القائمة الرئيسية فوراً من الكلاس clsMainScreen
		}
		}
	}

	static void _GoBackToTransactionsMenu()
	{
		cout << endl << endl;
		cout << "Press any key to go back to Transactions Menu...";
		system("pause > nul");
		ShowTransactionsMenu();
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
		
	}

	static void _ShowWithdrawScreen()
	{
		clsWithDrawScreen::ShowWithDrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static  void _ShowTransferLogListScreen()
	{
		clsTransferLog::ShowTransferLogListScreen();
	}

public:

	static void ShowTransactionsMenu()
	{
		if (!CheckAccessRight(clsUsers::enPermissions::enTransactions))
		{
			return; //This will exit the function and it will not continue.
		}

		clsScreen::_DrawScreenHeader("\t" "   " "Transactions Screen");

		cout << "\t\t\t\t=========================================================\n";
		cout << "\t\t\t\t\t\t" << "    " << "Transactions Menu" << "               " << endl;
		cout << "\t\t\t\t=========================================================\n";

		cout << "\t\t\t\t\t" << "[1] Deposit." << endl;
		cout << "\t\t\t\t\t" << "[2] Withdraw." << endl;
		cout << "\t\t\t\t\t" << "[3] TotalBalances." << endl;
		cout << "\t\t\t\t\t" << "[4] Transfer." << endl;
		cout << "\t\t\t\t\t" << "[5] Transfer Log." << endl;
		cout << "\t\t\t\t\t" << "[6] MainMenu." << endl;
		cout << "\t\t\t\t=========================================================\n";

		_PerformTransactionsMenuOption((enTransactionsMenu)_ReadTransactionsMenuOption());
	}
};

