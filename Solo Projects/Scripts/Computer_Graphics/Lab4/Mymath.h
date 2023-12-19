#pragma once
/*math related functions
* vertex mul matrix
* matrix mul matrix
* convert 2D - 1D
* matrix identidy
* etc...*/
#include "Defines.h"
#include <math.h>



int TwoToOne(int x, int y, int width)
{
	int convert = y * width + x;
	return convert;
}

unsigned int CLerp(unsigned int color1, unsigned int color2, float ratio)
{
	unsigned int red1 = (color1 & 0x00ff0000) >> 16;
	unsigned int green1 = (color1 & 0x0000ff00) >> 8;
	unsigned int blue1 = (color1 & 0x000000ff);
	unsigned int alpha1 = (color1 & 0xff000000) >> 24;

	unsigned int red2 = (color2 & 0x00ff0000) >> 16;
	unsigned int green2 = (color2 & 0x0000ff00) >> 8;
	unsigned int blue2 = (color2 & 0x000000ff);
	unsigned int alpha2 = (color2 & 0xff000000) >> 24;

	int a = ((int)alpha2 - (int)alpha1) * ratio + alpha1;
	int r = ((int)red2 - (int)red1) * ratio + red1;
	int g = ((int)green2 - (int)green1) * ratio + green1;
	int b = ((int)blue2 - (int)blue1) * ratio + blue1;

	return (a << 24) | (r << 16) | (g << 8) | b;
}
unsigned int Lerp(unsigned int one, unsigned int two, float ratio)
{
	unsigned int lerp = ((int)two - (int)one) * ratio + (int)one;
	return lerp;
}
float FLerp(float one, float two, float ratio)
{
	float lerp = (two - one) * ratio + one;
	return lerp;
}
float BLerp(Bary bya, float a, float b, float c)
{
	return a * bya.values[0] + b * bya.values[1] + c * bya.values[2];
}
unsigned int BaryCLerp(Bary bya, unsigned int color1, unsigned int color2, unsigned int color3)
{
	unsigned int red1 = (color1 & 0x00ff0000) >> 16;
	unsigned int green1 = (color1 & 0x0000ff00) >> 8;
	unsigned int blue1 = (color1 & 0x000000ff);
	unsigned int alpha1 = (color1 & 0xff000000) >> 24;

	unsigned int red2 = (color2 & 0x00ff0000) >> 16;
	unsigned int green2 = (color2 & 0x0000ff00) >> 8;
	unsigned int blue2 = (color2 & 0x000000ff);
	unsigned int alpha2 = (color2 & 0xff000000) >> 24;

	unsigned int red3 = (color3 & 0x00ff0000) >> 16;
	unsigned int green3 = (color3 & 0x0000ff00) >> 8;
	unsigned int blue3 = (color3 & 0x000000ff);
	unsigned int alpha3 = (color3 & 0xff000000) >> 24;



	float finalAlpha = BLerp(bya, alpha1, alpha2, alpha3);
	float finalRed = BLerp(bya, red1, red2, red3);
	float finalGreen = BLerp(bya, green1, green2, green3);
	float finalBlue = BLerp(bya, blue1, blue2, blue3);

	return ((unsigned int)finalAlpha << 24) | ((unsigned int)finalRed << 16) | ((unsigned int)finalGreen << 8) | (unsigned int)finalBlue;

}

float Radians(float degree)
{
	//float pi = 3.15;
	return degree * (pi / 180);
}

float Cotangent(float angle)
{
	return 1.0f / tan(Radians(angle));
}

float LineEquation(Vertex vertex, Vertex line[])
{
	return (line[0].xyzw[1] - line[1].xyzw[1]) * vertex.xyzw[0] + (line[1].xyzw[0] - line[0].xyzw[0]) * vertex.xyzw[1] + (line[0].xyzw[0] * line[1].xyzw[1]) - (line[0].xyzw[1] * line[1].xyzw[0]);
}


float VectorLegnth(Vertex& vectorA)
{
	return sqrt((vectorA.xyzw[0] * vectorA.xyzw[1]) + (vectorA.xyzw[1] * vectorA.xyzw[0]) + (vectorA.xyzw[2] * vectorA.xyzw[1]));
}

