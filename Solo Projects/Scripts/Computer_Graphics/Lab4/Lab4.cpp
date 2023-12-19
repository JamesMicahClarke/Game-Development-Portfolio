// Lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Rasterfunctions.h"
#include"RasterSurface.h"
#include <iostream>
#include <Windows.h>


int main()
{
	RS_Initialize("James", screenWidth, screenHeight);

	Matrix starWorld = SetIdentity(starWorld);
	Matrix cubeWorld = Translation(0, .5, 0);
	Matrix translation = Translation(0, 0, -6);
	Matrix rotation = XRotation(-18);
	//Matrix camera = FourMatrixXMatrix(Translation(0,0,0), XRotation())
	Matrix view = Inverse(FourMatrixXMatrix(translation, rotation));
	Matrix projection = Projection(90, .1, 100, .5);

	float rotVal = 0;
	const int starfill = 10000;
	const int objLoad = 1457;
	const int objIndicies = 2532;

	Vertex stars[starfill];
	Vertex* starPtr = stars;
	Vertex model[objLoad];

	for (int i = 0; i < starfill; i++)
	{
		stars[i].xyzw[0] = RandomPoint();
		stars[i].xyzw[1] = RandomPoint();
		stars[i].xyzw[2] = RandomPoint();
		stars[i].xyzw[3] = 1.0f;
	}

	while (RS_Update(screen, totalScreenArea))
	{
		for (int i = 0; i < totalScreenArea; i++)
		{
			screen[i] = 0x0;
			depth[i] = 1;
		}

		VertexShader = VS_World;
		S_world = starWorld;
		S_View = view;
		S_View = Translation(-1, 0, -1);
		S_Projection = projection;
		PixelShader = PS_White;

		Matrix rotateY;
		Matrix rotateX;
		//matrix mult a * b != b * a
		if (GetAsyncKeyState('D') & 0x1)
		{
			rotateY = YRotation(-.5);
			view = FourMatrixXMatrix(rotateY, view);
		}
		else if (GetAsyncKeyState('A') & 0x1)
		{
			rotateY = YRotation(.5);
			view = FourMatrixXMatrix(rotateY, view);
		}
		else if (GetAsyncKeyState('S') & 0x1)
		{
			rotateX = XRotation(-.5);
			view = FourMatrixXMatrix(rotateX, view);
		}
		else if (GetAsyncKeyState('W') & 0x1)
		{
			rotateX = XRotation(.5);
			view = FourMatrixXMatrix(rotateX, view);
		}

		unsigned int white = 0xffffffff;
		for (int i = 0; i < starfill; i++)
		{
			//copy each star, pass to vertex shader, ndc
			Vertex copy = starPtr[i];
			VS_World(copy);
			NDC(copy);
			DrawPixel(copy.xyzw[0], copy.xyzw[1], white, copy.U, copy.V, copy.xyzw[2]);
		}

		for (int i = 0; i < objLoad; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				model[i].xyzw[j] = StoneHenge_data[i].pos[j] * .1f;
				model[i].norms[j] = StoneHenge_data[i].nrm[j];
			}
			model[i].xyzw[3] = 1.0f;
			model[i].U = StoneHenge_data[i].uvw[0];
			model[i].V = StoneHenge_data[i].uvw[1];
		}
		PixelShader = PS_Image;

		for (int i = 0; i < objIndicies; i += 3)
		{
			BetterBruteTiangle(model[StoneHenge_indicies[i]], model[StoneHenge_indicies[i + 1]], model[StoneHenge_indicies[i + 2]]);
		}
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
