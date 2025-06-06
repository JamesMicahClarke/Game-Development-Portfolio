// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherSystem.h"
#include "Kismet/GameplayStatics.h"

/***********************************************
 * Filename:  		WeatherSystem.cpp
 * Date:      		04/11/2024
 * Mod. Date: 		05/24/2024
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
}

void AWeatherSystem::REI()
{
	RemoveExcessIndex();
}

void AWeatherSystem::RemoveExcessIndex()
{
	if (runREI)
	{
		for (int i = 0; i < disasterArr.Num(); i++)
		{
			if (disasterArr[i] == nullptr)
			{
				disasterArr.RemoveAt(i);
			}
		}
		for (int i = 0; i < weatherArr.Num(); i++)
		{
			if (weatherArr[i] == nullptr)
			{
				weatherArr.RemoveAt(i);
			}
		}
	}
}

void AWeatherSystem::SpawnDisaster_Implementation()
{

	//Location of the actor to be spawned
	const FVector m_location = GetActorLocation();
	//Rotation of the actor to be spawned
	const FRotator m_rotation = GetActorRotation();

	if (disasterArr[nextD] != NULL)
	{
		//Spawning object
		GetWorld()->SpawnActor<AActor>(disasterArr[nextD], m_location, m_rotation);
	}
}

void AWeatherSystem::SpawnWeather_Implementation()
{
	//Location of the actor to be spawned
	const FVector m_location = GetActorLocation();
	//Rotation of the actor to be spawned
	const FRotator m_rotation = GetActorRotation();

	if (weatherArr[nextW] != NULL)
	{

		//Spawning object
		GetWorld()->SpawnActor<AActor>(weatherArr[nextW], m_location, m_rotation);
	}
}

void AWeatherSystem::ClearWeather_Implementation()
{
	//Clears weather
	for (int i = 0; i < weatherArr.Num(); i++)
	{
		weatherObjToFind = UGameplayStatics::GetActorOfClass(GetWorld(), weatherArr[i].GetDefaultObject()->GetClass());

		if (weatherObjToFind != NULL)
		{
			weatherObjToFind->Destroy();
		}
	}
}

void AWeatherSystem::ClearDisaster_Implementation()
{
	//Clears disasters
	for (int i = 0; i < disasterArr.Num(); i++)
	{
		disObjToFind = UGameplayStatics::GetActorOfClass(GetWorld(), disasterArr[i].GetDefaultObject()->GetClass());

		if (disObjToFind != NULL)
		{
			disObjToFind->Destroy();
		}
	}
}

