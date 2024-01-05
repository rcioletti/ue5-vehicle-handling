// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include <Player/RaceCarPawn.h>
#include <Core/GameStructs.h>
#include "RaceSaveGame.generated.h"
/**
 * 
 */
UCLASS()
class HANDLING_API URaceSaveGame : public USaveGame
{

public:
	GENERATED_BODY()

	URaceSaveGame();

	UPROPERTY(BlueprintReadWrite, Category="Player Info")
	FString PlayerName;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	float BestLapTime;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	int32 Money = 10000;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	TArray<TSubclassOf<ARaceCarPawn>> OwnedCars;

	UPROPERTY(BlueprintReadWrite, Category = "Player Stats")
	TArray<FCarCustomizations> CarMods;
};
