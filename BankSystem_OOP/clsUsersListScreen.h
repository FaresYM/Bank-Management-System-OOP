#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUsers.h"

using namespace std;

class clsUsersListScreen : protected clsScreen
{
private:
	static void _PrintUserRecordLine(clsUsers User)
	{
		cout << "\t";
		cout << "| " << setw(25) << left << User.UserName;
		cout << "| " << setw(15) << left << User.Phone;
		cout << "| " << setw(25) << left << User.Email;
		cout << "| " << setw(15) << left << User.Password;
		cout << "| " << setw(10) << left << User.Permissions;
	}
public:

	static void ShowUsersList()
	{
		vector <clsUsers> vUsers = clsUsers::GetUsersList();

		string Header = "\t" "    " "Users List Screen";
		string SubHeader = "\t" "       " "(" + to_string(vUsers.size()) + ") User(s).\n";

		clsScreen::_DrawScreenHeader(Header, SubHeader);

		cout << "\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t";
		cout << "| " << left << setw(25) << "FullName";
		cout << "| " << left << setw(15) << "Phone";
		cout << "| " << left << setw(25) << "Email";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << "\n\t_____________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		if (vUsers.size() == 0)
			cout << "\t\t\t\t\t" "   " "No users available in the system!\n";
		else
			for (clsUsers User : vUsers)
			{

				_PrintUserRecordLine(User);
				cout << endl;
			}

		cout << "\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

	}
};

