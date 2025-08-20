// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherSystem.generated.h"


/***********************************************
 * Filename:  		WeatherSystem.h
 * Date:      		04/11/2024
 * Mod. Date: 		04/25/2024
 * Mod. Initials:	JC
 * Author:    		James Clarke
 ************************************************/

UCLASS()
class SAGA_API AWeatherSystem : public AActor
{
	GENERATED_BODY()

public:
	//Sets default values for this actor's properties
	AWeatherSystem();

	//FMath proxy - used to access properties of the FMath class
	FMath math;

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//FTimerHandle proxy
	FTimerHandle timerHandle;

	//An array that holds the duration for each disaster before clearing
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<float> disDuration;

	//An array that holds the duration for each normal weather event before clearing
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<float> normDuration;

	/*Time to wait before spawning.
	This should not be active while an event is happening*/
	UPROPERTY(EditAnywhere)
		float startDuration;

	//Runs a roullette to choose the next disaster state
	void SpawnDisaster();

	//Runs a roullette to choose the next non-disaster state
	void SpawnNormal();

	//Returns weather to it's constant state
	void ClearWeather();

private:
	
	//An array to store disaster event objects in for spawning
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<AActor>> disasterArr;

	//An array to store normal weather event objects in for spawning
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<TSubclassOf<AActor>> normalArr;

	//Object used to find disaster objects to be cleared 
	TArray<AActor*> disObjToFind;

	//Object used to find normal weather objects to be cleared 
	TArray<AActor*> normObjToFind;

	//An array of all weather events used to randomly select the type of weather being spawned
	TArray<TArray<TSubclassOf<AActor>>> randChoice;

	//Removes null indexes from weather arrays
	void RemoveExcessIndex();

	//Copies weather arrays for selection
	void FillRandChoice();

	//Randomly selects a disaster or normal weather
	void RandWeatherSelection();

	//If durations were set to negative values uses the absolute value
	void AbsoluteDuration();

};