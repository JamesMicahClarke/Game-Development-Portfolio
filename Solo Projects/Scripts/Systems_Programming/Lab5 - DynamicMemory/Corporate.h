#include <vector>
#include "Region.h"
#include "StringHelpers.h"

struct Corporate {
	std::vector<Region*> regions;

	Corporate() {
		int num = 35;
		for (int i = 0; i < num; i++) {
			Region* r = new Region;
			regions.push_back(r);
		}
	}

	~Corporate()
	{
		for (int i = 0; i < regions.size(); i++)
		{
			delete regions[i];
		}
	}

	long long GetReceipts() {
		long long* receipts = new long long();
		for (int i = 0; i < regions.size(); i++) {
			*receipts += regions[i]->GetReceipts();
		}
		long long temp = *receipts;
		delete receipts;
		return temp;
	}
};