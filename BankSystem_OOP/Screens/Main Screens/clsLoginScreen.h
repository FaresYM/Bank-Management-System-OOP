#pragma once

#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsLoginRegister.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	
	static bool _Login()
	{
		short Attempts = 3;
		string UserName, Password;
		bool LoginFailed = false;

		do
		{

			if (LoginFailed)
			{
				cout << "\nInvalid UserName/Password!... (" << Attempts << " attempts left).\n";
			}

			UserName = clsInputValidate::ReadString("\nEnter UserName: ");
			Password = clsInputValidate::ReadString("\nEnter Password: ");

			CurrentUser = clsUsers::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();

			if (LoginFailed)
			{
				Attempts--;

				if (Attempts == 0)
				{
					system("cls");
					system("color 4F");
					cout << "\t\t\t\t\t" << "--------------------------------------------\n" << endl;
					cout << "\t\t\t\t\t" << " Attempts are over! Your account is locked.\n" << endl;
					cout << "\t\t\t\t\t" << "--------------------------------------------\n" << endl;

					system("pause > nul");

					return false;
				}
			}

		} while (LoginFailed);

		clsLoginRegister::AddNewLoginRegister();

		clsMainScreen::ShowMainMenu();
		
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		clsScreen::_DrawScreenHeader("\t" "       " "Login Screen");

		return _Login();
	}
};

