// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "RasterSurface.h"
#include "Rasterfunctions.h"
#include <iostream>
#include <chrono>

int main()
{

	////34 Lines in total (22 grid, 12 cube)
	RS_Initialize("James", screenWidth, screenHeight);

	const Vertex HGridLines[22] =
	{
		/*1*/{-.5, 0, -.5, 1}, {.5, 0, -.5, 1},
		/*2*/{-.5, 0, -.4, 1}, {.5, 0, -.4, 1},
		/*3*/{-.5, 0, -.3, 1}, {.5, 0, -.3, 1},
		/*4*/{-.5, 0, -.2, 1}, {.5, 0, -.2, 1},
		/*5*/{-.5, 0, -.1, 1}, {.5, 0, -.1, 1},
		/*6*/{  -.5, 0, 0, 1}, {  .5, 0, 0, 1},
		/*7*/{ -.5, 0, .1, 1}, { .5, 0, .1, 1},
		/*8*/{ -.5, 0, .2, 1}, { .5, 0, .2, 1},
		/*9*/{ -.5, 0, .3, 1}, { .5, 0, .3, 1},
		/*10*/{-.5, 0, .4, 1}, { .5, 0, .4, 1},
		/*11*/{-.5, 0, .5, 1}, { .5, 0, .5, 1}
	};
	const Vertex VGridLines[22] =
	{
		/*1*/{-.5, 0, -.5, 1}, {-.5, 0, .5, 1},
		/*2*/{-.4, 0, -.5, 1}, {-.4, 0, .5, 1},
		/*3*/{-.3, 0, -.5, 1}, {-.3, 0, .5, 1},
		/*4*/{-.2, 0, -.5, 1}, {-.2, 0, .5, 1},
		/*5*/{-.1, 0, -.5, 1}, {-.1, 0, .5, 1},
		/*6*/{	0, 0, -.5, 1}, {  0, 0, .5, 1},
		/*7*/{ .1, 0, -.5, 1}, { .1, 0, .5, 1},
		/*8*/{ .2, 0, -.5, 1}, { .2, 0, .5, 1},
		/*9*/{ .3, 0, -.5, 1}, { .3, 0, .5, 1},
		/*10*/{.4, 0, -.5, 1}, { .4, 0, .5, 1},
		/*11*/{.5, 0, -.5, 1}, { .5, 0, .5, 1}
	};
	/*Matrix matrix;
	for (int i = 0; i < 16; i++)
	{
		matrix.elements[i] = 0;
	}
	matrix.elements[0] = 1;
	matrix.elements[5] = .309;
	matrix.elements[6] = .951;
	matrix.elements[9] = -.951;
	matrix.elements[10] = .309;
	matrix.elements[12] = 7;
	matrix.elements[13] = -2.282;
	matrix.elements[14] = 9.153;
	matrix.elements[15] = 1;
	matrix = Inverse(matrix);
	int x = 0;
	for (int i = 0; i < 16; i++)
	{
		x++;
		if (x == 4)
		{
			std::cout << "\n";
			x = 0;
		}
		std::cout << matrix.elements[i] << " ";

	}*/

	const Vertex SquareLines[24] =
	{
		//bottom
		/*1*/{-.25, -.25, .25, 1,0x0, 0,1}, {.25, -.25, .25,1,0x0, 1,1},
		/*2*/{.25, -.25,.25, 1,0x0, 1,1 }, {.25, -.25, -.25, 1,0x0, 1,0},
		/*3*/{.25, -.25, -.25, 1,0x0, 0,1}, {-.25,-.25, -.25, 1,0x0, 1,1},
		/*4*/{-.25, -.25, -.25, 1, 0x0, 0,0}, {-.25,-.25, .25, 1,0x0},
		//top
		/*5*/{-.25, .25, .25, 1,0x0, 0,0}, {.25, .25, .25, 1, 0x0, 1,0},
		/*6*/{.25, .25, .25, 1,0x0, 1,0}, {.25, .25, -.25, 1,0x0, 1,1},
		/*7*/{.25, .25, -.25, 1,0x0,0,0}, {-.25, .25, -.25, 1,0x0, 1,0},
		/*8*/{-.25, .25, -.25, 1, 0x0, 0,1}, {-.25, .25, .25, 1,0x0},
		//sides
		/*9*/{-.25, -.25, .25, 1, 0x0, 1,1}, { -.25, .25, .25, 1,0x0, 1,0},
		/*10*/{.25, -.25, .25, 1, 0x0, 0,1}, {.25, .25, .25, 1, 0x0, 0,0},
		/*11*/{.25, -.25, -.25, 1, 0x0, 1,1}, {.25, .25, -.25, 1,0x0,1,0},
		/*12*/{-.25, -.25, -.25, 1, 0x0, 0, 1}, {-.25, .25, -.25, 1, 0x0,0,0},
	};


	Matrix gridWorld = SetIdentity(gridWorld);
	Matrix cubeWorld = Translation(0, .5, 0);

	Matrix translation = Translation(0, 0, -1);
	Matrix rotation = XRotation(-18);
	Matrix view = Inverse(FourMatrixXMatrix(translation, rotation));
	float rotVal = 0;
	Matrix projection = Projection(90, .1, 10, 1);

	while (RS_Update(screen, totalScreenArea))
	{
		DefaultColor(screen, 0x00000000);
		for (int i = 0; i < totalScreenArea; i++)
		{
			depth[i] = 1;

		}

		VertexShader = VS_World;
		PixelShader = PS_White;


		S_world = gridWorld;
		S_View = view;
		S_Projection = projection;

		//Horizontal Grid
		/*1*/DrawLine(HGridLines[0], HGridLines[1]);
		/*2*/DrawLine(HGridLines[2], HGridLines[3]);
		/*3*/DrawLine(HGridLines[4], HGridLines[5]);
		/*4*/DrawLine(HGridLines[6], HGridLines[7]);
		/*5*/DrawLine(HGridLines[8], HGridLines[9]);
		/*6*/DrawLine(HGridLines[10], HGridLines[11]);
		/*7*/DrawLine(HGridLines[12], HGridLines[13]);
		/*8*/DrawLine(HGridLines[14], HGridLines[15]);
		/*9*/DrawLine(HGridLines[16], HGridLines[17]);
		/*10*/DrawLine(HGridLines[18], HGridLines[19]);
		/*11*/DrawLine(HGridLines[20], HGridLines[21]);
		//Vertical Grid
		/*1*/DrawLine(VGridLines[0], VGridLines[1]);
		/*2*/DrawLine(VGridLines[2], VGridLines[3]);
		/*3*/DrawLine(VGridLines[4], VGridLines[5]);
		/*4*/DrawLine(VGridLines[6], VGridLines[7]);
		/*5*/DrawLine(VGridLines[8], VGridLines[9]);
		/*6*/DrawLine(VGridLines[10], VGridLines[11]);
		/*7*/DrawLine(VGridLines[12], VGridLines[13]);
		/*8*/DrawLine(VGridLines[14], VGridLines[15]);
		/*9*/DrawLine(VGridLines[16], VGridLines[17]);
		/*10*/DrawLine(VGridLines[18], VGridLines[19]);
		/*11*/DrawLine(VGridLines[20], VGridLines[21]);

		S_world = FourMatrixXMatrix(Translation(0, .25, 0), YRotation(rotVal += .9));//.9
		PixelShader = PS_Green;

		//cube lines
		//bottom
		/*1*/DrawLine(SquareLines[0], SquareLines[1]);
		/*2*/DrawLine(SquareLines[2], SquareLines[3]);
		/*3*/DrawLine(SquareLines[4], SquareLines[5]);
		/*4*/DrawLine(SquareLines[6], SquareLines[7]);
		//top
		/*5*/DrawLine(SquareLines[8], SquareLines[9]);
		/*6*/DrawLine(SquareLines[10], SquareLines[11]);
		/*7*/DrawLine(SquareLines[12], SquareLines[13]);
		/*8*/DrawLine(SquareLines[14], SquareLines[15]);
		//sides
		/*9*/DrawLine(SquareLines[16], SquareLines[17]);
		/*10*/DrawLine(SquareLines[18], SquareLines[19]);
		/*11*/DrawLine(SquareLines[20], SquareLines[21]);
		/*12*/DrawLine(SquareLines[22], SquareLines[23]);

		//triangles
		PixelShader = PS_Image;
		//PixelShader = PS_Purple;
		//bottom
		BetterBruteTiangle(SquareLines[0], SquareLines[1], SquareLines[3]);
		BetterBruteTiangle(SquareLines[0], SquareLines[6], SquareLines[3]);
		//top
		BetterBruteTiangle(SquareLines[8], SquareLines[9], SquareLines[11]);
		BetterBruteTiangle(SquareLines[8], SquareLines[14], SquareLines[11]);
		//back
		//PixelShader = PS_Red;
		BetterBruteTiangle(SquareLines[16], SquareLines[17], SquareLines[19]);
		BetterBruteTiangle(SquareLines[16], SquareLines[18], SquareLines[19]);
		//front
		//PixelShader = PS_Blue;
		BetterBruteTiangle(SquareLines[20], SquareLines[21], SquareLines[22]);
		BetterBruteTiangle(SquareLines[21], SquareLines[22], SquareLines[23]);
		//left
		//PixelShader = PS_Green;
		BetterBruteTiangle(SquareLines[8], SquareLines[5], SquareLines[0]);
		BetterBruteTiangle(SquareLines[8], SquareLines[13], SquareLines[5]);
		////right
		////PixelShader = PS_Yellow;
		BetterBruteTiangle(SquareLines[10], SquareLines[12], SquareLines[2]);
		BetterBruteTiangle(SquareLines[4], SquareLines[12], SquareLines[2]);
	}

	RS_Shutdown();
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
