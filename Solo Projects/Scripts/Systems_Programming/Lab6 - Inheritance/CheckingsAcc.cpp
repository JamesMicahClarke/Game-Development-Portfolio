#include "CheckingsAcc.h"
#include <iostream>

void CheckingsAcc::Withdraw(float amount)
{
	if (withdrawls > 10)
	{
		std::cout << "the amount of withdrawls on your account has exceeded the free withdrawl limit.\nEvery withdrawl from now on will be charged $5 on this account.\n";
		accBalance -= 5;
		std::cout << "Your account has been charged $5 for this service.\n";
	}
	else
	{
		std::cout << "You have a free limit of 10 withdrawls on this account.";
	}
	BaseAccount::Withdraw(amount);
}