// HelperLibrary.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Helper.h"

//int GetValidatedInt(const char* strMessage, int nMinimumRange = 0, int nMaximumRange = 0);
//void Helper::Random(int number);
void Helper::BinPrint(unsigned int n);
int main()
{
	unsigned int p = 32;
	void BinPrint(unsigned int p);
	//void Random(int num);
	//std::cout << num << "\n";
	const char message[100] = "Hello";
	const char* messageptr;
	int a = 0;
	int b = 0;
	Helper::GetValidatedInt(message, a, b);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
