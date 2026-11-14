#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsTransferLog.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
	static void _PrintTransferLogLine(clsTransferLog::stTransferLog TransferLog)
	{
		cout << "\t";
		cout << "| " << setw(23) << left << TransferLog.DateTime;
		cout << "| " << setw(12) << left << TransferLog.SenderAccountNumber;
		cout << "| " << setw(12) << left << TransferLog.ReceiverAccountNumber;
		cout << "| " << setw(8) << left << TransferLog.TransferedAmount;
		cout << "| " << setw(12) << left << TransferLog.SenderBalance;
		cout << "| " << setw(12) << left << TransferLog.ReceiverBalance;
		cout << "| " << setw(10) << left << TransferLog.UserName;
	}

public:
	static void ShowTransferLogListScreen()
	{
		vector <clsTransferLog::stTransferLog> vTransferLogs = clsTransferLog::GetTransferLogsList();

		string Header = "\tTransfer Log List Screen";
		string SubHeader = "\t     (" + to_string(vTransferLogs.size()) + ") Record(s).\n";

		_DrawScreenHeader(Header, SubHeader);

		cout << "\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t";
		cout << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(12) << "S. Acc.Num";
		cout << "| " << left << setw(12) << "R. Acc.Num";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(12) << "S. Balance";
		cout << "| " << left << setw(12) << "R. Balance";
		cout << "| " << left << setw(10) << "User";
		cout << "\n\t_____________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		if (vTransferLogs.size() == 0)
			cout << "\t\t\t\t\t   No Transfers available in the system!\n";
		else
		{
			for (clsTransferLog::stTransferLog TransferLog : vTransferLogs)
			{
				_PrintTransferLogLine(TransferLog);
				cout << endl;
			}
		}

		cout << "\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;
	}
};
