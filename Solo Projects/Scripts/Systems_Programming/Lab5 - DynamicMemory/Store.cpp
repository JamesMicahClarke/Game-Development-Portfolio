#include "Store.h"
#include <vector>
#include <iostream>
#include "StringHelpers.h"

Store::Store() {
	int num = 200;
	int purchases = 10000;
	int returns = 10000;
	for (int i = 0; i < num; i++) {
		Register* r = new Register();
		for (int j = 0; i < purchases; i++) {
			r->Payment(10000);
		}
		for (int j = 0; i < returns; i++) {
			r->Refund(10000);
		}
		_registers.push_back(r);
	}
}
Store::~Store()
{
	for (int i = 0; i < _registers.size(); i++)
	{
		delete _registers[i];
	}
}
long long Store::GetReceipts() {
	long long* receipts = new long long();
	for (int i = 0; i < _registers.size(); i++) {
		long long* registerTotal = new long long(_registers[i]->GetCashReceipts() + _registers[i]->GetCreditReceipts());
		long long temp = *registerTotal;
		delete registerTotal;
		*receipts += temp;
	}
	std::cout << "\t\tStore: " << StringHelpers::FormatMoneyText(*receipts) << std::endl;
	long long keep = *receipts;
	delete receipts;
	return keep;
}
