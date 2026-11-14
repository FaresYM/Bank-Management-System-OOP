#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "Time.h"
#include "clsUtil.h"

using namespace std;

class clsUsers : public clsPerson
{
private:

	static inline const string _FileName = "Databases/Users.txt";

	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};

	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;

	bool _MarkedForDelete = false;

	static clsUsers _ConvertLineToUserObject(string Line, string Separator = "//")
	{
		vector <string> User = clsString::SplitString(Line, Separator);

		string PasswordFromFile = User[5];

		if (PasswordFromFile.substr(0, 5) == "[Enc]")
		{
			string ActualEncrypted = PasswordFromFile.substr(5); //معناها ابدأ القص من الحرف رقم 5 وحتى نهاية النص بحيث ميأخذش علامة التشفير [Enc] 
			User[5] = clsUtil::DecryptText(ActualEncrypted, 10);
		}
		else
		{
			User[5] = PasswordFromFile;
		}

		return clsUsers(enMode::UpdateMode, User[0], User[1], User[2], User[3], User[4], User[5], stoi(User[6]));
	}

	static string _ConvertUserObjectToLine(clsUsers User, string Separator = "//")
	{
		string Line;

		Line += User.FirstName + Separator;
		Line += User.LastName + Separator;
		Line += User.Email + Separator;
		Line += User.Phone + Separator;
		Line += User.UserName + Separator;

		//We store the encrypted password not the real one.
		string EncryptedPassword = "[Enc]" + clsUtil::EncryptText(User.Password, 10);
		Line += EncryptedPassword + Separator;

		Line += to_string(User.Permissions);

		return Line;
	}

	static vector <clsUsers> _LoadUsersDataFromFile()
	{
		vector <clsUsers> vUsers;

		fstream MyFile;

		MyFile.open(_FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUsers User = _ConvertLineToUserObject(Line);

				vUsers.push_back(User);
			}
			MyFile.close();
		}

		return vUsers;
	}

	void _SaveUsersDataToFile(vector <clsUsers> vUsers)
	{
		fstream MyFile;

		MyFile.open(_FileName, ios::out);

		string Line;

		if (MyFile.is_open())
		{
			for (clsUsers& U: vUsers)
			{
				if (U.MarkedForDelete() == false)
				{
					Line = _ConvertUserObjectToLine(U);

					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	void _AddNewLineToFile(string Line)
	{
		fstream MyFile;

		MyFile.open(_FileName, ios::app);

		if (MyFile.is_open())
		{
			MyFile << Line << endl;
		}

		MyFile.close();

	}

	static clsUsers _GetEmptyUserObject()
	{
		return clsUsers(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsUsers _FindUser(string UserName, string Password, bool JoinPassword)
	{
		fstream MyFile;

		MyFile.open(_FileName, ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUsers User = _ConvertLineToUserObject(Line);
				
				if (clsString::UpperAllString(User.UserName) == clsString::UpperAllString(UserName) && !JoinPassword)
				{
					MyFile.close();
					return User;
				}
				else if (clsString::UpperAllString(User.UserName) == clsString::UpperAllString(UserName) && (User.Password == Password) && JoinPassword)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	void _Update()
	{
		vector <clsUsers> vUsers = _LoadUsersDataFromFile();

		for (clsUsers& User : vUsers)
		{
			if (User.UserName == UserName)
			{
				User = *this;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);
	}

	void _AddNew()
	{
		_AddNewLineToFile(_ConvertUserObjectToLine(*this));
	}

public:

	enum enPermissions {enAll = -1, enClientsList = 1, enAddNewClient = 2, enDeleteClient = 4, enUpdateClient = 8,
						enFindClient = 16, enTransactions = 32, enManageUsers = 64, enCurrencyExchange = 128, enLoginRegister = 256};

	clsUsers(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string GetUserName()
	{
		return _UserName;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetPassword()
	{
		return _Password;
	}

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	_declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	_declspec(property(get = GetPassword, put = SetPassword)) string Password;
	_declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUsers Find(string UserName)
	{
		return _FindUser(UserName, "", false);
	}

	static clsUsers Find(string UserName, string Password)
	{
		return _FindUser(UserName, Password, true);
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedUserNameExists };

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
			if (clsUsers::IsUserExisted(UserName))
			{
				return enSaveResults::svFailedUserNameExists;
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

		vector <clsUsers> vUsers = _LoadUsersDataFromFile();

		for (clsUsers& U : vUsers)
		{
			if (U.UserName == UserName)
			{
				U._MarkedForDelete = true;

				_SaveUsersDataToFile(vUsers);

				*this = _GetEmptyUserObject();

				return true;
			}
		}

		return false;
	}

	static bool IsUserExisted(string UserName)
	{
		clsUsers User = clsUsers::Find(UserName);

		return (!User.IsEmpty());
	}

	static clsUsers GetAddNewUserObject(string UserName)
	{
		return clsUsers(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUsers> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermissions(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::enAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;

		return false;
	}
};

