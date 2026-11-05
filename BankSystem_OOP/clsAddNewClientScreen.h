#pragma once

#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsBankClients.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClients Client)
	{
		cout << "\nClient Card:";
		cout << "\n----------------------";
		cout << "\nFirstName     : " << Client.FirstName;
		cout << "\nLastName      : " << Client.LastName;
		cout << "\nFullName      : " << Client.FullName();
		cout << "\nEmail         : " << Client.Email;
		cout << "\nPhone         : " << Client.Phone;
		cout << "\nAccountNumber : " << Client.AccountNumber();
		cout << "\nPinCode       : " << Client.PinCode;
		cout << "\nAccountBalance: " << Client.AccountBalance;
		cout << "\n----------------------\n";
	}

	static void _ReadClientInfo(clsBankClients& Client)
	{
		cout << "\nEnter Client Info:\n";

		cout << "\nFirst Name: ";
		Client.FirstName = clsInputValidate::ReadString();

		cout << "\nLast Name: ";
		Client.LastName = clsInputValidate::ReadString();

		cout << "\nEmail: ";
		Client.Email = clsInputValidate::ReadString();

		cout << "\nPhone: ";
		Client.Phone = clsInputValidate::ReadString();

		cout << "\nPinCode: ";
		Client.PinCode = clsInputValidate::ReadString();

		cout << "\nAccountBalance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}

public:
	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRight(clsUsers::enPermissions::enAddNewClient))
		{
			return; //This will exit the function and it will not continue.
		}

		char Continue = 'Y';

		while (toupper(Continue) == 'Y')
		{
			clsScreen::_DrawScreenHeader("\t" "  " "Add New Client Screen");

			cout << "\nEnter Client AccountNumber: ";
			string AccountNumber = clsInputValidate::ReadString();

			while (clsBankClients::IsClientExisted(AccountNumber))
			{
				cout << "\nAccountNumber is already existed, Enter another one: ";
				AccountNumber = clsInputValidate::ReadString();
			}

			clsBankClients Client = clsBankClients::GetAddNewClientObject(AccountNumber);

			_ReadClientInfo(Client);

			clsBankClients::enSaveResults SaveResults;

			SaveResults = Client.Save();

			switch (SaveResults)
			{
			case clsBankClients::enSaveResults::svSucceeded:
			{
				cout << "\nAccount Added Successfully" << endl;
				_PrintClient(Client);
				break;
			}
			case clsBankClients::enSaveResults::svFailedEmptyObject:
			{
				cout << "\nError account was not saved because it is empty." << endl;
				break;
			}
			case clsBankClients::enSaveResults::svFailedAccountNumberExists:
			{
				cout << "\nError account was not saved because account number is used!" << endl;
				break;
			}
			}

			Continue = clsInputValidate::ReadChar("\nDo you want to add another client? (Y/N)? ");
		}
	}
};

