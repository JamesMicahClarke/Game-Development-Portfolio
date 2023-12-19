#pragma once
#include "Base1.h"
class Employee :
    public Base1
{
private:
    int salary;

public:
    void SetSalary(int _salary);
    void DisplayRecord();
};

