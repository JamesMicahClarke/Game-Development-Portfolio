// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "WeatherSystem.generated.h"

/***********************************************
 * Filename:  		WeatherSystem.h
 * Date:      		04/11/2024
 * Mod. Date: 		05/24/2024
 * Mod. Initials:	JC
 * Author:    		James Clarke
 ************************************************/


UCLASS()
class ####_API AWeatherSystem : public AActor //This portion has been edited out
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

	//manual switch to turn Remove Excess Index on/off (true by default) (c++)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weather System c++")
		bool runREI = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weather System c++")
		//next value for weather (c++)
		int nextW;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weather System c++")
		//next value for disasters (c++)
		int nextD;

	//An array to store disaster event objects in for spawning (make sure this lines up with the Disaster enum) (c++)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weather System c++")
		TArray<TSubclassOf<AActor>> disasterArr;

	//An array to store weather event objects in for spawning (make sure this lines up with the Weather enum) (c++)
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weather System c++")
		TArray<TSubclassOf<AActor>> weatherArr;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weather System c++")
		//Spawns the next disaster event (c++)
		void SpawnDisaster();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weather System c++")
		//Spawns the next weather event (c++)
		void SpawnWeather();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weather System c++")
		//Returns weather to it's default state (c++)
		void ClearWeather();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weather System c++")
		//Clears a disaster (c++)
		void ClearDisaster();

	//Protected version of Remove Excess Index which: "Removes null indexes from weather and disaster arrays" (c++)
	UFUNCTION(CallinEditor, Category = "Weather System c++")
		void REI();

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Weather System c++")
		//Object used to find disaster objects to be cleared 
		AActor* disObjToFind;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Weather System c++")
		//Object used to find normal weather objects to be cleared 
		AActor* weatherObjToFind;

	//Removes null indexes from weather and disaster arrays
	void RemoveExcessIndex();

};
