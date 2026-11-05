#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClients.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:
	static void _PrintClientRecordLine(clsBankClients Client)
	{
		cout << "\t";
		cout << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(25) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}
public:

	static void ShowClientsList()
	{
		if (!CheckAccessRight(clsUsers::enPermissions::enClientsList))
		{
			return; //This will exit the function and it will not continue.
		}

		vector <clsBankClients> vClients = clsBankClients::GetClientsList();
		
		cout << endl << endl;
		
		string Header = "\t" "    " "Clients List Screen";
		string SubHeader = "\t" "       " "(" + to_string(vClients.size()) + ") Client(s).\n";

		clsScreen::_DrawScreenHeader(Header, SubHeader);

		cout << "\t_________________________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "\t";
		cout << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(20) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(25) << "Email";
		cout << "| " << left << setw(10) << "Pin Code";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n\t_____________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		if (vClients.size() == 0)
			cout << "\t\t\t\t\t" "   " "No clients available in the system!\n";
		else
			for (clsBankClients& Client : vClients)
			{

				_PrintClientRecordLine(Client);
				cout << endl;
			}

		cout << "\t_______________________________________________________";
		cout << "___________________________________________________\n" << endl;

	}

};

