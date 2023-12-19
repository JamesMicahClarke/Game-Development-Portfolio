#pragma once
class Base1
{
private:
	char* character = nullptr;

public:
	Base1();
	~Base1();
	void baseCopy(Base1& opIn);
	Base1& operator=(const Base1& op);
	void SetName(const char* name);
	char* GetName();
	virtual void DisplayRecord() = 0;

};

