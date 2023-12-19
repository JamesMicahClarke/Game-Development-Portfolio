#include "TriangleStack.h"
#include <iostream>

void TriangleStack::SetBase(float base)
{
	mBase = base;
}
void TriangleStack::SetHeight(float height)
{
	mHeight = height;
}
float TriangleStack::GetArea()
{
	float area = (mBase * mHeight) / 2;
	return area;
}