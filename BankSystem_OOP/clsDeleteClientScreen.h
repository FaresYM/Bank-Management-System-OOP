#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClients.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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
public:

	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRight(clsUsers::enPermissions::enDeleteClient))
		{
			return; //This will exit the function and it will not continue.
		}

		char Continue = 'Y';

		while (toupper(Continue) == 'Y')
		{
			clsScreen::_DrawScreenHeader("\t" "  " "Delete Client Screen");

			cout << "\nEnter Client AccountNumber: ";
			string AccountNumber = clsInputValidate::ReadString();

			while (!clsBankClients::IsClientExisted(AccountNumber))
			{
				cout << "\nAccountNumber is not found, Enter another one: ";
				AccountNumber = clsInputValidate::ReadString();
			}

			clsBankClients Client = clsBankClients::Find(AccountNumber);

			_PrintClient(Client);

			char Answer = clsInputValidate::ReadChar("\nAre you sure about deleting this client? (Y/N)? ");

			if (toupper(Answer) == 'Y')
			{
				if (Client.Delete())
				{
					cout << "\nClient deleted successfully" << endl;
				}
				else
				{
					cout << "\nClient was not deleted." << endl;
				}
			}

			Continue = clsInputValidate::ReadChar("\nDo you want to delete another client? (Y/N)? ");
		}
	}
};

