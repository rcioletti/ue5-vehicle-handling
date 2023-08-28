// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
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

	UPROPERTY(BlueprintReadWrite, Category="Player Info")
	float BestLapTime;

	UPROPERTY(BlueprintReadWrite, Category="Player Info")
	float Money;
	
};