Vertex Vec3Normalize(Vertex& vectorA)
{
	Vertex norm;
	float magnitude = VectorLegnth(vectorA);
	for (int i = 0; i < 3; i++)
	{
		norm.norms[i] = vectorA.xyzw[i] / magnitude;
		//vectorB.norms[i] = magnitude;
	}
	return norm;
}

Vertex VCrossProduct(Vertex& vectorA, Vertex& vectorB)
{
	Vertex productResult;
	productResult.norms[0] = (vectorA.norms[1] * vectorB.norms[2]) -
		(vectorA.norms[2] * vectorB.norms[1]);

	productResult.norms[1] = (vectorA.norms[2] * vectorB.norms[0]) -
		(vectorA.norms[0] * vectorB.norms[2]);

	productResult.norms[2] = (vectorA.norms[0] * vectorB.norms[1]) -
		(vectorA.norms[1] * vectorB.norms[0]);

	return productResult;
}

float VDotProduct(Vertex& vectorA, Vertex& vectorB)
{
	float a = vectorA.norms[0] * vectorB.norms[0];
	float b = vectorA.norms[1] * vectorB.norms[1];
	float c = vectorA.norms[2] * vectorB.norms[2];

	return a + b + c;
}
float Saturate(float min, float max, float bigNum)
{
	if (bigNum < min)
	{
		bigNum = min;
	}
	if (bigNum > max)
	{
		bigNum = max;
	}
	return bigNum;
}


unsigned int ColorMod(unsigned int color1, unsigned int color2)
{
	unsigned int red1 = (color1 & 0x00ff0000) >> 16;
	unsigned int green1 = (color1 & 0x0000ff00) >> 8;
	unsigned int blue1 = (color1 & 0x000000ff);
	unsigned int alpha1 = (color1 & 0xff000000) >> 24;

	unsigned int red2 = (color2 & 0x00ff0000) >> 16;
	unsigned int green2 = (color2 & 0x0000ff00) >> 8;
	unsigned int blue2 = (color2 & 0x000000ff);
	unsigned int alpha2 = (color2 & 0xff000000) >> 24;

	//make floats
	float r1 = red1 / 255.0f;
	float r2 = red2 / 255.0f;

	float g1 = green1 / 255.0f;
	float g2 = green2 / 255.0f;

	float b1 = blue1 / 255.0f;
	float b2 = blue2 / 255.0f;

	float a1 = alpha1 / 255.0f;
	float a2 = alpha2 / 255.0f;


	float Newred = Saturate(0, 1, (r1 * r2));
	float Newgreen = Saturate(0, 1, (g1 * g2));
	float Newblue = Saturate(0, 1, (b1 * b2));
	float Newalpha = Saturate(0, 1, (a1 * a2));

	Newred *= 255;
	Newgreen *= 255;
	Newblue *= 255;
	Newalpha *= 255;

	unsigned int colorResult = ((unsigned int)Newred << 16) | ((unsigned int)Newgreen << 8) | (unsigned int)Newblue | ((unsigned int)Newalpha << 24);

	return colorResult;
}

