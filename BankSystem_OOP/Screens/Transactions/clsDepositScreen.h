#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClients.h"

class clsDepositScreen : protected clsScreen
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
	
	static void ShowDepositScreen()
	{
		clsScreen::_DrawScreenHeader("\t\tDeposit Screen");

		cout << "Enter Client AccountNumber: ";
		string AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClients::IsClientExisted(AccountNumber))
		{
			cout << "\nClient AccounNumber (" << AccountNumber << ") is not found, Enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClients Client = clsBankClients::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\nPlease enter deposit amount: ";
		double Amount = clsInputValidate::ReadDblNumber();

		char Answer = clsInputValidate::ReadChar("\nAre you sure you want to deposit this amount? (Y/N)? ");

		
		if (toupper(Answer) == 'Y')
		{
			if (Amount > 0 && Amount != 0)
			{
				Client.Deposit(Amount);
				cout << "\nAmount deposited successfully!" << endl;
				cout << "\nNew Balance is " << Client.AccountBalance << endl;
			}
			else
			{
				cout << "\nAmount was not deposited!" << endl;
				cout << "\nYour Balance is " << Client.AccountBalance << endl;
			}
		}
		else
		{
			cout << "\nAmount was not deposited!" << endl;
		}
	}
};

