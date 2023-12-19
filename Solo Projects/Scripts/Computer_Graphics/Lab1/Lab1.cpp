// Lab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//q

#include "RasterSurface.h"
#include "fire_01c.h"
#include "tiles_12.h"
#include "XTime.h"
#include <iostream>
#include <random>

unsigned int screenWidth = 500;
unsigned int screenHeight = 500;

unsigned int totalScreenArea = screenWidth * screenHeight;
const char student[] = { "James" };

unsigned int screenAr[250000] = { 0, };
unsigned int* screenPtr = screenAr;

const unsigned int* colorBuf = tiles_12_pixels;

int spriteLeft = 288;
int spriteRight = 319;
int spriteTop = 128;
int spriteBottom = 158;

//int spriteLeft = 282;
//int spriteRight = 324;
//int spriteTop = 122;
//int spriteBottom = 163;
int spriteHeight = spriteBottom - spriteTop;
int spriteWidth = spriteRight - spriteLeft;
int spriteArea = spriteHeight * spriteWidth;

struct Fire
{
	int T, L, B, R, Height, Width;
};

Fire animation[64];
Fire* anime = animation;

//int fireLeft = 0;
//int fireRight = 128;
//int fireTop = 0;
//int fireBottom = 128;
//int fireHeight = fireBottom - fireTop;
//int fireWidth = fireRight - fireLeft;
//int fireArea = fireHeight * fireWidth;

int rArrayX[10];
int rArrayY[10];


Fire* SetFireAnimation(Fire* animation)
{
	int column = 0;
	int row = 0;
	int SpWidth = 128;
	int SpHeight = 128;

	for (int i = 0; i < 64; i++)
	{
		animation[i].Width = SpWidth;
		animation[i].Height = SpHeight;
		if (column >= 8)
		{
			column = 0;
			row++;
		}
		animation[i].T = SpHeight * row;
		animation[i].L = SpWidth * column;
		animation[i].B = animation[i].T + SpHeight;
		animation[i].R = animation[i].L + SpWidth;
		column++;
	}
	return animation;
}
void randomAr()
{
	for (int i = 0; i < 10; i++)
	{
		rArrayX[i] = rand() % screenWidth;
		rArrayY[i] = rand() % screenHeight;

	}
}
//divide by float for ratio
unsigned int Lerp(unsigned int one, unsigned int two, float ratio)
{
	unsigned int lerp = ((int)two - (int)one) * ratio + one; //R = color/255 overwirting color is the alpha to use
	return lerp;
}

int TwoToOne(unsigned int x, unsigned int y, unsigned int width)
{
	int convert = y * width + x;
	return convert;
}
unsigned int ABlend(unsigned int color1, unsigned int color2)
{

	unsigned int alpha = 0xff000000;
	unsigned int blue = 0x000000ff;
	unsigned int red = 0x00ff0000;
	unsigned int green = 0x0000ff00;
	//color = blue;

	unsigned int newAlpha1 = (color1 & alpha) >> 24;
	unsigned int newRed1 = (color1 & red) >> 16;
	unsigned int newGreen1 = (color1 & green) >> 8;
	unsigned int newBlue1 = (color1 & blue);
	
	unsigned int newAlpha2 = (color2 & alpha) >> 24;
	unsigned int newRed2 = (color2 & red) >> 16;
	unsigned int newGreen2 = (color2 & green) >> 8;
	unsigned int newBlue2 = (color2 & blue);


	float ratio = newAlpha2 / 255.0f;

	/*if (ratio > 0.0f && ratio < 1.0f)
		int nDebiug = 0;*/

	unsigned int nextAlpha = Lerp(newAlpha1, newAlpha2, ratio);
	unsigned int nextRed = Lerp(newRed1, newRed2, ratio);
	unsigned int nextGreen = Lerp(newGreen1, newGreen2, ratio);
	unsigned int nextBlue = Lerp(newBlue1, newBlue2, ratio);

	//color1 = (color1 & nextAlpha1) << 4  | (color1 & nextRed1) << 24 | (color1 & nextGreen1) << 16 | (color1 & nextBlue1);
	color2 = (nextAlpha << 24) | ( nextRed << 16)| ( nextGreen << 8)| (nextBlue);

	/*if (color1 == 0)
	{
		return color2;
	}*/
	return color2;
}
void Draw(int x, int y, unsigned int color)
{
	if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
	{
		int index = TwoToOne(x, y, screenWidth);
		if (((color & 0xff000000) >> 24) < 255)
		{
			color = ABlend(screenAr[index], color);
			//screenAr[index] = Lerp(screenAr[index], color, 0xff000000 / 255.0f);

		}
		screenAr[index] = color;
	}
}

