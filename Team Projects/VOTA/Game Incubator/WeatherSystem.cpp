// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherSystem.h"
#include "Kismet/GameplayStatics.h"

/***********************************************
 * Filename:  		WeatherSystem.cpp
 * Date:      		04/11/2024
 * Mod. Date: 		04/25/2024
 * Mod. Initials:	JC
 * Author:    		James Clarke
 ************************************************/

 // Sets default values
AWeatherSystem::AWeatherSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AWeatherSystem::BeginPlay()
{
	Super::BeginPlay();

	RemoveExcessIndex();

	FillRandChoice();

	AbsoluteDuration();

	//Starts timer to spawn the first event
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWeatherSystem::RandWeatherSelection, startDuration, false);

}

void AWeatherSystem::RemoveExcessIndex()
{
	for (int i = 0; i < disasterArr.Num(); i++)
	{
		if (disasterArr[i] == nullptr)
		{
			disasterArr.RemoveAt(i);
		}
	}
	for (int i = 0; i < normalArr.Num(); i++)
	{
		if (normalArr[i] == nullptr)
		{
			normalArr.RemoveAt(i);
		}
	}
}

void AWeatherSystem::FillRandChoice()
{
	//Copies weather arrays
	randChoice.Emplace(disasterArr);
	randChoice.Emplace(normalArr);
}

void AWeatherSystem::AbsoluteDuration()
{
	if (startDuration < 0)
		startDuration = math.Abs(startDuration);

	for (int i = 0; i < disDuration.Num(); i++)
	{
		if (disDuration[i] < 0)
			disDuration[i] = math.Abs(disDuration[i]);
	}

	for (int i = 0; i < normDuration.Num(); i++)
	{
		if (normDuration[i])
			normDuration[i] = math.Abs(normDuration[i]);
	}
}

void AWeatherSystem::RandWeatherSelection()
{
	//Randomly chooses an index to check for
	int rand = math.RandRange(0, randChoice.Num() - 1);

	//Spawns weather based on chosen index
	switch (rand)
	{
	case 0:

		SpawnDisaster();
		break;
	case 1:

		SpawnNormal();
		break;
	}

}

void AWeatherSystem::SpawnDisaster()
{

	//Location of the actor to be spawned
	const FVector m_location = GetActorLocation();
	//Rotation of the actor to be spawned
	const FRotator m_rotation = GetActorRotation();

	//Provides a random index of the array
	int rand = math.RandRange(0, disasterArr.Num() - 1);

	//Spawning object
	GetWorld()->SpawnActor<AActor>(disasterArr[rand], m_location, m_rotation);

	AbsoluteDuration();

	//Starts timer to wait before clearing weather
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWeatherSystem::ClearWeather, disDuration[rand], false);
}

void AWeatherSystem::SpawnNormal()
{
	//Location of the actor to be spawned
	const FVector m_location = GetActorLocation();
	//Rotation of the actor to be spawned
	const FRotator m_rotation = GetActorRotation();

	//Provides a random index of the array
	int rand = math.RandRange(0, normalArr.Num() - 1);

	//Spawning object
	GetWorld()->SpawnActor<AActor>(normalArr[rand], m_location, m_rotation);

	AbsoluteDuration();

	//Starts timer to wait before clearing weather
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWeatherSystem::ClearWeather, normDuration[rand], false);
}

void AWeatherSystem::ClearWeather()
{
	//Clears weather
	for (int i = 0; i < disasterArr.Num(); i++)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), disasterArr[i].GetDefaultObject()->GetClass(), disObjToFind);
		for (AActor* Actor : disObjToFind)
		{
			Actor->Destroy();
		}
	}
	for (int i = 0; i < normalArr.Num(); i++)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), normalArr[i].GetDefaultObject()->GetClass(), normObjToFind);
		for (AActor* Actor : normObjToFind)
		{
			Actor->Destroy();
		}
	}

	//Clears timer
	GetWorld()->GetTimerManager().ClearTimer(timerHandle);

	AbsoluteDuration();

	//Starts the countdown for the next event
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AWeatherSystem::RandWeatherSelection, startDuration, false);
}

