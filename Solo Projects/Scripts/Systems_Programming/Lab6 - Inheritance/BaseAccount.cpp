#include "BaseAccount.h"
#include <iostream>

void BaseAccount::Withdraw(float amount)
{
	accBalance -= amount;
	withdrawls++;
	std::cout << "You have: $" << amount << " subtracted from your account\n";
	std::cout << "Your withdrawals: " << withdrawls << "\n";
	std::cout << "Account balance: " << accBalance << "\n";
}
void BaseAccount::Deposit(float amount)
{
	accBalance += amount ;
	std::cout << "You have: $" << amount << " added to your account\n";
	std::cout << "Account balance: " << accBalance << "\n";
}
float BaseAccount::GetBalance() const
{
	return accBalance;
}