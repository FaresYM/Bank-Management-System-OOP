#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClients.h"

class clsTotalBalancesScreen : protected clsScreen
{
private:
	static void PrintClientBalance(clsBankClients Client)
	{
		cout << "\t\t";
		cout << "| " << setw(25) << left << Client.AccountNumber();
		cout << "| " << setw(30) << left << Client.FullName();
		cout << "| " << setw(15) << left << Client.AccountBalance;

	}

	static double GetTotalBalances(vector <clsBankClients> vClients)
	{
		double TotalBalances = 0;

		for (clsBankClients& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}

public:

	static void ShowTotalBalancesScreen()
	{
		vector <clsBankClients> vClients = clsBankClients::GetClientsList();

		string Header = "\t" "  " "Total Balances Screen";
		string SubHeader = "\t" "      " "(" + to_string(vClients.size()) + ") Client(s).";

		clsScreen::_DrawScreenHeader(Header, SubHeader);

		cout << "\n\t\t__________________________________________________________________________________________\n" << endl;
		cout << "\t\t";
		cout << "| " << left << setw(25) << "Accout Number";
		cout << "| " << left << setw(30) << "Client Name";
		cout << "| " << left << setw(15) << "Balance";
		cout << "\n\t\t__________________________________________________________________________________________\n" << endl;

		if (vClients.size() == 0)
			cout << "\t\t\tThere is no clients in the system." << endl;
		else
			for (clsBankClients& Client : vClients)
			{
				PrintClientBalance(Client);
				cout << endl;
			}

		cout << "\t\t__________________________________________________________________________________________\n" << endl;

		cout << "\t\t\t\t\t\tTotal Balances = " << GetTotalBalances(vClients) << endl;
	}
};

