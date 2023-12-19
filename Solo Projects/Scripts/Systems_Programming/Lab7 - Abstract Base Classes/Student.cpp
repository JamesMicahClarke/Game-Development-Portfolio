#include "student.h"
#include <iostream>

void Student::SetGPA(float gpa)
{
	GPA = gpa;
}
void Student::DisplayRecord()
{
	std::cout << "Student: " << GetName() << " GPA: " << GPA << "\n";
}