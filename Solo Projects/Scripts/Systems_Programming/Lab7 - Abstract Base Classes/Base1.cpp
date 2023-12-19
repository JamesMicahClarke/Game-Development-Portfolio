#include "Base1.h"
#include <iostream>


Base1::Base1()
{
}
Base1::~Base1()
{
	delete[] character;
}
void Base1::baseCopy(Base1& opIn)
{
	*this = opIn;
}
Base1& Base1::operator=(const Base1& op)
{
	if (this != & op)
	{
		SetName(op.character);
	}

	return *this;
}
void Base1::SetName(const char* name)
{

	int length = strlen(name) + 1;
	character = new char[length];
	strcpy_s(character, length, name);
}
char* Base1::GetName()
{
	return character;
}