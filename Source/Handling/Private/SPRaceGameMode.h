// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <RaceCarPawn.h>
#include "SPRaceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASPRaceGameMode : public AGameModeBase
{
	GENERATED_BODY()

	ASPRaceGameMode();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

public:

	void SortCarPosition();

	TArray<AActor*> Cars;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<AActor> PathBP;

	AActor* Path;

	TArray<float> CurrentPosition;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 GameLaps;
};
