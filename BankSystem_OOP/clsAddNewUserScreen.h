#pragma once

#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
	static bool _AskYesNo(string Message)
	{
		char Answer = clsInputValidate::ReadChar(Message);
		return (toupper(Answer) == 'Y');
	}

	static void ReadPermissions(int& Permissions)
	{
		if (_AskYesNo("\nShow Clients List? (Y/N)? "))
		{
			Permissions += clsUsers::enPermissions::enClientsList;
		}

		if (_AskYesNo("\nAdd New Client? (Y/N)? "))
		{
			Permissions += clsUsers::enPermissions::enAddNewClient;
		}

		if (_AskYesNo("\nDelete Client? (Y/N)? "))
		{
			Permissions += clsUsers::enPermissions::enDeleteClient;
		}
       
		if (_AskYesNo("\nUpdate Client? (Y/N)? "))
		{
			Permissions += clsUsers::enPermissions::enUpdateClient;
		}
       
		if (_AskYesNo("\nFind Client? (Y/N)? "))
		{
			Permissions += clsUsers::enPermissions::enFindClient;
		}

		if (_AskYesNo("\nShow Transactions? (Y/N)? "))
		{
			Permissions += clsUsers::enPermissions::enTransactions;
		}

		if (_AskYesNo("\nShow Manage Users? (Y/N)? "))
		{
			Permissions += clsUsers::enPermissions::enManageUsers;
		}

		if (_AskYesNo("\nShow Login Register? (Y/N)? "))
		{
			Permissions += clsUsers::enPermissions::enLoginRegister;
		}
	}

	static int GetPermissions()
	{
		int Permissions = 0;
		char Answer = clsInputValidate::ReadChar("\nDo you want to give full access? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			return clsUsers::enPermissions::enAll;
		else
		{
			cout << "\nDo you want to give access to: " << endl;

			ReadPermissions(Permissions);
		}

		return Permissions;
	}

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

	static void _ReadUserInfo(clsUsers& User)
	{
		cout << "\nEnter User Info:\n";

		cout << "\nFirst Name: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nLast Name: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEmail: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nPhone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nPassword: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nPermissions: ";
		User.Permissions = GetPermissions();
	}

public:

	static void ShowAddNewUserScreen()
	{
		char Continue = 'Y';

		while (toupper(Continue) == 'Y')
		{
			clsScreen::_DrawScreenHeader("\t" "   " "Add New User Screen");

			string UserName = clsInputValidate::ReadString("Enter UserName: ");

			while (clsUsers::IsUserExisted(UserName))
			{

				cout << "\nUserName (" << UserName << ") is existed, Enter another one: ";
				UserName = clsInputValidate::ReadString();
			}

			char Answer = clsInputValidate::ReadChar("\nAre you sure about adding this user? (Y/N)? ");

			if (toupper(Answer) == 'Y')
			{
				clsUsers User = clsUsers::GetAddNewUserObject(UserName);
				_ReadUserInfo(User);

				clsUsers::enSaveResults SaveResults;

				SaveResults = User.Save();

				switch (SaveResults)
				{
				case clsUsers::enSaveResults::svSucceeded:
				{
					cout << "\nAccount added successfully" << endl;
					_PrintUser(User);
					break;
				}
				case clsUsers::enSaveResults::svFailedEmptyObject:
				{
					cout << "\nError account was not saved because it is empty." << endl;
					break;
				}
				case clsUsers::enSaveResults::svFailedAccountNumberExists:
				{
					cout << "\nError account was not saved because account number is used." << endl;
					break;
				}
				}
			}

			Continue = clsInputValidate::ReadChar("\nDo you want to add another user? (Y/N)? ");
		}
	}

};

