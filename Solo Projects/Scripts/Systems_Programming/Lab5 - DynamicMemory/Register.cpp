#include <iostream>
#include "Register.h"
#include "StringHelpers.h"

Register::Register() {
	_cashReceipts = new long long(10000);
	_creditReceipts = new long long(10000);
}

Register::~Register()
{
	delete _cashReceipts;
	delete _creditReceipts;
}

void Register::Payment(long long amount) {
	*_cashReceipts += amount;
}
void Register::Refund(long long amount) {
	if (amount > * _cashReceipts) {
		*_cashReceipts = 0;
	} else {
		*_cashReceipts -= amount;
	}
}
long long Register::GetCashReceipts() {
	std::cout << "\t\t\tCash: " << StringHelpers::FormatMoneyText(*_cashReceipts) << std::endl;
	return *_cashReceipts;
}
long long Register::GetCreditReceipts() {
	std::cout << "\t\t\tCredit: " << StringHelpers::FormatMoneyText(*_creditReceipts) << std::endl;
	return *_creditReceipts;
}