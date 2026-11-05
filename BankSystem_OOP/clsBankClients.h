#pragma once

#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsUtil.h"

using namespace std;

class clsBankClients : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2};
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkedForDelete = false;


	static clsBankClients _ConvertLineToClientObject(string Line, string Separator = "_")
	{
		vector <string> vClientObject;

		vClientObject = clsString::SplitString(Line, Separator);

		string PinCodeFromFile = vClientObject[5];

		if (PinCodeFromFile.substr(0, 5) == "[Enc]")
		{
			string ActualEncrypted = PinCodeFromFile.substr(5); //معناها ابدأ القص من الحرف رقم 5 وحتى نهاية النص بحيث ميأخذش علامة التشفير [Enc]
			vClientObject[5] = clsUtil::DecryptText(ActualEncrypted, 15); 
		}
		else
		{
			vClientObject[5] = PinCodeFromFile;
		}

		return clsBankClients(enMode::UpdateMode, vClientObject[0], vClientObject[1], vClientObject[2],
			vClientObject[3], vClientObject[4], vClientObject[5], stod(vClientObject[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClients Client, string Separator = "_")
	{
		string Line;

		Line += Client.FirstName + Separator;
		Line += Client.LastName + Separator;
		Line += Client.Email + Separator;
		Line += Client.Phone + Separator;
		Line += Client.AccountNumber() + Separator;

		//We store the encrypted pincode not the real one.
		string EncryptedPinCode = "[Enc]" + clsUtil::EncryptText(Client.PinCode, 15);
		Line += EncryptedPinCode + Separator;

		Line += to_string(Client.AccountBalance);

		return Line;
	}

	static vector <clsBankClients> _LoadClientsDataFromFile()
	{
		vector <clsBankClients> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClients Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return vClients;
	}

	void _SaveClientsDataToFile(vector <clsBankClients> vClients)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::out);

		string Line;

		if (MyFile.is_open())
		{
			for (clsBankClients& C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					Line = _ConvertClientObjectToLine(C);

					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	void _AddNewLineToFile(string Line)
	{
		fstream MyFile;

		MyFile.open("Clients.txt", ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
		}

		MyFile.close();

	}

	static clsBankClients _GetEmptyClientObject()
	{
		return clsBankClients(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankClients _FindClient(string AccountNumber, string PinCode, bool JoinPinCode)
	{
		vector <clsBankClients> vClients;

		fstream MyFile;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClients Client = _ConvertLineToClientObject(Line);

				if (clsString::UpperAllString(Client.AccountNumber()) == clsString::UpperAllString(AccountNumber) && !JoinPinCode)
				{
					MyFile.close();
					return Client;
				}
				else if (clsString::UpperAllString(Client.AccountNumber()) == clsString::UpperAllString(AccountNumber) && (Client.PinCode == PinCode) && JoinPinCode)
				{
					MyFile.close();
					return Client;
				}
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	void _Update()
	{
		vector <clsBankClients> vClients = _LoadClientsDataFromFile();

		for (clsBankClients& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);
	}	

	void _AddNew()
	{
		_AddNewLineToFile(_ConvertClientObjectToLine(*this));
	}

public:

	clsBankClients(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	//We commented it because we print in UI not trhough object

	/*void Print()
	{
		cout << "\nClient Card:";
		cout << "\n----------------------";
		cout << "\nFirstName     : " << FirstName;
		cout << "\nLastName      : " << LastName;
		cout << "\nFullName      : " << FullName();
		cout << "\nEmail         : " << Email;
		cout << "\nPhone         : " << Phone;
		cout << "\nAccountNumber : " << _AccountNumber;
		cout << "\nPinCode       : " << _PinCode;
		cout << "\nAccountBalance: " << _AccountBalance;
		cout << "\n----------------------\n";
	}*/

	static clsBankClients Find(string AccountNumber)
	{
		return _FindClient(AccountNumber, "", false);
	}

	static clsBankClients Find(string AccountNumber, string PinCode)
	{
		return _FindClient(AccountNumber, PinCode, true);
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFailedEmptyObject;
			}
		}
		case enMode::UpdateMode:
		{
			_Update();

			return enSaveResults::svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (clsBankClients::IsClientExisted(AccountNumber()))
			{
				return enSaveResults::svFailedAccountNumberExists;
			}
			else
			{
				_AddNew();

				//We need to change the mode to update after add new
				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}
		}
		}
	}

	bool Delete()
	{

		vector <clsBankClients> vClients = _LoadClientsDataFromFile();

		for (clsBankClients &C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C._MarkedForDelete = true;

				_SaveClientsDataToFile(vClients);

				*this = _GetEmptyClientObject();

				return true;
			}
		}

		return false;
	}
	
	static bool IsClientExisted(string AccountNumber)
	{
		clsBankClients Client = clsBankClients::Find(AccountNumber);

		return (!Client.IsEmpty());
	}
	
	static clsBankClients GetAddNewClientObject(string AccounNumber)
	{
		return clsBankClients(enMode::AddNewMode, "", "", "", "", AccounNumber, "", 0);
	}

	static vector <clsBankClients> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	void Deposit(double Amount)
	{
		if (Amount > 0)
		{
			AccountBalance += Amount;
			Save();
		}
	}

	void WithDraw(double Amount)
	{
		if (Amount <= AccountBalance && Amount > 0)
		{
			AccountBalance -= Amount;
			Save();
		}
	}
	
};

