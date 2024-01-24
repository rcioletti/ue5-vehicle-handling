// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include <GameFramework\PlayerStart.h>
#include <Player\RaceCarPawn.h>
#include "MPRaceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API AMPRaceGameMode : public AGameMode
{
	GENERATED_BODY()
	
	AMPRaceGameMode();

	virtual void BeginPlay() override;

	virtual void GenericPlayerInitialization(AController* Controller) override;

	TArray<FTransform> FindAllPlayerStart();

	TArray<AActor*> AllPlayerStartActor;

public:

	UFUNCTION(BLueprintCallable)
	void SpawnPlayer(APlayerController* PlayerController);

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TArray<ARaceCarPawn*> Cars;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 GameLaps;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 RacePayout;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	bool bHasRaceStarted = false;
};
