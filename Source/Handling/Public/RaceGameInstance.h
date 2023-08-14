// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <RaceSaveGame.h>
#include "RaceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API URaceGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString SaveGameSlotName = "local_save";

	UPROPERTY(BlueprintReadWrite, Category="Settings")
	URaceSaveGame* SaveGameObject;

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void LoadGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void SaveGame();
};
