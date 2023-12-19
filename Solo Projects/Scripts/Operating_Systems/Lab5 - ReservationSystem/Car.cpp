///////////////////////////////////////////////////////////////////////////////////
// file:  Car.cpp
// Job:   holds the Car definitions 
//////////////////////////////////////////////////////////////////////////////////
#include "Car.h"
#include "Station.h"

using namespace std;

extern void testACar(void*);

Car::Car(void) 
{
	fillCount = 0;
	tryCount = 0;
	thread = nullptr;
	stationToUse = nullptr;
	numberWaitingInLine = nullptr;
}

Car::~Car(void)
{
}

int Car::getFillCount(void)
{
	return this->fillCount;
}

int Car::getTryCount(void)
{
	return this->tryCount;
}

int Car::fillTank(void)
{
	int result;

	if(stationToUse == nullptr)
		return -1;

	tryCount++;

	result = stationToUse->fillUp();

	if(result == 1)
	{
		this->fillCount++;
	}

	return 1;
}

void Car::startCar(void testACar(Car* car))
{
	///////////////////////////////////////////////////////////////////////////
	// TODO: Start the thread that will be used for the car
	//(these will be joinable threads)
	///////////////////////////////////////////////////////////////////////////
	thread = new std::thread(testACar, this);
	
}

void Car::waitForCarToStop(void)
{
	///////////////////////////////////////////////////////////////////////////
	// TODO: stop and clean up the car threads
	///////////////////////////////////////////////////////////////////////////
	thread->join();

	delete thread;
}

void Car::setStationToUse(Station *myStation)
{
	stationToUse = myStation;	
}

void Car::setCountMutex(std::mutex* m)
{
	this->countMutex = m;
}

void Car::setCountCondition(std::condition_variable* cv)
{
	this->countCondition = cv;
}

void Car::setGunMutex(std::mutex* m)
{
	this->gunMutex = m;
}

void Car::setGunCondition(std::condition_variable* cv)
{
	this->gunCondition = cv;
}

void Car::setNumberStandingInLine(int* num)
{
	this->numberWaitingInLine = num;
}

void Car::incNumberWaitingInLine()
{
	(*(this->numberWaitingInLine))++;
}

void Car::decNumberWaitingInLine()
{
	(*(this->numberWaitingInLine))--;
}

void Car::setTestOver(bool* b)
{
	this->testOver = b;
}

Station* Car::getStationToUse(void)
{
	return this->stationToUse; 
}

std::mutex* Car::getCountMutex(void)
{
	return this->countMutex;
}

std::condition_variable* Car::getCountCondition(void)
{
	return this->countCondition;
}

std::mutex* Car::getGunMutex(void)
{
	return this->gunMutex;
}

std::condition_variable* Car::getGunCondition(void)
{
	return this->gunCondition;
}

bool* Car::getTestOver(void)
{
	return this->testOver;
}
