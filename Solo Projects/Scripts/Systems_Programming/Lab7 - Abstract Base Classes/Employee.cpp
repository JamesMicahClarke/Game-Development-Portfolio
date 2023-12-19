#include "Employee.h"
#include <iostream>

void Employee::SetSalary(int _salary)
{
	salary = _salary;
}
void Employee::DisplayRecord()
{
	std::cout << "Name: " << GetName() << " Salary: " << salary << "\n";
}