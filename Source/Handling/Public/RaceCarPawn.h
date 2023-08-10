// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "RaceCarPawn.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API ARaceCarPawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BLueprintCallable)
	int32 GetCurrentPosition();

	UFUNCTION(BLueprintCallable)
	void SetPosition(int32 Position);

	UFUNCTION(BLueprintCallable)
	void SetLapCount(int32 Lap);

	UFUNCTION(BLueprintCallable)
	int32 GetLapCount();

	UFUNCTION(BLueprintCallable)
	float GetCurrentTime();

	UFUNCTION(BLueprintCallable)
	void ClearTimer();

	UFUNCTION(BLueprintCallable)
	float GetCurrentBestTime();

	UPROPERTY(EditAnywhere)
	int32 CurrentPosition;

	UPROPERTY(EditAnywhere)
	int32 CurrentLap;

	UPROPERTY(EditAnywhere)
	float TimeCounter;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<float> LapTimes;

};
