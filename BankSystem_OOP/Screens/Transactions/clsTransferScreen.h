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

	static string _ReadValidAccountNumber(string Message)
	{
		string AccountNumber = clsInputValidate::ReadString(Message);

		while (!clsBankClients::IsClientExisted(AccountNumber))
		{
			cout << "\nAccount Number is not found, enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static clsBankClients _ReadReceiverClient(string SenderAccountNumber)
	{
		string ReceiverAccountNumber = _ReadValidAccountNumber("\nEnter Account Number to transfer to: ");

		while (clsString::UpperAllString(SenderAccountNumber) == clsString::UpperAllString(ReceiverAccountNumber))
		{
			cout << "\nYou cannot transfer money to the same account! Enter another Account Number: ";
			ReceiverAccountNumber = _ReadValidAccountNumber("");
		}

		return clsBankClients::Find(ReceiverAccountNumber);
	}

	static double _ReadTransferAmount(clsBankClients SenderClient)
	{
		cout << "\nEnter Transfer Amount: ";
		double Amount = clsInputValidate::ReadDblNumber();

		while (Amount <= 0 || Amount > SenderClient.AccountBalance)
		{
			if (Amount <= 0)
				cout << "\nAmount must be greater than zero, enter another amount: ";
			else
				cout << "\nAmount exceeds the available balance, enter another amount: ";

			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}

	static void _Transfer()
	{
		string SenderAccountNumber = _ReadValidAccountNumber("\nEnter Account Number to transfer from: ");
		clsBankClients SenderClient = clsBankClients::Find(SenderAccountNumber);
		_PrintClient(SenderClient);

		clsBankClients ReceiverClient = _ReadReceiverClient(SenderAccountNumber);
		_PrintClient(ReceiverClient);

		double TransferAmount = _ReadTransferAmount(SenderClient);

		char Answer = clsInputValidate::ReadChar("\nAre you sure you want to perform this transaction? (Y/N)? ");

		if (toupper(Answer) == 'Y')
		{
			SenderClient.WithDraw(TransferAmount);
			ReceiverClient.Deposit(TransferAmount);
			clsTransferLog::AddNewTransferLog(CurrentUser, SenderClient, ReceiverClient, TransferAmount);

			cout << "\nAmount Transferred successfully!\n";
			_PrintClient(SenderClient);
			_PrintClient(ReceiverClient);
		}
		else
		{
			cout << "\nOperation cancelled. Amount was not transferred.\n";
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

