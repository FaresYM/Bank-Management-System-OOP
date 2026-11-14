#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClients.h"

class clsWithDrawScreen : protected clsScreen
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

	static void ShowWithDrawScreen()
	{
		clsScreen::_DrawScreenHeader("\t" "      " "WithDraw Screen");

		cout << "Enter Client AccountNumber: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClients::IsClientExisted(AccountNumber))
		{
			cout << "\nClient AccounNumber (" << AccountNumber << ") is not found, Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClients Client = clsBankClients::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\nPlease enter withdraw amount: ";
		double Amount = clsInputValidate::ReadDblNumberBetween(1, Client.AccountBalance, "\nCannot withdraw, You must Enter a valid amount: ");

		char Answer = clsInputValidate::ReadChar("\nAre you sure you want to withdraw this amount? (Y/N)? ");


		if (toupper(Answer) == 'Y')
		{
			Client.WithDraw(Amount);
			cout << "\nAmount withdrawn successfully!" << endl;
			cout << "\nNew Balance is " << Client.AccountBalance << endl;
		}
		else
		{
			cout << "\nAmount was not withdrawn!" << endl;
		}
	}
};