unsigned int ColorCombine(unsigned int color1, unsigned int color2)
{
	unsigned int alpha1 = (color1 & 0xff000000) >> 24;
	unsigned int red1 = (color1 & 0x00ff0000) >> 16;
	unsigned int green1 = (color1 & 0x0000ff00) >> 8;
	unsigned int blue1 = (color1 & 0x000000ff);

	unsigned int alpha2 = (color2 & 0xff000000) >> 24;
	unsigned int red2 = (color2 & 0x00ff0000) >> 16;
	unsigned int green2 = (color2 & 0x0000ff00) >> 8;
	unsigned int blue2 = (color2 & 0x000000ff);

	float r1 = red1 / 255.0f;
	float r2 = red2 / 255.0f;

	float g1 = green1 / 255.0f;
	float g2 = green2 / 255.0f;

	float b1 = blue1 / 255.0f;
	float b2 = blue2 / 255.0f;

	float a1 = alpha1 / 255.0f;
	float a2 = alpha2 / 255.0f;

	float red = Saturate(0, 1, red1 + red2) * 255.0f;
	float green = Saturate(0, 1, green1 + green2) * 255.0f;
	float blue = Saturate(0, 1, blue1 + blue2) * 255.0f;
	float alpha = Saturate(0, 1, alpha1 + alpha2) * 255.0f;

	//red *= 255.0f;
	/*green *= 255.0f;
	blue *= 255.0f;
	alpha *= 255.0f;*/

	unsigned int colorResult = ((unsigned int)alpha << 24) | ((unsigned int)red << 16) | ((unsigned int)green << 8) | (unsigned int)blue;

	return colorResult;
}
Bary Barycentric(Vertex P, Vertex A, Vertex B, Vertex C, Vertex lineAC[], Vertex lineBA[], Vertex lineCB[])
{
	Bary coords;
	float alpha = LineEquation(A, lineCB);
	float beta = LineEquation(B, lineAC);
	float gamma = LineEquation(C, lineBA);
	float b = LineEquation(P, lineAC);
	float c = LineEquation(P, lineBA);
	float a = LineEquation(P, lineCB);
	coords.values[0] = a / alpha;
	coords.values[1] = b / beta;
	coords.values[2] = c / gamma;
	return coords;
}

float DerterminantX3(Matrix matrix)
{
	float a = matrix.elements[0];
	Matrix matrix1, matrix2, matrix3;

	matrix1.elements[0] = matrix.elements[4];
	matrix1.elements[1] = matrix.elements[5];
	matrix1.elements[2] = matrix.elements[7];
	matrix1.elements[3] = matrix.elements[8];
	float deterA = a * ((matrix1.elements[0] * matrix1.elements[3]) - (matrix1.elements[2] * matrix1.elements[1]));

	float b = matrix.elements[1];
	matrix2.elements[0] = matrix.elements[3];
	matrix2.elements[1] = matrix.elements[5];
	matrix2.elements[2] = matrix.elements[6];
	matrix2.elements[3] = matrix.elements[8];
	float deterB = b * ((matrix2.elements[0] * matrix2.elements[3]) - (matrix2.elements[2] * matrix2.elements[1]));

	float c = matrix.elements[2];
	matrix2.elements[0] = matrix.elements[3];
	matrix2.elements[1] = matrix.elements[4];
	matrix2.elements[2] = matrix.elements[6];
	matrix2.elements[3] = matrix.elements[7];
	float deterC = c * ((matrix2.elements[0] * matrix2.elements[3]) - (matrix2.elements[2] * matrix2.elements[1]));

	return deterA - deterB + deterC;
}

float DeterminantX4(Matrix matrix)
{
	Matrix matrix1, matrix2, matrix3, matrix4;
	float values[4];

	values[0] = matrix.elements[0];
	matrix1.elements[0] = matrix.elements[5];
	matrix1.elements[1] = matrix.elements[6];
	matrix1.elements[2] = matrix.elements[7];
	matrix1.elements[3] = matrix.elements[9];
	matrix1.elements[4] = matrix.elements[10];
	matrix1.elements[5] = matrix.elements[11];
	matrix1.elements[6] = matrix.elements[13];
	matrix1.elements[7] = matrix.elements[14];
	matrix1.elements[8] = matrix.elements[15];

	values[1] = matrix.elements[1];
	matrix2.elements[0] = matrix.elements[4];
	matrix2.elements[1] = matrix.elements[6];
	matrix2.elements[2] = matrix.elements[7];
	matrix2.elements[3] = matrix.elements[8];
	matrix2.elements[4] = matrix.elements[10];
	matrix2.elements[5] = matrix.elements[11];
	matrix2.elements[6] = matrix.elements[13];
	matrix2.elements[7] = matrix.elements[14];
	matrix2.elements[8] = matrix.elements[15];

	values[2] = matrix.elements[2];
	matrix3.elements[0] = matrix.elements[4];
	matrix3.elements[1] = matrix.elements[5];
	matrix3.elements[2] = matrix.elements[7];
	matrix3.elements[3] = matrix.elements[8];
	matrix3.elements[4] = matrix.elements[9];
	matrix3.elements[5] = matrix.elements[11];
	matrix3.elements[6] = matrix.elements[12];
	matrix3.elements[7] = matrix.elements[13];
	matrix3.elements[8] = matrix.elements[15];

	values[3] = matrix.elements[3];
	matrix4.elements[0] = matrix.elements[4];
	matrix4.elements[1] = matrix.elements[5];
	matrix4.elements[2] = matrix.elements[6];
	matrix4.elements[3] = matrix.elements[8];
	matrix4.elements[4] = matrix.elements[9];
	matrix4.elements[5] = matrix.elements[10];
	matrix4.elements[6] = matrix.elements[12];
	matrix4.elements[7] = matrix.elements[13];
	matrix4.elements[8] = matrix.elements[14];

	values[0] *= DerterminantX3(matrix1);
	values[1] *= DerterminantX3(matrix2);
	values[2] *= DerterminantX3(matrix3);
	values[3] *= DerterminantX3(matrix4);

	return values[0] + values[1] + values[2] + values[3];
}

