#pragma once
#include "BaseAccount.h"
class CreditAcc :
    public BaseAccount
{
private:
    int spent;
public:
    void Withdraw(float amount);
};

