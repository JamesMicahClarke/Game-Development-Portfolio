#pragma once
class TriangleHeap
{
private:
	float* mBase = new float;
	float* mHeight = new float;
	
public:
	void SetBase(float base);
	void SetHeight(float height);
	float GetArea();
	TriangleHeap();
	~TriangleHeap();
	TriangleHeap& operator=(const TriangleHeap& op);
	void TriangleCopy(TriangleHeap& copy);
};

