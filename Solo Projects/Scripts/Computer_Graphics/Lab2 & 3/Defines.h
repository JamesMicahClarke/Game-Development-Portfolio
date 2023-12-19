#pragma once
// globals
//#defines / macros
//struct
#include <iostream>
#include "treeolife.h"
const unsigned int screenWidth = 800;
const unsigned int screenHeight = 800;
const unsigned int totalScreenArea = screenWidth * screenHeight;
unsigned int screen[totalScreenArea] = { 0, };
//unsigned int screen[screenWidth][screenHeight];

float depth[totalScreenArea];

// 3.14159 for more accuracy
float pi = 3.14159;

//unsigned int* screenPtr = screen;
//float gridXBottom = 
//float worldMatrix[16] = { 1,0,0,0,
//						  0,1,0,0,
//						  0,0,1,0,
//						  0,0,0,1 };
/*  0  1   2  3
	4  5   6  7
	8  9  10 11
	12 13 14 15*/

	//Matrix world;  //{1, 0, 0, 0,
	//				  0,1,0,0,
	//				  0,0,1,0,
	//				  0,0,0,1};

struct Pixel
{
	unsigned int pixel;
};

struct Vertex
{
	float xyzw[4];
	unsigned int color;
	float U;
	float V;
};

struct Matrix
{
	union
	{
		float elements[16];

		struct
		{
			float m[4][4];
		};
	};
	//Vertex vertex[4] = 
	//{
	//	//Identity
	//	{1,0,0,0},
	//	{0,1,0,0},
	//	{0,0,1,0},
	//	{0,0,0,1}
	//};					
						/*  0  1   2  3
							4  5   6  7
							8  9  10 11
							12 13 14 15*/
};

struct Bary
{
	//0-Alpha,1-Beta,2-Gamma
	float values[3];
};

Vertex SetVertex(float X, float Y, float Z, unsigned int color)
{
	Vertex vertex;
	vertex.xyzw[0] = X;
	vertex.xyzw[1] = Y;
	vertex.xyzw[2] = Z;
	vertex.xyzw[3] = 1;
	vertex.color = color;
	return vertex;
}