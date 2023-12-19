// Pointers2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "TriangleHeap.h"
#include "TriangleStack.h"

void SwapValues(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	std::cout << "a = " << *a << "\nb = " << *b;
}
int AddNumbersReturnInt(int* a, int* b)
{
	int sum = *a + *b;
	std::cout << sum;
	return sum;
}
void AddNumbersReturnVoid(int a, int b, int* sum)
{
	int save = a + b;
	sum = &save;
	std::cout << *sum;
}
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(-1);
	_CrtDumpMemoryLeaks();

	int a = 5;
	int b = 6;
	int* sum = nullptr;
	std::cout << "a = " << a << "\nb = " << b << "\n";
	std::cout << "----AddNumbersReturnInt----\n";
	AddNumbersReturnInt(&a, &b);
	std::cout << "\n----AddNumbersReturnVoid----\n";
	AddNumbersReturnVoid(a, b, sum);
	std::cout << "\n----SwapValues----\n";
	SwapValues(&a, &b);

	std::cout << "\n----TriangleStack----\n";
	std::vector<TriangleStack> triangle;
	TriangleStack triangleb;
	TriangleStack triangleh;

	triangleb.SetBase(4);
	triangleb.SetHeight(13);
	triangle.push_back(triangleb);

	triangleh.SetBase(13);
	triangleh.SetHeight(15);
	triangle.push_back(triangleh);

	for (int i = 0; i < triangle.size() - 1; i++)
	{
		std::cout << "Triangleb's Area: " << triangleb.GetArea() << "\nTriangleh's Area: "<< triangleh.GetArea() << "\n";
	}

	std::cout << "----TriangleHeap----\n";
	std::vector<TriangleHeap> triangle2;
	TriangleHeap triangleq;
	TriangleHeap trianglew;

	triangleq.SetBase(4);
	triangleq.SetHeight(13);
	triangle2.push_back(triangleq);//misplaced memory problem (I believe)!!!

	trianglew.SetBase(13);
	trianglew.SetHeight(15);
	triangle2.push_back(trianglew);//misplaced memory problem (I believe)!!!

	for (int i = 0; i < triangle2.size() - 1; i++)
	{
		std::cout << "Triangleq's Area: " << triangleq.GetArea() << "\nTrianglew's Area: " << trianglew.GetArea() << "\n";
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
