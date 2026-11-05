#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClients.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
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

	static void ShowFindClientScreen()
	{
		if (!CheckAccessRight(clsUsers::enPermissions::enFindClient))
		{
			return; //This will exit the function and it will not continue.
		}

		clsScreen::_DrawScreenHeader("\t" "    " "Find Client Screen");

		cout << "Enter Client AccounNumber: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClients::IsClientExisted(AccountNumber))
		{
			cout << "\nClient with AccountNumber (" << AccountNumber << ") is not existed, Enter Another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		cout << endl << "Client has found! :)" << endl;

		clsBankClients Client = clsBankClients::Find(AccountNumber);

		_PrintClient(Client);
	}
};

