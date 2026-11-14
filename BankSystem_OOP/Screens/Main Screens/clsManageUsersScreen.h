#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:

	enum enManageUsersOption {enShowUsersList = 1, enAddNewUser = 2, enDeleteUser = 3, enUpdateUser = 4, enFindUser = 5, enMainMenu = 6};

	static short _ReadManageUsersOption()
	{
		cout << "\t\t\t\tChoose what do you want to do? [1 to 6]? ";

		short Option = clsInputValidate::ReadNumberBetween(1, 6, "\t\t\t\tChoose what do you want to do? [1 to 6]? ");

		return Option;
	}

	static void _PerformManageUsersMenuOption(enManageUsersOption Option)
	{
		switch (Option)
		{
		case enManageUsersOption::enShowUsersList:
		{
			_ShowUsersListScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersOption::enAddNewUser:
		{
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;

		}
		case enManageUsersOption::enDeleteUser:
		{
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersOption::enUpdateUser:
		{
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersOption::enFindUser:
		{
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersOption::enMainMenu:
		{
			// --- (Circular Include Error Fix) ---
			// المشكلة: تعارض دائري بين كلاس إدارة المستخدمين وكلاس القائمة الرئيسية عند عمل تضمين لكل كلاس عند الآخر.
			// الحل الاحترافي: حذفنا استدعاء القائمة الرئيسية من هذا الملف نهائياً.
			// نكتفي بطرق المكان هنا فارغ وبمجرد انتهاء الفانكشن
			// يتم فتح القائمة الرئيسية فوراً من الكلاس clsMainScreen
		}
		}
	}

	static void _GoBackToManageUsersMenu()
	{
		cout << endl << endl;
		cout << "Press any key to go back to Manage Users Menu...";
		system("pause > nul");
		ShowManageUsersMenu();
	}

	static void _ShowUsersListScreen()
	{
		clsUsersListScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

public:

	static void ShowManageUsersMenu()
	{
		if (!CheckAccessRight(clsUsers::enPermissions::enManageUsers))
		{
			return; //This will exit the function and it will not continue.
		}

		clsScreen::_DrawScreenHeader("\t" "   " "Manage Users Screen");

		cout << "\t\t\t\t=========================================================\n";
		cout << "\t\t\t\t\t\t" << "    " << "Manage Users Menu" << "    " << endl;
		cout << "\t\t\t\t=========================================================\n";

		cout << "\t\t\t\t\t" << "[1] Show Users List." << endl;
		cout << "\t\t\t\t\t" << "[2] Add New User." << endl;
		cout << "\t\t\t\t\t" << "[3] Delete User." << endl;
		cout << "\t\t\t\t\t" << "[4] Update User." << endl;
		cout << "\t\t\t\t\t" << "[5] Find User." << endl;
		cout << "\t\t\t\t\t" << "[6] Main Menu." << endl;
		cout << "\t\t\t\t=========================================================\n";

		_PerformManageUsersMenuOption((enManageUsersOption)_ReadManageUsersOption());
	}
};

