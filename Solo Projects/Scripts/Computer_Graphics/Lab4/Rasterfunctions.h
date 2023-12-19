#pragma once
/*drawing routines
draw pixel
drawline
etc...*/
#include "Shaders.h"


float RandomPoint()
{
	return RAND_FLOAT(-1, 1) * 50;
}
//float RandomF(float min, float max)
//{
//	float ratio = rand() / (float)RAND_MAX;
//	return Lerp(min, max, ratio);
//}

void DefaultColor(unsigned int* buffer, unsigned int color)
{
	for (int y = 0; y < screenHeight; y++)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			int index = TwoToOne(x, y, screenWidth);
			buffer[index] = color;
		}
	}
}
void DrawPixel(int x, int y, unsigned int& color, float u, float v, float z = 0)
{
	if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
	{

		if (depth[TwoToOne(x, y, screenWidth)] > z)
		{
			depth[TwoToOne(x, y, screenWidth)] = z;
			int index = TwoToOne(x, y, screenWidth);
			//PixelShader(color, u, v);
			screen[index] = color;

		}
	}
}

void Parametric(int startX, int endX, int startY, int endY, float startZ, float endZ, float u, float v, unsigned int color)
{
	float xDistance = endX - startX;
	float yDistance = endY - startY;
	//float zDistance = endZ - startZ;
	float largest = std::max(abs(xDistance), abs(yDistance));
	//largest = std::max(largest, abs(zDistance));

	for (int i = 0; i < largest; i++)
	{
		float ratio = i / largest;
		unsigned int currX = Lerp(startX, endX, ratio);
		unsigned int currY = Lerp(startY, endY, ratio);
		float currZ = FLerp(startZ, endZ, ratio);
		if (PixelShader)
		{
			PixelShader(color, u, v);
		}
		color = ColorMod(red, blue);
		DrawPixel(currX, currY, color, u, v, currZ);
	}
}

void DrawLine(const Vertex& start, const Vertex& end)
{
	Vertex copyA = start;
	Vertex copyB = end;
	if (VertexShader != nullptr)
	{
		VertexShader(copyA);
		VertexShader(copyB);
	}

	NDC(copyA);
	NDC(copyB);
	/*if (PixelShader)
	{
		PixelShader(copyA.color);
	}*/
	Parametric(copyA.xyzw[0], copyB.xyzw[0], copyA.xyzw[1], copyB.xyzw[1], copyA.xyzw[2], copyB.xyzw[2], copyA.U, copyB.V, 0xffff0000);
}

void BetterBruteTiangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	Vertex copy1 = v1;
	Vertex copy2 = v2;
	Vertex copy3 = v3;

	if (VertexShader != nullptr)
	{
		VertexShader(copy1);
		VertexShader(copy2);
		VertexShader(copy3);
	}

	NDC(copy1);
	NDC(copy2);
	NDC(copy3);

	float startX = std::min(copy1.xyzw[0], copy2.xyzw[0]);
	startX = std::min(startX, copy3.xyzw[0]);

	float startY = std::min(copy1.xyzw[1], copy2.xyzw[1]);
	startY = std::min(startY, copy3.xyzw[1]);

	float endX = std::max(copy1.xyzw[0], copy2.xyzw[0]);
	endX = std::max(endX, copy3.xyzw[0]);

	float endY = std::max(copy1.xyzw[1], copy2.xyzw[1]);
	endY = std::max(endY, copy3.xyzw[1]);

	//startX = 0.0f;
	//endX = screenWidth - 1;
	//startY = 0.0f;
	//endY = screenHeight - 1;

	for (float y = startY; y <= endY; y++)
	{
		for (float x = startX; x <= endX; x++)
		{
			Vertex currentXY = SetVertex(x, y, 0, 0x00000000);
			Vertex lineAC[2];
			lineAC[0] = copy1;
			lineAC[1] = copy3;

			Vertex lineBA[2];
			lineBA[0] = copy2;
			lineBA[1] = copy1;

			Vertex lineCB[2];
			lineCB[0] = copy3;
			lineCB[1] = copy2;

			Bary bya = Barycentric(currentXY, copy1, copy2, copy3, lineAC, lineBA, lineCB);
			if (bya.values[1] >= 0 && bya.values[1] <= 1 && bya.values[2] >= 0 && bya.values[2] <= 1 && bya.values[0] >= 0 && bya.values[0] <= 1)
			{
				float z = BLerp(bya, copy1.xyzw[2], copy2.xyzw[2], copy3.xyzw[2]);
				float textU = BLerp(bya, copy1.U, copy2.U, copy3.U);
				float textV = BLerp(bya, copy1.V, copy2.V, copy3.V);
				unsigned int color = BaryCLerp(bya,copy1.color, copy2.color, copy3.color);
				//unsigned int color = copy1.color;
				if (PixelShader)
				{
					PixelShader(color, textU, textV);
				}
				DrawPixel(x, y, color, textU, textV, z);
			}
		}
	}
}
//float VerticalLine(float x1, float y1, float x2, float y2)
//{
//	float X = x2 - x1; //parallel vector
//	float Y = y2 - y1; //parallel vector
//
//	float A = y1 - y2;//perpendicular vector
//	float B = x2 - x1; //perpendicular vector
//	float C = -(y1 - y2) * x1 - (x2 - x1) * y1;
//
//	float result = LineEquation(X, Y, A, B, C);
//	return result;
//}
