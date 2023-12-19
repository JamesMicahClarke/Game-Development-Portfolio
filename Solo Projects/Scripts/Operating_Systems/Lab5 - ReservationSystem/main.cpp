///////////////////////////////////////////////////////////////////////////////////
// file:  main.cpp
// Job:   to hold the main logic of the test and to hold the function that will be the thread
//////////////////////////////////////////////////////////////////////////////////

// include needed files
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

#include "Car.h"
#include "Station.h"

using namespace std;

// Include file and line numbers for memory leak detection for visual studio in debug mode
// NOTE: The current implementation of C++11 shipped with Visual Studio 2012 will leak a single
//   44-byte mutex (at_thread_exit_mutex) internally if any threads have been created. This
//   will show up in the output window without a filename or line number.
#if defined _MSC_VER && defined _DEBUG
	#include <crtdbg.h>
	#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define ENABLE_LEAK_DETECTION() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
	#define ENABLE_LEAK_DETECTION()
#endif

///////////////////////////////////////////////////////////////////////////////////
// Name:		pause
//
// Arguments:	void
//
// Note:		Prompts the user to press enter and waits for user input
//
// Returns:		void
///////////////////////////////////////////////////////////////////////////////////
void pause()
{
	printf("Press Enter to continue\n");
	getchar();
}

///////////////////////////////////////////////////////////////////////////////////
// Name:		testACar
//
// Arguments:	Car* - the pointer to the memory of a car that is in this test
//
// Note:		First handle the starting gun scenario then run the test until
//				the bool is toggled from the time limit
//
// Returns:		void
///////////////////////////////////////////////////////////////////////////////////
void testACar(Car* car)
{
	//starting line with count inc the wait for the gun
	unique_lock<mutex> gunUnique(*(car->getGunMutex()));
	{
		car->getCountMutex()->lock();
		{
			car->incNumberWaitingInLine();
			car->getCountCondition()->notify_one();
		}
		car->getCountMutex()->unlock();
		car->getGunCondition()->wait(gunUnique);
	}
	gunUnique.unlock();

	// run test until flag is set
	while((*(car->getTestOver())) == false)
	{
		car->fillTank();
	}
}

///////////////////////////////////////////////////////////////////////////////////
// Name:		main
//
// Arguments:	int argc	- gives the number of command line params passed in plus
//							  one for the .exe
//				char** argv - array of the command line params (use atoi to access)
//
// Note:		launch point of the project will set up the test and print the results
//
// Returns:		int			- exit flag for the main func
///////////////////////////////////////////////////////////////////////////////////
int main(int argc, char**argv)
{
	ENABLE_LEAK_DETECTION();

	// create variables for command line args
	int maxCars = 0;
	int maxPumps = 0;
	int timeInSecForTest = 0;
	
	// read in command line args or use defaults provided
	if(argc != 4)
	{
		maxCars = 10;
		maxPumps = 2;
		timeInSecForTest = 30;
	}
	else
	{
		maxCars = atoi(argv[1]);
		maxPumps = atoi(argv[2]);
		timeInSecForTest = atoi(argv[3]);

		if(maxCars <= 0)
		{
			cout << "Car count <= 0, exiting" << endl;
			exit(-1);
		}

		if(maxPumps <= 0)
		{
			cout << "Pump count <= 0, exiting" << endl;
			exit(-1);
		}

		if(timeInSecForTest <= 0)
		{
			cout << "timeInSecForTest <= 0, exiting" << endl;
			exit(-1);
		}
	}

	cout << "Running Gas Station, using " << maxCars << " cars, using " << maxPumps << " pumps" << endl;
	
	// creates all variables need for the test of the reservation system
	// needed:
	//				1 bool
	//				1 int
	//				3 mutex
	//				3 condition variables
	//				1 Station
	//				the Station will make our pumps
	//				(max) cars

	bool testOver;
	int numberStandingInLine = 0;
	std::mutex countMutex;
	std::mutex gunMutex;
	condition_variable gunCondition;
	condition_variable countCondition;
	Station stationToUse;
	std::mutex stationMutex;
	condition_variable stationCondition;
	Car *carsInTheTest = new Car[maxCars];
	
	// set all variables into there respected classes
	stationToUse.createPumps(maxPumps);
	stationToUse.setCarsInStation(maxCars);
	stationToUse.setStationMutex(&stationMutex);
	stationToUse.setStationCondition(&stationCondition);

	for(int i = 0; i < maxCars; i++)
	{
		carsInTheTest[i].setStationToUse(&stationToUse);
		carsInTheTest[i].setNumberStandingInLine(&numberStandingInLine);
		carsInTheTest[i].setCountMutex(&countMutex);
		carsInTheTest[i].setCountCondition(&countCondition);
		carsInTheTest[i].setGunMutex(&gunMutex);
		carsInTheTest[i].setGunCondition(&gunCondition);
		carsInTheTest[i].setTestOver(&testOver);
		carsInTheTest[i].startCar(testACar);
	}

	// waiting till everyone is at the starting line
	unique_lock<mutex> countUnique(countMutex);
	{
		while(numberStandingInLine != maxCars)
		{
			countCondition.wait(countUnique);
		}
	}
	countUnique.unlock();

	// shoot the gun
	gunMutex.lock();
	{
		testOver = false;
		gunCondition.notify_all();
	}
	gunMutex.unlock();

	//pause for the length of the test
	this_thread::sleep_for(chrono::seconds(timeInSecForTest));

	// our test in now over so start the ending sequence
	stationMutex.lock();
	{
		testOver = true;
		stationCondition.notify_all();
	}
	stationMutex.unlock();

	for(int i = 0; i < maxCars; i++)
	{
		carsInTheTest[i].waitForCarToStop();
	}
	
	//print all result for the cars and pumps at the station
	cout << "Cars:" << endl;
	for(int i = 0; i < maxCars; i++)
	{
		cout << "  car # " << i << ", Fill count " << carsInTheTest[i].getFillCount(); 
		cout << ", Try count " << carsInTheTest[i].getTryCount() << endl;
	}

	cout << "Station:" << endl;

	for(int i = 0; i < maxPumps; i++)
	{
		cout << "  Pump " << i << ", Fill count " << stationToUse.getPumpFillCount(i) << endl;
	}

	// clean up our memory
	delete []carsInTheTest;

	// pause main at end of program
	pause();
	return 0;
}
