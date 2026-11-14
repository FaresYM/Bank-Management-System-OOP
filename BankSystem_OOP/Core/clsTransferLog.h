#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsString.h"
#include "clsUsers.h"
#include "clsBankClients.h"

using namespace std;

class clsTransferLog
{
public:
	struct stTransferLog
	{
		string DateTime;
		string SenderAccountNumber;
		string ReceiverAccountNumber;
		double TransferedAmount = 0;
		double SenderBalance = 0;
		double ReceiverBalance = 0;
		string UserName;
	};

private:

	static inline const string _FileName = "Databases/TransferLog.txt";

	static string _ConvertTransferLogToLine(clsUsers User, clsBankClients Sender, clsBankClients Receiver, double Amount, string Separator = "//")
	{
		string Line;

		Line += clsDate::GetSystemDateTimeString() + Separator;
		Line += Sender.AccountNumber() + Separator;
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

		if (vTransferLogs.size() >= 7)
		{
			TransferLog.DateTime = vTransferLogs[0];
			TransferLog.SenderAccountNumber = vTransferLogs[1];
			TransferLog.ReceiverAccountNumber = vTransferLogs[2];
			TransferLog.TransferedAmount = stod(vTransferLogs[3]);
			TransferLog.SenderBalance = stod(vTransferLogs[4]);
			TransferLog.ReceiverBalance = stod(vTransferLogs[5]);
			TransferLog.UserName = vTransferLogs[6];
		}

		return TransferLog;
	}

	static void _AddNewLineToFile(string Line)
	{
		fstream MyFile;
		MyFile.open(_FileName, ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	static vector <stTransferLog> _LoadTransfersLogFromFile()
	{
		vector <stTransferLog> vTransferLogs;
		fstream MyFile;

		MyFile.open(_FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				if (!Line.empty())
				{
					vTransferLogs.push_back(_ConvertLineToTransferLog(Line));
				}
			}
			MyFile.close();
		}

		return vTransferLogs;
	}

public:
	static void AddNewTransferLog(clsUsers User, clsBankClients Sender, clsBankClients Receiver, double Amount)
	{
		_AddNewLineToFile(_ConvertTransferLogToLine(User, Sender, Receiver, Amount));
	}

	static vector <stTransferLog> GetTransferLogsList()
	{
		return _LoadTransfersLogFromFile();
	}
};
