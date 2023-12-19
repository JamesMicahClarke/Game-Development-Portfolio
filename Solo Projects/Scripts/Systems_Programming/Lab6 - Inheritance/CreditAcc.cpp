#include "CreditAcc.h"
#include <iostream>

void CreditAcc::Withdraw(float amount)
{
	spent = 40;
	if (amount > spent)
	{
		std::cout << "You've exceeded passed your spending limit! You must pay $5,000.\n";
		accBalance -= 5000;
	}
	else
	{
		std::cout << "There is a threshold of $40 for this account. Please refer to our Finance Policy.\n";
	}
	BaseAccount::Withdraw(amount);
}