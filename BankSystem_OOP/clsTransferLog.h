#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsBankClients.h"
#include "Global.h"

using namespace std;

class clsTransferLog : protected clsScreen
{
public:
	struct stTransferLog
	{
		string DateTime;
		string SenderAccountNumber;
		string ReceiverAccountNumber;
		double TransferedAmount;
		double SenderBalance;
		double ReceiverBalance;
		string UserName;
	};

private:
	static string _ConvertTransferLogToLine(clsUsers User, clsBankClients Sender, clsBankClients Receiver, double Amount, string Separator = "//")
	{
		string Line;

		Line += clsDate::GetSystemDateTimeString() + Separator;
		Line += Sender.AccountNumber()  + Separator;
		Line += Receiver.AccountNumber() + Separator;
		Line += to_string(Amount) + Separator;
		Line += to_string(Sender.AccountBalance) + Separator;
		Line += to_string(Receiver.AccountBalance) + Separator;
		Line += User.UserName;

		return Line;
	}

	static stTransferLog _ConvertLineToTransferLog(string Line, string Separator = "//")
	{
		vector <string> vTransferLogs = clsString::SplitString(Line, Separator);
		stTransferLog TransferLog;

		TransferLog.DateTime = vTransferLogs[0];
		TransferLog.ReceiverAccountNumber = vTransferLogs[1];
		TransferLog.SenderAccountNumber = vTransferLogs[2];
		TransferLog.TransferedAmount = stod(vTransferLogs[3]);
		TransferLog.SenderBalance = stod(vTransferLogs[4]);
		TransferLog.ReceiverBalance = stod(vTransferLogs[5]);
		TransferLog.UserName = vTransferLogs[6];

		return TransferLog;
	}

	static void _AddNewLineToFile(string Line)
	{
		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
		}

		MyFile.close();

	}

	static vector <stTransferLog> _LoadTransfersLogFromFile()
	{
		vector <stTransferLog> vTransferLogs;

		fstream MyFile;

		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				stTransferLog TransferLog = _ConvertLineToTransferLog(Line);

				vTransferLogs.push_back(TransferLog);
			}
			MyFile.close();
		}

		return vTransferLogs;
	}

	static void _PrintTransferLogLine(stTransferLog TransferLog)
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
	
	static void AddNewTransferLog(clsUsers User, clsBankClients Sender, clsBankClients Receiver, double Amount)
	{
		_AddNewLineToFile(_ConvertTransferLogToLine(User, Sender, Receiver, Amount));
	}

	static void ShowTransferLogListScreen()
	{
		vector <stTransferLog> vTransferLogs = _LoadTransfersLogFromFile();

		string Header = "\tTransfer Log List Screen";
		string SubHeader = "\t" "     " "(" + to_string(vTransferLogs.size()) + ") Records(s).\n";

		clsScreen::_DrawScreenHeader(Header, SubHeader);

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
			cout << "\t\t\t\t\t" "   " "No Transfers available in the system!\n";
		else
			for (stTransferLog TransferLog : vTransferLogs)
			{

				_PrintTransferLogLine(TransferLog);
				cout << endl;
			}

		cout << "\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

	}
};

