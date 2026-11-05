#pragma once

#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsLoginRegister.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:
	public:

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

		MyFile.open("LoginRegister.txt", ios::app);

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

		MyFile.open("LoginRegister.txt", ios::in);

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

	static bool _Login()
	{
		short Attempts = 3;
		string UserName, Password;
		bool LoginFailed = false;

		do
		{

			if (LoginFailed)
			{
				cout << "\nInvalid UserName/Password!... (" << Attempts << " attempts left).\n";
			}

			UserName = clsInputValidate::ReadString("\nEnter UserName: ");
			Password = clsInputValidate::ReadString("\nEnter Password: ");

			CurrentUser = clsUsers::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();

			if (LoginFailed)
			{
				Attempts--;

				if (Attempts == 0)
				{
					system("cls");
					system("color 4F");
					cout << "\t\t\t\t\t" << "--------------------------------------------\n" << endl;
					cout << "\t\t\t\t\t" << " Attempts are over! Your account is locked.\n" << endl;
					cout << "\t\t\t\t\t" << "--------------------------------------------\n" << endl;

					system("pause > nul");

					return false;
				}
			}

		} while (LoginFailed);

		clsLoginRegister::AddNewLoginRegister();

		clsMainScreen::ShowMainMenu();
		
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		clsScreen::_DrawScreenHeader("\t" "       " "Login Screen");

		return _Login();
	}
};

