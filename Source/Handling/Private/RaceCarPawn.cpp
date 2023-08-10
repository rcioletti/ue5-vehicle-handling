// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceCarPawn.h"
#include "Engine/World.h"

void ARaceCarPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TimeCounter = DeltaSeconds + TimeCounter;

	//if (GEngine)
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Time: %f"), TimeCounter));
}

int32 ARaceCarPawn::GetCurrentPosition()
{
	return CurrentPosition;
}

void ARaceCarPawn::SetPosition(int32 Position)
{
	CurrentPosition = Position;
}

void ARaceCarPawn::SetLapCount(int32 Lap)
{
	CurrentLap = Lap;
}

int32 ARaceCarPawn::GetLapCount()
{
	return CurrentLap;
}

float ARaceCarPawn::GetCurrentTime()
{
	return TimeCounter;
}

void ARaceCarPawn::ClearTimer()
{
	LapTimes.Add(TimeCounter);
	TimeCounter = 0.0f;
}

float ARaceCarPawn::GetCurrentBestTime()
{
	if (FMath::Max<float>(LapTimes) != 0.0f)
	{
		return FMath::Min<float>(LapTimes);
	}
	else {
		return 0.0f;
	}
}
