// Pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
enum EnumColorDefinition { Turquoise = 1, Dandelion };
struct Car
{
	char Make[32];
	char Model[32];
	int Year;
	int Mileage;
	EnumColorDefinition Color;
};
void repaintCar(Car* ptrCar, EnumColorDefinition newcolor);
void printCar(Car c);
void printCarPointer(Car* ptrCar);
void addMileage(Car* ptrCar, int milestoadd);
void Prog1();
void Prog2(int number, int* point);
void Prog3();
int main()
{
	int address[16];
	int num;
	int* pnt;
	
	Prog1();
	srand(time(NULL));
	for (int i = 0; i < 15; i++)
	{
		address[i] = rand();
		num = address[i];
		pnt = &num;
	}
	Prog2(num, pnt);
	Prog3();

}

void Prog1()
{
	std::cout << "---------------Program 1---------------\n";
	int address[16];
	srand(time(NULL));
	for (int i = 0; i < 15; i++)
	{
		address[i] = rand();
		std::cout << address[i] << "\n";
		std::cout << &address[i] << "\n";
	}
}
void Prog2(int number, int* point)
{
	std::cout << "---------------Program 2---------------\n";
	std::cout << "Array slot value: " << number << "\n" << "Array memory address: " << point << "\n";

}
//part 1
void Prog3()
{
	std::cout << "---------------Program 3---------------\n";
	Car CarArray[4] = { "Car ", 4};
	Car* point;
	int colorInput;
	for (int i = 0; i < 3; i++)
	{
		std::cout << "What make car would you like?" << "\n";
		std::cin.getline(CarArray[i].Make, 32);//!!!

		std::cout << "What model do you choose?" << "\n";
		std::cin.getline(CarArray[i].Model, 32);

		std::cout << "What year is your car?" << "\n";
		std::cin >> CarArray[i].Year;
		while (!std::cin >> CarArray[i].Year)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please enter a number\n" << "What year is your car?" << "\n";
			std::cin >> CarArray[i].Year;
		}

		std::cout << "How much mileage does your car have?" << "\n";
		std::cin >> CarArray[i].Mileage;
		while (!std::cin >> CarArray[i].Mileage)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please enter a number\n" << "How much mileage does your car have?\n";
			std::cin >> CarArray[i].Mileage;
			
		}

		std::cout << "What color is your car?\n1. Turquoise\n2. Dandelion\n";
		std::cin >> colorInput;
		while (!std::cin || colorInput < 1 || colorInput > 2 )
		{
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "Please choose a number between 1 and 2!\n" << "What color is your car?\n1. Turquoise\n2. Dandelion\n";
				std::cin >> colorInput;
			}
			else if (colorInput > 2 || colorInput < 1)
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "Please choose a number between 1 and 2!\n" << "What color is your car?\n1. Turquoise\n2. Dandelion\n";
				std::cin >> colorInput;
			}
		}
		if (colorInput != 2)
		{
			CarArray[i].Color = Turquoise;


		}
		else
		{
			CarArray[i].Color = Dandelion;
		}
		
		point = &CarArray[i];
		std::cout << "Printing car...\n";
		printCar(*point);
		std::cout << "Printing car pointer...\n";
		printCarPointer(point);
		addMileage(point, CarArray[i].Mileage);
		repaintCar(point, CarArray[i].Color);
		printCar(*point);
		repaintCar(point, CarArray[i].Color);
		std::cin.ignore(INT_MAX, '\n');
	}
	std::cout << "original output\n";
	for (int indx = 0; indx < 3; indx++)
	{
		
		std::cout << "Car - " << CarArray[indx].Year << " ";
		if (CarArray[indx].Color != 2)
		{
			std::cout << "Turquoise";
		}
		else
		{
			std::cout << "Dandelion";
		}
		 std:: cout<< " " << CarArray[indx].Make << " " << CarArray[indx].Model << " with " << CarArray[indx].Mileage << " miles\n";
		 
	}
	
}
//void Validate(int num)
//{
//	bool run = true;
//	while (run)
//	{
//		std::cin >> num;
//		if (std::cin.fail())
//		{
//			std::cin.clear();
//			std::cin.ignore(INT_MAX, '\n');
//		}
//		else
//		{
//			run = false;
//		}
//	}
//}
void repaintCar(Car* ptrCar, EnumColorDefinition newcolor)
{
	if (newcolor != Turquoise)
	{
		newcolor = Turquoise;
	}
	else
	{
		newcolor = Dandelion;
	}
	ptrCar->Color = newcolor;
	std::cout << "Repainted version\n";
}
void printCar(Car c)
{
	std::cout << c.Year << " ";
	if (c.Color != 2)
	{
		std::cout << "Turquoise";
	}
	else
	{
		std::cout << "Dandelion";
	}
	 std::cout << " " << c.Make << " " << c.Model << " with " << c.Mileage << " miles.\n\n";

}
void printCarPointer(Car* ptrCar)
{
	std::cout << (*ptrCar).Year << " ";
	if ((*ptrCar).Color != 2)
	{
		std::cout << "Turquoise";
	}
	else
	{
		std::cout << "Dandelion";
	}
	std::cout << " " << (*ptrCar).Make << " " << (*ptrCar).Model << " with " << (*ptrCar).Mileage << " miles.\n\n";
}
void addMileage(Car* ptrCar, int milestoadd)
{
	milestoadd = ptrCar->Mileage + 10;
	std::cout << "New mileage: " << milestoadd << "\n";
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