Matrix Cofactor(Matrix matrix)
{
	Matrix cofactor;
	cofactor.elements[0] = (matrix.elements[5] * matrix.elements[10] * matrix.elements[15]) + (matrix.elements[6] * matrix.elements[11] * matrix.elements[13]) + (matrix.elements[7] * matrix.elements[9] * matrix.elements[14]) - (matrix.elements[7] * matrix.elements[10] * matrix.elements[13]) - (matrix.elements[6] * matrix.elements[9] * matrix.elements[15]) - (matrix.elements[5] * matrix.elements[11] * matrix.elements[14]);
	cofactor.elements[1] = (-1 * (matrix.elements[1] * matrix.elements[10] * matrix.elements[15])) - (matrix.elements[2] * matrix.elements[11] * matrix.elements[13]) - (matrix.elements[3] * matrix.elements[9] * matrix.elements[14]) + (matrix.elements[3] * matrix.elements[10] * matrix.elements[13]) + (matrix.elements[2] * matrix.elements[9] * matrix.elements[15]) + (matrix.elements[1] * matrix.elements[11] * matrix.elements[14]);
	cofactor.elements[2] = (matrix.elements[1] * matrix.elements[6] * matrix.elements[15]) + (matrix.elements[2] * matrix.elements[7] * matrix.elements[13]) + (matrix.elements[3] * matrix.elements[5] * matrix.elements[14]) - (matrix.elements[3] * matrix.elements[6] * matrix.elements[13]) - (matrix.elements[2] * matrix.elements[5] * matrix.elements[15]) - (matrix.elements[1] * matrix.elements[7] * matrix.elements[14]);
	cofactor.elements[3] = (-1 * (matrix.elements[1] * matrix.elements[6] * matrix.elements[11])) - (matrix.elements[2] * matrix.elements[7] * matrix.elements[9]) - (matrix.elements[3] * matrix.elements[5] * matrix.elements[10]) + (matrix.elements[3] * matrix.elements[6] * matrix.elements[9]) + (matrix.elements[2] * matrix.elements[5] * matrix.elements[11]) + (matrix.elements[1] * matrix.elements[7] * matrix.elements[10]);

	cofactor.elements[4] = (-1 * (matrix.elements[4] * matrix.elements[10] * matrix.elements[15])) - (matrix.elements[6] * matrix.elements[11] * matrix.elements[12]) - (matrix.elements[7] * matrix.elements[8] * matrix.elements[14]) + (matrix.elements[7] * matrix.elements[10] * matrix.elements[12]) + (matrix.elements[6] * matrix.elements[8] * matrix.elements[15]) + (matrix.elements[4] * matrix.elements[11] * matrix.elements[14]);
	cofactor.elements[5] = (matrix.elements[0] * matrix.elements[10] * matrix.elements[15]) + (matrix.elements[2] * matrix.elements[11] * matrix.elements[12]) + (matrix.elements[3] * matrix.elements[8] * matrix.elements[14]) - (matrix.elements[3] * matrix.elements[10] * matrix.elements[12]) - (matrix.elements[2] * matrix.elements[8] * matrix.elements[15]) - (matrix.elements[0] * matrix.elements[11] * matrix.elements[14]);
	cofactor.elements[6] = (-1 * (matrix.elements[0] * matrix.elements[6] * matrix.elements[15])) - (matrix.elements[2] * matrix.elements[7] * matrix.elements[12]) - (matrix.elements[3] * matrix.elements[4] * matrix.elements[14]) + (matrix.elements[3] * matrix.elements[6] * matrix.elements[12]) + (matrix.elements[2] * matrix.elements[4] * matrix.elements[15]) + (matrix.elements[0] * matrix.elements[7] * matrix.elements[14]);
	cofactor.elements[7] = (matrix.elements[0] * matrix.elements[6] * matrix.elements[11]) + (matrix.elements[2] * matrix.elements[7] * matrix.elements[8]) + (matrix.elements[3] * matrix.elements[4] * matrix.elements[10]) - (matrix.elements[3] * matrix.elements[6] * matrix.elements[8]) - (matrix.elements[2] * matrix.elements[4] * matrix.elements[11]) - (matrix.elements[0] * matrix.elements[7] * matrix.elements[10]);

	cofactor.elements[8] = (matrix.elements[4] * matrix.elements[9] * matrix.elements[15]) + (matrix.elements[5] * matrix.elements[11] * matrix.elements[12]) + (matrix.elements[7] * matrix.elements[8] * matrix.elements[13]) - (matrix.elements[7] * matrix.elements[9] * matrix.elements[12]) - (matrix.elements[5] * matrix.elements[8] * matrix.elements[15]) - (matrix.elements[4] * matrix.elements[11] * matrix.elements[13]);
	cofactor.elements[9] = (-1 * (matrix.elements[0] * matrix.elements[9] * matrix.elements[15])) - (matrix.elements[1] * matrix.elements[11] * matrix.elements[12]) - (matrix.elements[3] * matrix.elements[8] * matrix.elements[13]) + (matrix.elements[3] * matrix.elements[9] * matrix.elements[12]) + (matrix.elements[1] * matrix.elements[8] * matrix.elements[15]) + (matrix.elements[0] * matrix.elements[11] * matrix.elements[13]);
	cofactor.elements[10] = (matrix.elements[0] * matrix.elements[5] * matrix.elements[15]) + (matrix.elements[1] * matrix.elements[7] * matrix.elements[12]) + (matrix.elements[3] * matrix.elements[4] * matrix.elements[13]) - (matrix.elements[3] * matrix.elements[5] * matrix.elements[12]) - (matrix.elements[1] * matrix.elements[4] * matrix.elements[15]) - (matrix.elements[0] * matrix.elements[7] * matrix.elements[13]);
	cofactor.elements[11] = (-1 * (matrix.elements[0] * matrix.elements[5] * matrix.elements[11])) - (matrix.elements[1] * matrix.elements[7] * matrix.elements[8]) - (matrix.elements[3] * matrix.elements[4] * matrix.elements[9]) + (matrix.elements[3] * matrix.elements[5] * matrix.elements[8]) + (matrix.elements[1] * matrix.elements[4] * matrix.elements[11]) + (matrix.elements[0] * matrix.elements[7] * matrix.elements[9]);

	cofactor.elements[12] = (-1 * (matrix.elements[4] * matrix.elements[9] * matrix.elements[14])) - (matrix.elements[5] * matrix.elements[10] * matrix.elements[12]) - (matrix.elements[6] * matrix.elements[8] * matrix.elements[13]) + (matrix.elements[6] * matrix.elements[9] * matrix.elements[12]) + (matrix.elements[5] * matrix.elements[8] * matrix.elements[14]) + (matrix.elements[4] * matrix.elements[10] * matrix.elements[13]);
	cofactor.elements[13] = (matrix.elements[0] * matrix.elements[9] * matrix.elements[14]) + (matrix.elements[1] * matrix.elements[10] * matrix.elements[12]) + (matrix.elements[2] * matrix.elements[8] * matrix.elements[13]) - (matrix.elements[2] * matrix.elements[9] * matrix.elements[12]) - (matrix.elements[1] * matrix.elements[8] * matrix.elements[14]) - (matrix.elements[0] * matrix.elements[10] * matrix.elements[13]);
	cofactor.elements[14] = (-1 * (matrix.elements[0] * matrix.elements[5] * matrix.elements[14])) - (matrix.elements[1] * matrix.elements[6] * matrix.elements[12]) - (matrix.elements[2] * matrix.elements[4] * matrix.elements[13]) + (matrix.elements[2] * matrix.elements[5] * matrix.elements[12]) + (matrix.elements[1] * matrix.elements[4] * matrix.elements[14]) + (matrix.elements[0] * matrix.elements[6] * matrix.elements[13]);
	cofactor.elements[15] = (matrix.elements[0] * matrix.elements[5] * matrix.elements[10]) + (matrix.elements[1] * matrix.elements[6] * matrix.elements[8]) + (matrix.elements[2] * matrix.elements[4] * matrix.elements[9]) - (matrix.elements[2] * matrix.elements[5] * matrix.elements[8]) - (matrix.elements[1] * matrix.elements[4] * matrix.elements[10]) - (matrix.elements[0] * matrix.elements[6] * matrix.elements[9]);
	return cofactor;
}

