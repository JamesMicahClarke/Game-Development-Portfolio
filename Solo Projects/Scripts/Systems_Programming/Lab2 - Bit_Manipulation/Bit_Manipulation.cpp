// Bit_Manipulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
unsigned int bitField = 0;
void TurnOn(int bit);
void TurnOff(int bit);
void Toggle(int bit);
void Negate();
void LeftShift();
void RightShift();
void BinaryPrint(unsigned int n);
int main()
{
	unsigned int test;
	int choice;
	enum options { TurnOn = 1, TurnOff, Toggle, Negate, LeftShift, RightShift, Exit };
	std::cout << "bitField: " << bitField << "\n";
	std::cout << "bits: ";
	BinaryPrint(bitField);
	bool run = true;
	while (run)
	{
		std::cout << "\n";
		std::cout << "1.TurnOn\n" << "2.TurnOff\n" << "3.Toggle\n" << "4.Nagate\n" << "5.LeftShift\n" << "6.RightShift\n" << "7.Exit\n" << "Choose an operation: ";
		std::cin >> choice;
		bool run = true;
		switch (choice)
		{
		case TurnOn:
			std::cout << "choose bit index: ";
			std::cin >> bitField;
			void TurnOn(int bitField);
			std::cout << "bitField: " << bitField << "\n";
			std::cout << "bits: ";
			BinaryPrint(bitField);
			break;
		case TurnOff:
			
			std::cout << "choose bit index: ";
			std::cin >> bitField;
			void TurnOff(int bitField);
			std::cout << "bitField: " << bitField << "\n";
			std::cout << "bits: ";
			BinaryPrint(bitField);
			break;
		case Toggle:
			std::cout << "choose bit index: ";
			std::cin >> bitField;
			void Toggle(int bitField);
			std::cout << "bitField: " << bitField << "\n";
			std::cout << "bits: ";
			BinaryPrint(bitField);
			break;
		case  Negate:
			void Negate();
			std::cout << "bitField: " << bitField << "\n";
			std::cout << "bits: ";
			BinaryPrint(~bitField);
			break;
		case LeftShift:
			void LeftShift();
			std::cout << "bitField: " << bitField << "\n";
			std::cout << "bits: ";
			BinaryPrint(bitField << 1);
			break;
		case RightShift:
			void RightShift();
			std::cout << "bitField: " << bitField << "\n";
			std::cout << "bits: ";
			BinaryPrint(bitField >> 1);
			break;
		case Exit:
			run = false;
			break;
		}
	}
	return 0;
}

void TurnOn(int bit)
{
	/*This function should take in a number to determine which bit should be turned on.You may set this up to be the bit index(like an array, but 0 would be the right - most,
	//1 would be the one to the left of that, etc) or you may have it represent the actual bit value itself(1, 2, 4, 8, 16, etc).Either method is fine, it just depends on how you
	//choose to write your main code to decide which number to pass as the parameter.

		HINT: “or” |*/

	bitField |= 1 << bit;
}
void TurnOff(int bit)
{
	bitField &= ~(1 << bit);
}
void Toggle(int bit)
{
	bitField ^= 1 << bit;
}
void Negate()
{
	bitField = ~bitField;
}
void LeftShift()
{
	bitField <<= 1;

}
void RightShift()
{
	bitField >>= 1;
}

void BinaryPrint(unsigned int n)
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

	/*for (int i = 0; i < 32; i++)
	{
		if (n > 1)
		{
				BinaryPrint(n / 2);
				std::cout << n % 2;
				
		}
	}*/
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
