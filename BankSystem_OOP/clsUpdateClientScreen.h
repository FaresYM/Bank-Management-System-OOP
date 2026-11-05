#pragma once

#include <iostream>
#include <string>
#include "clsBankClients.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

	static void ShowUpdateClientInfoScreen()
	{
		if (!CheckAccessRight(clsUsers::enPermissions::enUpdateClient))
		{
			return; //This will exit the function and it will not continue.
		}

		char Continue = 'Y';

		while (toupper(Continue) == 'Y')
		{
			_DrawScreenHeader("\tUpdate Clients Info Screen");

			string AccountNumber;

			cout << "\nPlease Enter Client AccounNumber: ";
			AccountNumber = clsInputValidate::ReadString();

			while (!clsBankClients::IsClientExisted(AccountNumber))
			{
				cout << "\nAccountNumber is not found, Enter another one: ";
				AccountNumber = clsInputValidate::ReadString();
			}

			clsBankClients Client = clsBankClients::Find(AccountNumber);
			_PrintClient(Client);

			cout << "\nUpdated Client Info: ";
			cout << "\n---------------------------\n";

			_ReadClientInfo(Client);

			clsBankClients::enSaveResults SaveResults;

			SaveResults = Client.Save();

			switch (SaveResults)
			{
			case clsBankClients::enSaveResults::svSucceeded:
			{
				_PrintClient(Client);
				cout << "\nAccount Updated Successfully! :)\n";
				break;
			}
			case clsBankClients::enSaveResults::svFailedEmptyObject:
			{
				cout << "\nError Account was not saved because it is empty.\n";
				break;
			}
			}

			Continue = clsInputValidate::ReadChar("\nDo you want to delete another user? (Y/N)? ");
		}

	}
};

