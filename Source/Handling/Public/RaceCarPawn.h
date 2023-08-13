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


public:

	UFUNCTION(BLueprintCallable)
	void ClearTimer();

	UFUNCTION(BLueprintCallable)
	float GetCurrentBestTime();

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 CurrentPosition;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	float TimeCounter;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 CurrentLap = 1;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TArray<float> LapTimes;

};
