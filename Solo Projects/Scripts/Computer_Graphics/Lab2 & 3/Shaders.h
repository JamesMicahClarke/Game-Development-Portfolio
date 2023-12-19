#pragma once
//emulate the .ppt slides(day3)
#include "Mymath.h"

void (*VertexShader)(Vertex&) = 0;
void (*PixelShader)(unsigned int&, float& u, float& v) = 0;

Matrix S_world;
Matrix S_View;
Matrix S_Projection;

void VS_World(Vertex& multiply)
{
	multiply = FourVectorXMatrix(multiply, S_world);
	multiply = FourVectorXMatrix(multiply, S_View);
	multiply = FourVectorXMatrix(multiply, S_Projection);
	multiply = PerspectDiv(multiply);
}


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
void PS_White(unsigned int& color, float& u, float& v)
{
	color = 0xFFFFFFFF;
}
void PS_Red(unsigned int& color, float& u, float& v)
{
	color = 0x00ff0000;
}
void PS_Green(unsigned int& color, float& u, float& v)
{
	color = 0x0000ff00;
}
void PS_Yellow(unsigned int& color, float& u, float& v)
{
	color = 0x00ffff00;
}
void PS_Blue(unsigned int& color, float& u, float& v)
{
	color = 0x000000ff;
}
void PS_Purple(unsigned int& color, float& u, float& v)
{
	color = 0xffff00ff;
}
void PS_Image(unsigned int& color, float& u, float& v)
{
	u *=  treeolife_width;
	v *= treeolife_height;

	unsigned int index = TwoToOne(u, v, treeolife_width);
	color = treeolife_pixels[index];
	color = ARGB(color);
}