Matrix SetIdentity(Matrix& matrix)
{
	for (int i = 0; i < 16; i++)
	{
		matrix.elements[i] = 0;
	}
	matrix.elements[0] = 1;
	matrix.elements[5] = 1;
	matrix.elements[10] = 1;
	matrix.elements[15] = 1;
	return matrix;
}

Matrix Translation(float x, float y, float z)
{
	Matrix matrix = SetIdentity(matrix);
	matrix.elements[12] = x;
	matrix.elements[13] = y;
	matrix.elements[14] = z;
	return matrix;
}

Matrix XRotation(float angle)
{
	Matrix _matrix = SetIdentity(_matrix);
	_matrix.elements[5] = cos(Radians(angle));
	_matrix.elements[6] = -sin(Radians(angle));
	_matrix.elements[9] = sin(Radians(angle));
	_matrix.elements[10] = cos(Radians(angle));
	return _matrix;
}
Matrix YRotation(float angle)//, float angle2, float angle3, float angle4)
{
	Matrix matrix = SetIdentity(matrix);
	matrix.elements[0] = cos(Radians(angle));
	matrix.elements[2] = sin(Radians(angle));
	matrix.elements[8] = -sin(Radians(angle));
	matrix.elements[10] = cos(Radians(angle));
	return matrix;
}
void ZRotation(Matrix& _matrix, float angle)
{
	_matrix.elements[0] = cos(Radians(angle));
	_matrix.elements[1] = -sin(Radians(angle));
	_matrix.elements[4] = sin(Radians(angle));
	_matrix.elements[5] = cos(Radians(angle));
}

