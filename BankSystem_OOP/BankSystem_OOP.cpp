#include <iostream>
#include <string>
#include <iomanip>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsLoginScreen.h"

using namespace std;

int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}

}