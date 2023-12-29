// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include <RaceCarPawn.h>
#include <SPRaceGameMode.h>
#include "SPRaceGameState.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API ASPRaceGameState : public AGameStateBase
{
	GENERATED_BODY()

	ASPRaceGameState();

private:
	virtual void Tick(float DeltaSeconds) override;

	void BeginPlay();

	void SortCarPosition();

	TMap<ARaceCarPawn*, float> CarsCurrentPositionInTrack;

	TArray<ARaceCarPawn*> SortAllCarsByPosition(TArray<ARaceCarPawn*>);

	inline static bool SortPredicate(const ARaceCarPawn& itemA, const ARaceCarPawn& itemB);

	ASPRaceGameMode* GM;

	FTimerHandle FuzeTimerHandle;

	float RaceStartTime;

public:

	UPROPERTY(BlueprintReadOnly)
	TArray<ARaceCarPawn*> CarsOrderedByCurrentPosition;

	UFUNCTION(BlueprintCallable)
	void SetRaceStarted();

	UFUNCTION(BlueprintPure)
	float GetRaceTime();
	
};