void Scaling(Matrix& matrix, float x, float y, float z)
{
	matrix.elements[0] = matrix.elements[0] * x;
	matrix.elements[5] = matrix.elements[5] * y;
	matrix.elements[10] = matrix.elements[10] * z;
}

void NDC(Vertex& vertex)
{
	vertex.xyzw[0] = std::floor((vertex.xyzw[0] + 1) * screenWidth / 2);
	vertex.xyzw[1] = floor((1 - vertex.xyzw[1]) * screenHeight / 2);
}

Vertex FourVectorXMatrix(const Vertex& vector, const Matrix& matrix)
{
	Vertex temp = vector;
	temp.xyzw[0] = (vector.xyzw[0] * matrix.elements[0]) +
		(vector.xyzw[1] * matrix.elements[4]) +
		(vector.xyzw[2] * matrix.elements[8]) +
		(vector.xyzw[3] * matrix.elements[12]);

	temp.xyzw[1] = (vector.xyzw[0] * matrix.elements[1]) +
		(vector.xyzw[1] * matrix.elements[5]) +
		(vector.xyzw[2] * matrix.elements[9]) +
		(vector.xyzw[3] * matrix.elements[13]);

	temp.xyzw[2] = (vector.xyzw[0] * matrix.elements[2]) +
		(vector.xyzw[1] * matrix.elements[6]) +
		(vector.xyzw[2] * matrix.elements[10]) +
		(vector.xyzw[3] * matrix.elements[14]);

	temp.xyzw[3] = (vector.xyzw[0] * matrix.elements[3]) +
		(vector.xyzw[1] * matrix.elements[7]) +
		(vector.xyzw[2] * matrix.elements[11]) +
		(vector.xyzw[3] * matrix.elements[15]);

	return temp;
}

