#pragma once
/*math related functions
* vertex mul matrix
* matrix mul matrix
* convert 2D - 1D
* matrix identidy
* etc...*/
#include "Defines.h"
#include <math.h>


//TwoToOne - converts a 2D array to 1D (used in indexing) 
int TwoToOne(int x, int y, int width)
{
	int convert = y * width + x;
	return convert;
}

//returns a integer value that is between 2 points (often used for moving or changing values)
unsigned int Lerp(unsigned int one, unsigned int two, float ratio)
{
	unsigned int lerp = ((int)two - (int)one) * ratio + (int)one;
	return lerp;
}
//returns a floating value that is between 2 points (often used for moving or changing values)
float FLerp(float one, float two, float ratio)
{
	float lerp = (two - one) * ratio + one;
	return lerp;
}
//returns a Barycentric value that is between 2 points (often used for moving or changing values)
float BLerp(Bary bya, float a, float b, float c)
{
	return a * bya.values[0] + b * bya.values[1] + c * bya.values[2];
}

//converts an angle to a radian as a float
float Radians(float degree)
{
	return degree * (pi / 180);
}
//returns the cotangent of an angle
float Cotangent(float angle)
{
	return 1.0f / tan(Radians(angle));
}


float LineEquation(Vertex vertex, Vertex line[])
{
	return (line[0].xyzw[1] - line[1].xyzw[1]) * vertex.xyzw[0] + (line[1].xyzw[0] - line[0].xyzw[0]) * vertex.xyzw[1] + (line[0].xyzw[0] * line[1].xyzw[1]) - (line[0].xyzw[1] * line[1].xyzw[0]);
}

//sets barycentric coordinates for a triangle
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

/*NDC - takes in a vertex to confine the x and y values from 1 to - 1 on the screen
values should be from 1 to -1*/
void NDC(Vertex& vertex)
{
	vertex.xyzw[0] = (vertex.xyzw[0] + 1) * screenWidth / 2;
	vertex.xyzw[1] = (1 - vertex.xyzw[1]) * screenHeight / 2;
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
