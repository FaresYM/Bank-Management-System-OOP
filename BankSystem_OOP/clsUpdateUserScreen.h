#pragma once

#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private:

	static void ReadPermissions(int& Permissions)
	{
		char Answer;

		Answer = clsInputValidate::ReadChar("\nShow Clients List? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			Permissions += clsUsers::enPermissions::enClientsList;

		Answer = clsInputValidate::ReadChar("\nAdd New Client? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			Permissions += clsUsers::enPermissions::enAddNewClient;

		Answer = clsInputValidate::ReadChar("\nDelete Client? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			Permissions += clsUsers::enPermissions::enDeleteClient;

		Answer = clsInputValidate::ReadChar("\nUpdate Client? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			Permissions += clsUsers::enPermissions::enUpdateClient;

		Answer = clsInputValidate::ReadChar("\nFind Client? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			Permissions += clsUsers::enPermissions::enFindClient;

		Answer = clsInputValidate::ReadChar("\nShow Transactions? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			Permissions += clsUsers::enPermissions::enTransactions;

		Answer = clsInputValidate::ReadChar("\nShow Manage Users? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			Permissions += clsUsers::enPermissions::enManageUsers;

		Answer = clsInputValidate::ReadChar("\nShow Login Register? (Y/N)? ");

		if (toupper(Answer) == 'Y')
			Permissions += clsUsers::enPermissions::enLoginRegister;
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

	static void ShowUpdateUserScreen()
	{
		char Continue = 'Y';

		while (toupper(Continue) == 'Y')
		{
			clsScreen::_DrawScreenHeader("\t" "   " "Update User Screen");

			cout << "Enter UserName: ";
			string UserName = clsInputValidate::ReadString();

			while (!clsUsers::IsUserExisted(UserName))
			{
				cout << "\nUser (" << UserName << ") is not found, Enter another one: ";
				UserName = clsInputValidate::ReadString();
			}

			clsUsers User = clsUsers::Find(UserName);
			_PrintUser(User);

			char Answer = clsInputValidate::ReadChar("\nAre you sure you want to update this user? (Y/N)? ");

			if (toupper(Answer) == 'Y')
			{
				_ReadUserInfo(User);
			}
			else
			{
				cout << "\nUser wasn't updated!" << endl;
				return;
			}

			clsUsers::enSaveResults SaveResults;

			SaveResults = User.Save();

			switch (SaveResults)
			{
			case clsUsers::enSaveResults::svSucceeded:
			{
				_PrintUser(User);
				cout << "\nUser updated successfully!\n";
				break;
			}
			case clsUsers::enSaveResults::svFailedEmptyObject:
			{
				cout << "\nError Account was not saved because it is empty.\n";
				break;
			}
			}

			Continue = clsInputValidate::ReadChar("\nDo you want to update another user? (Y/N)? ");
		}
	}
};

