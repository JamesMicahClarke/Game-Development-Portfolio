#include "TriangleHeap.h"
#include <iostream>

TriangleHeap::TriangleHeap()
{
}
TriangleHeap::~TriangleHeap()
{
	delete mBase;
	delete mHeight;
}
void TriangleHeap::TriangleCopy(TriangleHeap& copy)
{
	*this = copy;
}
TriangleHeap& TriangleHeap::operator=(const TriangleHeap& op)
{
	if (this != &op)
	{
		SetBase(*op.mBase);
		SetHeight(*op.mHeight);
	}

	return *this;
}
void TriangleHeap::SetBase(float base)
{
	*mBase = base;
}
void TriangleHeap::SetHeight(float height)
{
	*mHeight = height;
}
float TriangleHeap::GetArea()
{
	float area = (*mBase) * (*mHeight) / 2;
	return area;
}