Matrix FourMatrixXMatrix(Matrix matrix1, Matrix matrix2)
{
	//index 0
	Matrix tmatrix;
	tmatrix.elements[0] =
		(matrix1.elements[0] * matrix2.elements[0]) +
		(matrix1.elements[1] * matrix2.elements[4]) +
		(matrix1.elements[2] * matrix2.elements[8]) +
		(matrix1.elements[3] * matrix2.elements[12]);
	//index 1
	tmatrix.elements[1] =
		(matrix1.elements[0] * matrix2.elements[1]) +
		(matrix1.elements[1] * matrix2.elements[5]) +
		(matrix1.elements[2] * matrix2.elements[9]) +
		(matrix1.elements[3] * matrix2.elements[13]);
	//index 2
	tmatrix.elements[2] =
		(matrix1.elements[0] * matrix2.elements[2]) +
		(matrix1.elements[1] * matrix2.elements[6]) +
		(matrix1.elements[2] * matrix2.elements[10]) +
		(matrix1.elements[3] * matrix2.elements[14]);
	//index 3
	tmatrix.elements[3] =
		(matrix1.elements[0] * matrix2.elements[3]) +
		(matrix1.elements[1] * matrix2.elements[7]) +
		(matrix1.elements[2] * matrix2.elements[11]) +
		(matrix1.elements[3] * matrix2.elements[15]);

	//index 4
	tmatrix.elements[4] =
		(matrix1.elements[4] * matrix2.elements[0]) +
		(matrix1.elements[5] * matrix2.elements[4]) +
		(matrix1.elements[6] * matrix2.elements[8]) +
		(matrix1.elements[7] * matrix2.elements[12]);
	//index 5
	tmatrix.elements[5] =
		(matrix1.elements[4] * matrix2.elements[1]) +
		(matrix1.elements[5] * matrix2.elements[5]) +
		(matrix1.elements[6] * matrix2.elements[9]) +
		(matrix1.elements[7] * matrix2.elements[13]);

	//index 6
	tmatrix.elements[6] =
		(matrix1.elements[4] * matrix2.elements[2]) +
		(matrix1.elements[5] * matrix2.elements[6]) +
		(matrix1.elements[6] * matrix2.elements[10]) +
		(matrix1.elements[7] * matrix2.elements[14]);
	//index 7
	tmatrix.elements[7] =
		(matrix1.elements[4] * matrix2.elements[3]) +
		(matrix1.elements[5] * matrix2.elements[7]) +
		(matrix1.elements[6] * matrix2.elements[11]) +
		(matrix1.elements[7] * matrix2.elements[15]);


	//index 8
	tmatrix.elements[8] =
		(matrix1.elements[8] * matrix2.elements[0]) +
		(matrix1.elements[9] * matrix2.elements[4]) +
		(matrix1.elements[10] * matrix2.elements[8]) +
		(matrix1.elements[11] * matrix2.elements[12]);
	//index 9
	tmatrix.elements[9] =
		(matrix1.elements[8] * matrix2.elements[1]) +
		(matrix1.elements[9] * matrix2.elements[5]) +
		(matrix1.elements[10] * matrix2.elements[9]) +
		(matrix1.elements[11] * matrix2.elements[13]);
	//index 10
	tmatrix.elements[10] =
		(matrix1.elements[8] * matrix2.elements[2]) +
		(matrix1.elements[9] * matrix2.elements[6]) +
		(matrix1.elements[10] * matrix2.elements[10]) +
		(matrix1.elements[11] * matrix2.elements[14]);
	//index 11
	tmatrix.elements[11] =
		(matrix1.elements[8] * matrix2.elements[3]) +
		(matrix1.elements[9] * matrix2.elements[7]) +
		(matrix1.elements[10] * matrix2.elements[11]) +
		(matrix1.elements[11] * matrix2.elements[15]);


	//index 12
	tmatrix.elements[12] =
		(matrix1.elements[12] * matrix2.elements[0]) +
		(matrix1.elements[13] * matrix2.elements[4]) +
		(matrix1.elements[14] * matrix2.elements[8]) +
		(matrix1.elements[15] * matrix2.elements[12]);
	//index 13
	tmatrix.elements[13] =
		(matrix1.elements[12] * matrix2.elements[1]) +
		(matrix1.elements[13] * matrix2.elements[5]) +
		(matrix1.elements[14] * matrix2.elements[9]) +
		(matrix1.elements[15] * matrix2.elements[13]);
	//index 14
	tmatrix.elements[14] =
		(matrix1.elements[12] * matrix2.elements[2]) +
		(matrix1.elements[13] * matrix2.elements[6]) +
		(matrix1.elements[14] * matrix2.elements[10]) +
		(matrix1.elements[15] * matrix2.elements[14]);
	//index 15
	tmatrix.elements[15] =
		(matrix1.elements[12] * matrix2.elements[3]) +
		(matrix1.elements[13] * matrix2.elements[7]) +
		(matrix1.elements[14] * matrix2.elements[11]) +
		(matrix1.elements[15] * matrix2.elements[15]);




	return tmatrix;

}
Matrix Inverse(Matrix matrix)
{
	float deter = DeterminantX4(matrix);
	Matrix cofactor = Cofactor(matrix);
	Matrix inverse;
	for (int i = 0; i < 16; i++)
	{
		inverse.elements[i] = cofactor.elements[i] / deter;
	}
	return inverse;
}

