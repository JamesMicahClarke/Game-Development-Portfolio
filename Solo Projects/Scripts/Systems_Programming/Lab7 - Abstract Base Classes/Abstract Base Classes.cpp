// Abstract Base Classes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Base1.h"
#include "Employee.h"
#include "Student.h"


int Validate()
{
	int number;
	bool run = true;
	std::cin >> number;
	while (run)
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please choose a valid number.\n";
			std::cin >> number;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			run = false;
		}
	}
	return number;
}
void AddRecord(std::vector<Base1*>& v)
{
	std::cout << "What record would you like to add?\n1. Employee\n2. Student\n";
	int pick;
	pick = Validate();
	Employee* answer = new Employee();
	Student* answer2 = new Student();
	switch (pick)
	{
	case 1:
		char name[32];
		std::cout << "Please input a name\n";
		std::cin.getline(name, 32);
		int salary;
		std::cout << "Please input a salary\n";
		std::cin >> salary;
		answer->SetName(name);
		answer->SetSalary(salary);
		v.push_back(answer);
		
		break;
	case 2:
		
		char name2[32];
		std::cout << "Please input a name\n";
		std::cin.getline(name, 32);
		float gpa;
		std::cout << "Please input a gpa\n";
		std::cin >> gpa;
		answer->SetName(name);
		answer->SetSalary(gpa);
		v.push_back(answer);
		
		break;
	}
}
void DisplayRecords(std::vector<Base1*>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		v[i]->DisplayRecord();
	}
}
void DuplicateRecord(std::vector<Base1*>& v)
{
	
	std::cout << "What index would you like to input in?\n1. Employee\n2. Student";
	int answer = Validate();
	Employee* test = dynamic_cast<Employee*>(v[answer]);
	Student* test2 = dynamic_cast<Student*>(v[answer]);
	switch (answer)
	{
	case 1:
		//vector elements start at 0.

		if (test != nullptr)
		{
			Base1* copy = new Employee(*test);
			v.push_back(copy);

			std::cout << "Employee\n";
		}
		break;
	case 2:
		
		if (test2 != nullptr)
		{
			Base1* copy2 = new Student(*test2);
			v.push_back(copy2);
			std::cout << "Student\n";
		}
		break;
	}
		
		
}
int main()
{
	std::vector<Base1*> ptr;
	bool run = true;
	int choice;
	while (run)
	{
		std::cout << "Record Menu\n1. Add a record\n2. Display records\n3. Duplicate a record\n";
		choice = Validate();

		switch (choice)
		{
		case 1:
			AddRecord(ptr);
			break;
		case 2:
			DisplayRecords(ptr);
			break;
		case 3:
			DuplicateRecord(ptr);
			break;
		case 4:
			run = false;
			break;
		}
	}
	for (int i = 0; i < ptr.size(); i++)
	{
		delete ptr[i];
	}
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
