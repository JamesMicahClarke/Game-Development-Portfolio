// C++Basics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void Prog1();
void Prog2();
void Prog3();
void Prog4();
void Prog5();
void Prog6();
void Prog7();
void Prog8();
void Prog9();
void Prog10();
int main()
{
	Prog1();
	Prog2();
	Prog3();
	Prog4();
	Prog5();
	Prog6();
	Prog7();
	Prog8();
	Prog9();
	Prog10();
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



void Prog1()
{
	std::cout << "====Program 1====\n\n";
	std::cout << "Input your initials: ";
	char initials[3];
	std::cin.getline(initials, 3);
	int age;
	bool run = true;
	while (run)
	{
		std::cout << "Input your age: ";
		std::cin >> age;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		else
		{
			int years = age * 365;
			std::cout << initials << ", you've been alive for " << years << " days now!\n";
			run = false;
		}
	}
	
}

void Prog2()
{
	std::cout << "====Program 2====\n\n";

	std::cout << "Please input 5 numbers \n";
	int number[5];
	for (int i = 0; i < 5; i++)
	{
		std::cout << "Enter your number here: ";
		std::cin >> number[i];
		
	}
	std::cout << "Your number: ";
	for (int i = 0; i < 5; i++)
	{
		std::cout << number[i];
	}
}

void Prog3()
{
	std::cout << "====Program 3====\n\n";

	int a;
	int b;
	int c;
	

	std::cout << "Please input 3 numbers \n";
	
	std::cout << "First num: ";
	std::cin >> a;
	
	std::cout << "Second num: ";
	std::cin >> b;
	
	std::cout << "Third num:";
	std::cin >> c;
	
	int equation1 = a + 1 * b + 2 - c;
	int equation2 = (a + 1) * (b + 2) - c;

	std::cout << "Variable a: " << a << "\n" << "Variable b: " << b << "\n" << "Variable c: " << c << "\n" << "a + 1 * b + 2 - c = " << equation1 << "\n" << "(a + 1) * (b + 2) - c = " << equation2 << "\n";
}

void Prog4()
{
	std::cout << "====Program 4====\n\n";
	
	std::cout << "type: " << "          " << "Range: " << "\n\n" << "----------------------\n\n";
	std::cout << "short" << "          " << SHRT_MIN << " to " << SHRT_MAX << "\n";
	std::cout << "ushort" << "          " << "0" << " to " << USHRT_MAX << "\n";
	std::cout << "int" << "          " << INT_MIN << " to " << INT_MAX << "\n";
	std::cout << "uint" << "          " << "0" << " to " << UINT_MAX << "\n";
	std::cout << "long" << "          " << LONG_MIN << " to " << LONG_MAX << "\n";
	std::cout << "ulong" << "          " << "0" << " to " << ULONG_MAX << "\n";
	std::cout << "llong" << "          " << LLONG_MIN << " to " << LLONG_MAX << "\n";
	std::cout << "ullong" << "          " << "0" << " to " << ULLONG_MAX << "\n";
}

void Prog5()
{
	std::cout << "====Program 5====\n\n";

	char name[32];
	std::cout << "Please type your full name here: ";
	std::cin.getline(name, 32);
	std::cout << name << "! " << "Did you know that mermaids are fictional beings?!\n";
}

void Prog6()
{
	std::cout << "====Program 6====\n\n";

	
	bool ofAge = true;
	while (ofAge)
	{
		std::cout << "Please enter your age: ";
		int age;
		std::cin >> age;

		if (age < 21)
		{
			std::cout << "You're too young! Try again when you're older!" << "\n";
			ofAge = false;
		}
		else
		{
			std::cout << "Welcome to the club! LETS GET WILD!!!!!" << "\n" << "*turns into animals*" << "\n";
		}
	}
	
}

void Prog7()
{
	std::cout << "====Program 7====\n\n";

	bool run = true;
	while (run)
	{
		std::cout << "Please type in an EVEN number: ";
		int even;
		std::cin >> even;
		if (even % 2 == 0)
		{
			std::cout << "EVEN the gods know your power!" << "\n\n";
		}
		else
		{
			std::cout << "Why did you choose to disobey?! Leave Immediately!" << "\n";
			run = false;
		}	
	}
	
}

void Prog8()
{
	std::cout << "====Program 8====\n\n";

	std::cout << "Please enter a divisor: ";
	int divisor;
	std::cin >> divisor;
	bool gen = true;
	srand(time(NULL));
	for ( int i = 0; i < 3; i++)
	{
		int random = rand();
		if (random % divisor == 0)
		{
			std::cout << random << "     " << "-yes" << "\n";
		}
		else
		{
			std::cout << random << "     " << "-no" << "\n";
		}
	}
}

void Prog9()
{
	std::cout << "====Program 9====\n\n";

	enum popsicles { Red = 1, Blue, Green, Purple};
	int pop;
	bool run = true;
		std::cout << "Which color Popsicle would you like?" << "\n" << "1. Red\n" << "2. Blue\n" << "3. Green\n" << "4. Purple\n";
		std::cin >> pop;
		switch (pop)
		{
		case Red:
			std::cout << "Red is Yummy and sweet!";
			break;
		case Blue:
			std::cout << "Blue is a tasty treat!";
			break;
		case Green:
			std::cout << "Green tastes like feet!";
			break;
		case Purple:
			std::cout << "Purple is ready to eat!";
			break;
		}
}

void Prog10()
{
	std::cout << "====Program 10====\n\n";
	enum choice {Easy = 1, Normal, Hard};
	std::cout << "Choose your difficulty" << "\n" << "1. Easy\n" << "2. Normal\n" << "3. Hard\n" << "You've chosen: ";
	int levels;
	std::cin >> levels;
	int enemies;
	
	switch (levels)
	{
	case 1:
		srand(time(NULL));
		enemies = rand() % 10 +1;
		std::cout << "Time to fight " << enemies << " enemies!" << "\n";
		break;
	case 2:
		srand(time(NULL));
		enemies = rand() % 30 + 1;
		std::cout << "Time to fight " << enemies << " enemies!" << "\n";
		break;
	case 3:
		srand(time(NULL));
		enemies = rand() % 100 + 1;
		std::cout << "Time to fight " << enemies << " enemies!" << "\n";
		break;
	}
}