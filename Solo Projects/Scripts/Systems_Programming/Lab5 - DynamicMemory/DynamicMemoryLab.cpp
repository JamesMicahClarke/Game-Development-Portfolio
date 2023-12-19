#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <math.h>
#include "Corporate.h"
#include "StringHelpers.h"

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(152);
    _CrtDumpMemoryLeaks();

    Corporate* c = new Corporate;
    long long r = c->GetReceipts();
    std::cout << "Corporate: " << StringHelpers::FormatMoneyText(r) << std::endl;
    delete c;
}
