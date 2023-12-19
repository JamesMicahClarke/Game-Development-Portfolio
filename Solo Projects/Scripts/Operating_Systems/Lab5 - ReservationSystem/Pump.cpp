///////////////////////////////////////////////////////////////////////////////////
// file:  Pump.cpp
// Job:   holds the Pump definitions 
//////////////////////////////////////////////////////////////////////////////////
#include "Pump.h"
#include <thread>

using namespace std;

Pump::Pump(void)
{
	fillCount = 0;
}

Pump::~Pump(void)
{
}

void Pump::fillTankUp(void)
{
	fillCount++;
	
	this_thread::sleep_for(chrono::milliseconds(30));
}

int Pump::getFillCount(void)
{
	return fillCount;
}