//BGRA->ARGB
unsigned int ARGB(unsigned int color)
{
	unsigned int result = 0;
	unsigned int red = 0x0000ff00;
	unsigned int green = 0x00ff0000;
	unsigned int blue = 0xff000000;
	unsigned int alpha = 0x000000ff;

	result = ((color & alpha) << 24u) | ((color & red) << 8u) | ((color & green) >> 8u) | ((color & blue) >> 24u);

	return result;
}

void Blit(int _x, int _y, const unsigned int* image, unsigned int iWidth, unsigned int spWidth, unsigned int spHeight, int top, int left)//screenHeight
{
	for (int y = 0; y < spHeight; y++)
	{
		for (int x = 0; x < spWidth; x++)
		{
			int imgeIndex = TwoToOne(left + x, top + y, iWidth);
			unsigned int color = image[imgeIndex];
			color = ARGB(color);
			Draw(_x + x, _y + y, color);
		}
	}
}
void RandomTreePrint()
{
	int treeLeft = 318;
	int treeRight = 384;
	int treeTop = 14;
	int treeBottom = 94;
	int treeHeight = treeBottom - treeTop;
	int treeWidth = treeRight - treeLeft;
	int treeArea = treeHeight * treeWidth;
	for (int i = 0; i < 10; i++)
	{
		Blit(rArrayX[i], rArrayY[i], tiles_12_pixels, tiles_12_width, treeWidth, treeHeight, treeTop, treeLeft);
	}
}
void BackgroundPrint()
{
	for (int x = 0; x < screenWidth / spriteWidth + 1; x++) // add 1 to fill the border 
	{
		for (int y = 0; y < screenHeight / spriteHeight + 1; y++)
		{
			Blit(x * spriteWidth, y * spriteHeight, tiles_12_pixels, tiles_12_width, spriteWidth, spriteHeight, spriteTop, spriteLeft);

		}
	}
}
void DefaultColor(unsigned int* buffer, unsigned int color)
{
	for (int i = 0; i < totalScreenArea; i++)
	{
		buffer[i] & 0x00000000;
		buffer[i] = color;
	}
}

//void AnimationHelper(float& elapse, int& index, XTime& timer)
//{
//	timer.Restart();
//	timer.Signal();
//
//	elapse += timer.Delta();
//	if (elapse > 1.0f / 30.0f)
//	{
//		index++;
//		elapse = 0;
//		if (index >= 64)
//		{
//			index = 0;
//		}
//	}
//
//}

void FireAnimation(float& elapsed, int& index, XTime& timer)
{
	anime = SetFireAnimation(animation);
	timer.Signal();

	elapsed += timer.Delta();
	if (elapsed > 1.0f / 30.0f)
	{
		index++;
		elapsed = 0;
		if (index >= 64)
		{
			index = 0;
		}
	}
	Blit(250, 250, fire_01c_pixels, fire_01c_width, anime[index].Width, anime[index].Height, anime[index].T, anime[index].L);
	timer.Restart();
}

int main()
{
	//stays here. Called once. Will create and open a WIN32 WINDOW.
	RS_Initialize(student, screenWidth, screenHeight);
	float elapsed = 0;
	int index = 0;
	XTime timer;

	srand(time(NULL));
	randomAr();
	/*Called at least once per frame
		will continue to return true until the WIN32 Window closes.
		Once the window is closed, RS_Update will return false.*/
	while (RS_Update(screenAr, totalScreenArea))
	{
		BackgroundPrint();
		RandomTreePrint();
		FireAnimation(elapsed, index, timer);
	}

	//stays here. Called once.
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
