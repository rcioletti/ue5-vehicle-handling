// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <RaceCarPawn.h>
#include <GameFramework\PlayerStart.h>
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
	
	TArray<FTransform> FindAllPlayerStart();

	TArray<AActor*> AllPlayerStartActor;

public:

	UFUNCTION(BLueprintCallable)
	void SpawnPlayer(APlayerController* PlayerController);

	void SortCarPosition();

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TArray<AActor*> Cars;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<AActor> PathBP;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<ARaceCarPawn> PlayerCar;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<ARaceCarPawn> AICar;

	AActor* Path;

	TArray<float> CurrentPosition;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 GameLaps;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 MaxBots;
};
