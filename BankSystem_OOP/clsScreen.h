#pragma once

#include <iostream>
#include "Global.h"
#include "clsUsers.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Header, string SubHeader = "")
	{
		system("cls");
		cout << "\t\t\t\t\t-----------------------------------------\n" << endl;
		cout << "\t\t\t\t\t" << Header + "\n";
		cout << "\t\t\t\t\t" << SubHeader << "\n";
		cout << "\t\t\t\t\t-----------------------------------------\n" << endl;

		cout << "\t\t\t\t\t" << "User: " << CurrentUser.UserName  << endl;
		cout << "\t\t\t\t\t" << "Date: " << clsDate::DateToString(clsDate()) << endl << endl;
	}

	static bool CheckAccessRight(clsUsers::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccessPermissions(Permission))
		{
			system("cls");
			cout << "\t\t\t\t\t-----------------------------------------\n" << endl;
			cout << "\t\t\t\t\t" << "   " << "Access Denied! Contact your admin.\n\n";
			cout << "\t\t\t\t\t-----------------------------------------\n" << endl;
			return false;
		}
		else
		{
			return true;
		}
	}

};

