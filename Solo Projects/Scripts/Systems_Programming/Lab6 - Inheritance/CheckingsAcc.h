#pragma once
#include "BaseAccount.h"
class CheckingsAcc :
    public BaseAccount
{
public:
    void Withdraw(float amount);
};

