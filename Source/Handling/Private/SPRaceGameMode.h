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

	TArray<ARaceCarPawn*> SortAllCarsByPosition(TArray<ARaceCarPawn*>);

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TArray<AActor*> Cars;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<AActor> PathBP;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<ARaceCarPawn> PlayerCar;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<ARaceCarPawn> AICar;

	AActor* Path;

	TMap<ARaceCarPawn*, float> CarsCurrentPositionInTrack;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TArray<ARaceCarPawn*> CarsOrderedByCurrentPosition;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 GameLaps;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	int32 MaxBots;

	inline static bool SortPredicate(const ARaceCarPawn& itemA,const ARaceCarPawn& itemB);
};
