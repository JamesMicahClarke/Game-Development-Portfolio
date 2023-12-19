#pragma once
class TriangleStack
{
private:
	float mBase;
	float mHeight;
public:
	void SetBase(float base);
	void SetHeight(float height);
	float GetArea();
};

