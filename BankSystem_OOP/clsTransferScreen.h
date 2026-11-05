#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClients.h"
#include "clsInputValidate.h"
#include "clsTransferLog.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _Transfer()
	{
		string SenderAccountNumber, ReceiverAccountNumber;

		SenderAccountNumber = clsInputValidate::ReadString("\nEnter AccountNumber to transfer from: ");

		clsBankClients SenderClient = clsBankClients::Find(SenderAccountNumber);
		_PrintClient(SenderClient);

	
		ReceiverAccountNumber = clsInputValidate::ReadString("\nEnter AccountNumber to transfer to: ");

		clsBankClients ReceiverClient = clsBankClients::Find(ReceiverAccountNumber);
		_PrintClient(ReceiverClient);

		cout << "\nEnter Transfer Amount: ";
		double TransferedAmount = clsInputValidate::ReadDblNumber();

		while (TransferedAmount > SenderClient.AccountBalance)
		{
			cout << "\nAmount exceeds the available balance, Enter another amount: ";
			TransferedAmount = clsInputValidate::ReadDblNumber();
		}

		char Answer = clsInputValidate::ReadChar("\nAre you sure you want to perform this transaction? (Y/N)? ");

		if (toupper(Answer) == 'Y')
		{
			if (TransferedAmount > 0)
			{
				SenderClient.WithDraw(TransferedAmount);
				ReceiverClient.Deposit(TransferedAmount);

				cout << "\nAmount Transfered successfully!\n";

				_PrintClient(SenderClient);
				_PrintClient(ReceiverClient);
				clsTransferLog::AddNewTransferLog(CurrentUser, SenderClient, ReceiverClient, TransferedAmount);
			}
			else
			{
				cout << "\nAmount was not transfered.\n";
			}
		}
		else
		{
			cout << "\nAmount was not transfered.\n";
		}
	}

	static void _PrintClient(clsBankClients Client)
	{
		cout << "\nClient Card:";
		cout << "\n----------------------";
		cout << "\nFullName      : " << Client.FullName();
		cout << "\nAcc. Number   : " << Client.AccountNumber();
		cout << "\nBalance       : " << Client.AccountBalance;
		cout << "\n----------------------\n";
	}

public:

	static void ShowTransferScreen()
	{
		clsScreen::_DrawScreenHeader("\t" "     " "Transfer Screen");

		_Transfer();
	}
};

