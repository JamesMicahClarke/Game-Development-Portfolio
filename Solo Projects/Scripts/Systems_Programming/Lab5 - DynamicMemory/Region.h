#pragma once
#include <vector>
#include "Store.h"
#include "StringHelpers.h"

struct Region {
	std::vector<Store*> stores;

	Region() {
		int num = 40;
		for (int i = 0; i < num; i++) {
			Store* s = new Store;
			stores.push_back(s);
		}
	}

	~Region()
	{
		for (int i = 0; i < stores.size(); i++)
		{
			delete stores[i];
		}
	}
	
	long long GetReceipts() {
		long long* receipts = new long long();
		for (int i = 0; i < stores.size(); i++) {
			*receipts += stores[i]->GetReceipts();
		}
		std::cout << "\t\Region: " << StringHelpers::FormatMoneyText(*receipts) << std::endl;
		long long save = *receipts;
		delete receipts;
		return save;
	}
};