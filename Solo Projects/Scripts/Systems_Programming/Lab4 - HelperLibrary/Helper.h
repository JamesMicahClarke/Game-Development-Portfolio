#pragma once
#include <iostream>


namespace Helper
{
	int GetValidatedInt(const char* strMessage, int nMinimumRange = 0, int nMaximumRange = 0)
	{
		int answer;
		std::cout << strMessage << "\n";
		std::cin >> answer;
		bool go = true;
		while (go)
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "Please input a number!\n";
				std::cout << strMessage << "\n";
				std::cin >> answer;
			}
			else
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			//if min and max is 0, do not check range. Otherwise check range.
			if (nMaximumRange != 0 || nMinimumRange != 0)
			{
				if (answer >= nMinimumRange && answer <= nMaximumRange)
				{
					std::cout << "checking range";
					return answer;
					go = false;
				}
				else 
				{
					std::cout << "Please input a number!\n";
					std::cout << strMessage << "\n";
					std::cin >> answer;
				}
			}
			else
			{
				std::cout << "min and max is 0";
				go = false;
			}
		}
	}
	void BinPrint(unsigned int n)
	{
		for (int i = 1 << 30; i > 0; i = i / 2)
		{
			if ((n & i) != 0)
			{
				std::cout << "1";
			}
			else
			{
				std::cout << "0";
			}
		}
	}
	void ClearBuff(int number)
	{
		bool run = true;
		while (run)
		{
			std::cin >> number;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "invalid answer please try again\n";
				std::cin >> number;
			}
			else
			{
				std::cout << "Valid answer accepted\n";
			}
		}
	}
	/*void Random(int number)
		{
			srand(time(NULL));
			number = rand() % 10 + 1;
			std::cout << number;
		}*/

	
	
}