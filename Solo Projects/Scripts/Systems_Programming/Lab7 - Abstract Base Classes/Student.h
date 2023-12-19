#pragma once
#include "Base1.h"
class Student :
    public Base1
{
private:
    float GPA;

public:
    void SetGPA(float gpa);
    void DisplayRecord();
};

