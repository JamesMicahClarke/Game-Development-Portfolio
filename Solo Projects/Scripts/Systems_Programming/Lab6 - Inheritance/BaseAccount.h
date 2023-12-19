#pragma once
class BaseAccount
{
protected:
	float accBalance = 0;
	int withdrawls = 0;
public:
	void Withdraw(float amount);
	void Deposit(float amount);
	float GetBalance() const;

};

