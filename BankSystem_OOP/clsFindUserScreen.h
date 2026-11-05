#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUsers User)
	{
		cout << "\nUser Card:";
		cout << "\n----------------------";
		cout << "\nFirstName     : " << User.FirstName;
		cout << "\nLastName      : " << User.LastName;
		cout << "\nFullName      : " << User.FullName();
		cout << "\nEmail         : " << User.Email;
		cout << "\nPhone         : " << User.Phone;
		cout << "\nUserName      : " << User.UserName;
		cout << "\nPassword      : " << User.Password;
		cout << "\nPermissions   : " << User.Permissions;
		cout << "\n----------------------\n";
	}
public:

	static void ShowFindUserScreen()
	{
		clsScreen::_DrawScreenHeader("\t" "    " "Find User Screen");

		cout << "Enter UserName: ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUsers::IsUserExisted(UserName))
		{
			cout << "\nUser (" << UserName << ") is not found, Enter another one: ";
			UserName = clsInputValidate::ReadString();
		}

		cout << endl << "User has found! :)" << endl;

		clsUsers User = clsUsers::Find(UserName);

		_PrintUser(User);
	}
};

