#pragma once

#include <iostream>
#include <fstream>
#include "clsDate.h"
#include "clsUsers.h"
#include "clsScreen.h"
#include "Global.h"

using namespace std;

class clsLoginRegister : protected clsScreen
{
public:

	static inline const string _FileName = "Databases/LoginRegister.txt";

	struct stLoginRegisterRecord {
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};

private:
	static string _ConvertUserLoginRegisterToLine(clsUsers User, string Separator = "//")
	{
		string Line;

		Line += clsDate::GetSystemDateTimeString() + Separator;
		Line += User.UserName + Separator;
		Line += User.Password + Separator;
		Line += to_string(User.Permissions);

		return Line;
	}
	static stLoginRegisterRecord _ConvertLineToRecord(string Line, string Separator = "//")
	{
		vector <string> vData = clsString::SplitString(Line, Separator);
		stLoginRegisterRecord Record;

		// شرط الأمان: نضمن أن الـ vector ممتلئ تماماً بـ 4 عناصر قبل تخصيص القيم
		if (vData.size() >= 4)
		{
			Record.DateTime = vData[0];
			Record.UserName = vData[1];
			Record.Password = vData[2];
			Record.Permissions = stoi(vData[3]);
		}
		else
		{
			// قيم افتراضية في حال وجود سطر تالف في الملف لتجنب انهيار البرنامج
			Record.DateTime = "N/A";
			Record.UserName = "N/A";
			Record.Password = "N/A";
			Record.Permissions = 0;
		}

		return Record;
	}


	static void _AddNewLineToFile(string Line)
	{
		fstream MyFile;

		MyFile.open(_FileName, ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
		}

		MyFile.close();

	}

	static vector <stLoginRegisterRecord> _LoadRegisterDataFromFile()
	{
		vector <stLoginRegisterRecord> RegisterData;

		fstream MyFile;

		MyFile.open(_FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				stLoginRegisterRecord Record = _ConvertLineToRecord(Line);

				RegisterData.push_back(Record);
			}
			MyFile.close();
		}

		return RegisterData;
	}

	static void _PrintLoginRecordLine(stLoginRegisterRecord Record)
	{
		cout << "\t";
		cout << "| " << setw(35) << left << Record.DateTime;
		cout << "| " << setw(25) << left << Record.UserName;
		cout << "| " << setw(15) << left << Record.Password;
		cout << "| " << setw(10) << left << Record.Permissions;
	}

public:

	static void AddNewLoginRegister()
	{
		_AddNewLineToFile(_ConvertUserLoginRegisterToLine(CurrentUser));
	}

	static void ShowLoginRegisterListScreen()
	{
		if (!CheckAccessRight(clsUsers::enPermissions::enLoginRegister))
		{
			return; //This will exit the function and it will not continue.
		}

		vector <stLoginRegisterRecord> vRegisterList = _LoadRegisterDataFromFile();

		string Header = "\t" "Login Register List Screen";
		string SubHeader = "\t" "     " "(" + to_string(vRegisterList.size()) + ") Record(s).\n";

		clsScreen::_DrawScreenHeader(Header, SubHeader);

		cout << "\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t";
		cout << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(25) << "UserName";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << "\n\t_____________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		if (vRegisterList.size() == 0)
			cout << "\t\t\t\t\t" "   " "No logins available in the register!\n";
		else
			for (stLoginRegisterRecord Record : vRegisterList)
			{

				_PrintLoginRecordLine(Record);

				cout << endl;
			}

		cout << "\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

	}
};

