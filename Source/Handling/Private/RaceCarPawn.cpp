// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceCarPawn.h"
#include "Engine/World.h"

void ARaceCarPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TimeCounter = DeltaSeconds + TimeCounter;


	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Name: %s"), *Name));
}

void ARaceCarPawn::ClearTimer()
{
	LapTimes.Add(TimeCounter);
	TimeCounter = 0.0f;
}

float ARaceCarPawn::GetCurrentBestTime()
{
	if (FMath::Min<float>(LapTimes) != NULL)
	{
		return FMath::Min<float>(LapTimes);
	}
	else {
		return 0.0f;
	}
}