Matrix Transpose(Matrix _matrix)
{
	Matrix transpose;
	transpose.elements[0] = _matrix.elements[0];
	transpose.elements[1] = _matrix.elements[4];
	transpose.elements[2] = _matrix.elements[8];
	transpose.elements[3] = _matrix.elements[12];
	transpose.elements[4] = _matrix.elements[1];
	transpose.elements[5] = _matrix.elements[5];
	transpose.elements[6] = _matrix.elements[9];
	transpose.elements[7] = _matrix.elements[13];
	transpose.elements[8] = _matrix.elements[2];
	transpose.elements[9] = _matrix.elements[6];
	transpose.elements[10] = _matrix.elements[10];
	transpose.elements[11] = _matrix.elements[14];
	transpose.elements[12] = _matrix.elements[3];
	transpose.elements[13] = _matrix.elements[7];
	transpose.elements[14] = _matrix.elements[11];
	transpose.elements[15] = _matrix.elements[15];
	return transpose;
}
Vertex PerspectDiv(Vertex vertex)
{
	Vertex perspect = vertex;
	perspect.xyzw[0] = vertex.xyzw[0] / vertex.xyzw[3];
	perspect.xyzw[1] = vertex.xyzw[1] / vertex.xyzw[3];
	perspect.xyzw[2] = vertex.xyzw[2] / vertex.xyzw[3];
	return perspect;
}

Matrix Projection(float fov, float near, float far, float aspectR)
{
	Matrix projection = SetIdentity(projection);
	float yScale = Cotangent(.5 * fov);
	float xScale = yScale * aspectR;
	float zNear = 1;
	float zFar = 1;

	if (near != 0)
	{
		zNear = near;
	}
	if (far > near)
	{
		zFar = far;
	}

	projection.elements[0] = xScale;
	projection.elements[5] = yScale;
	projection.elements[10] = zFar / (zFar - zNear);
	projection.elements[11] = 1;
	projection.elements[14] = -1 * (zFar * zNear) / (zFar - zNear);
	projection.elements[15] = 0;

	return projection;
}
