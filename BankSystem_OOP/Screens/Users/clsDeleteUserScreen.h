#pragma once

#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
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

	static void ShowDeleteUserScreen()
	{
		char Continue = 'Y';

		while (toupper(Continue) == 'Y')
		{
			clsScreen::_DrawScreenHeader("\t" "   " "Delete Client Screen");

			cout << "\nEnter UserName: ";
			string UserName = clsInputValidate::ReadString();

			while (!clsUsers::IsUserExisted(UserName))
			{
				cout << "\nUserName (" << UserName << ") is not found, Enter another one: ";
				UserName = clsInputValidate::ReadString();
			}

			clsUsers User = clsUsers::Find(UserName);

			_PrintUser(User);

			char Answer = clsInputValidate::ReadChar("\nAre you sure about deleting this user? (Y/N)? ");

			if (toupper(Answer) == 'Y')
			{
				if (User.Delete())
				{
					cout << "\nUser deleted successfully" << endl;
				}
				else
				{
					cout << "\nUser was not deleted." << endl;
				}
			}
			else
			{
				return;
			}

			Continue = clsInputValidate::ReadChar("\nDo you want to delete another user? (Y/N)? ");
		}
	}
};

