#pragma once
//emulate the .ppt slides(day3)
#include "Mymath.h"
#include "StoneHenge_Texture.h"

void (*VertexShader)(Vertex&) = 0;
void (*PixelShader)(unsigned int&, float& u, float& v) = 0;

Matrix S_world;
Matrix S_View;
Matrix S_Projection;

void VS_World(Vertex& multiply)
{
	multiply = FourVectorXMatrix(multiply, S_world);
	Vertex surfaceXyz = multiply;
	multiply = FourVectorXMatrix(multiply, S_View);
	multiply = FourVectorXMatrix(multiply, S_Projection);
	multiply = PerspectDiv(multiply);
	Vertex dVert;
	dVert.norms[0] = 0.577;
	dVert.norms[1] = 0.577;
	dVert.norms[2] = -0.577;

	float lightR = VDotProduct(multiply, dVert);
	lightR = Saturate(0, 1, lightR);
	unsigned int dLight = CLerp(0x0, 0xFFC0C0F0, lightR);
	//multiply.color = dLight;

	Vertex lightP;
	lightP.xyzw[0] = -1 - surfaceXyz.xyzw[0];
	lightP.xyzw[1] = .5f - surfaceXyz.xyzw[1];
	lightP.xyzw[2] = 1 - surfaceXyz.xyzw[2];

	Vertex directionP = Vec3Normalize(lightP);
	float ratioP = VDotProduct(multiply, directionP);
	ratioP = Saturate(0, 1, ratioP);
	float att = 1.0f - Saturate(0, 1, VectorLegnth(lightP)/ lightRadius);
	unsigned int pLight = CLerp(0x0, 0xFFFFFF00, ratioP/att);
	multiply.color = ColorCombine(dLight, pLight);
	multiply.color = pLight;
}

unsigned int ARGB(unsigned int color)
{
	unsigned int result = 0;

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
	u *= StoneHenge_width;
	v *= StoneHenge_height;

	unsigned int index = TwoToOne(u, v, StoneHenge_width);
	unsigned int texture = StoneHenge_pixels[index];
	texture = ARGB(texture);
	color = ColorMod(texture, color);
}