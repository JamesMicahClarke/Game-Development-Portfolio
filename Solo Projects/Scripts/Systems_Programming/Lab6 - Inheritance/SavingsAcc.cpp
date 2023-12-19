#include "SavingsAcc.h"
#include <iostream>

void SavingsAcc::Withdraw(float amount)
{
	if (withdrawls == 3)
	{
		std::cout << "You have reached the maximum amount of withdrawals for this account.\nWe could not register your withdrawal!\n";
		return;
	}
	else
	{
		std::cout << "You have a maximum limit of 3 withdrawls on this account.\n";
	}
	BaseAccount::Withdraw(amount);
}