// LevelParse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "h2bParser.h"
using namespace std;

void MatrixRead(char(&read)[2000], char delimiter[], ifstream& file, int readingSize = 0);

int main()
{
	char str[2000];
	// 0- '.' 1- ',' 2- '/n' 3-space  4- '(' 5- ')' 6- '<' 7- '>'
	char delim[8] = { '.', ',' ,'/n', ' ', '(', ')', '<', '>'};
	ifstream inFile;
	inFile.open("C:/Users/James Clarke/Desktop/Programming/PP4/Week_1_Handout/Portfolio Project/GameLevel.txt", ios::in);

	if (inFile.is_open())
	{
		int i = 0;
		int j = 0;
		while (!inFile.eof())
		{
			inFile.getline(str, 100);
			if (strcmp("MESH", str) == 0)
			{
				cout << "----------MESH------------" << endl;
				
				MatrixRead(str, delim, inFile);

			}
			if (strcmp("CAMERA", str) == 0)
			{
				cout << "----------CAMERA------------" << endl;
				
				MatrixRead(str, delim, inFile);
				
			}
			if (strcmp("LIGHT", str) == 0)
			{
				cout << "----------LIGHT------------" << endl;
				MatrixRead(str, delim, inFile);
			}
			i++;
			
		}
		inFile.close();
	}

}

void MatrixRead(char(&read)[2000], char delimiter[], ifstream& file, int readingSize)
{
	file.getline(read, 100, delimiter[6]);
	file.read(read, readingSize);
	cout << read;

	file.getline(read, 100, delimiter[4]);

	file.getline(read, 100, delimiter[1]);
	float matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[5]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << endl;
	//cout << matrix << endl; //4th

	file.getline(read, 100, delimiter[4]);

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[5]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << endl;
	//cout << matrix << endl; //8th

	file.getline(read, 100, delimiter[4]);

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[5]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << endl;
	//cout << matrix << endl;//12th

	file.getline(read, 100, delimiter[4]);

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[1]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << " ";
	//cout << matrix << " ";

	file.getline(read, 100, delimiter[5]);
	matrix = atof(read);
	file.read(read, readingSize);
	cout << read << endl;
	//cout << matrix<< endl;//16th
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
