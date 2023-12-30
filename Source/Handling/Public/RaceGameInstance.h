// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <RaceSaveGame.h>
#include <RaceCarPawn.h>
#include "RaceGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API URaceGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	URaceGameInstance();

	UPROPERTY(BlueprintReadOnly)
	FString SaveGameSlotName = "local_save ";

	UPROPERTY(BlueprintReadWrite, Category="Settings")
	URaceSaveGame* SaveGameObject;

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void LoadGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void SetCarCustomizations(FCarCustomizations CarMod);

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	FCarCustomizations GetCarCustomizations(TSubclassOf<ARaceCarPawn> CarPawnReference);

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void AddMoney(int32 Money);

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void RemoveMoney(int32 Money);

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	bool SetNewBestTime(float Time, FString MapName);

	UPROPERTY(BlueprintReadWrite, Category="Game Settings")
	FName SelectedMap;

	UPROPERTY(BlueprintReadWrite, Category = "Game Settings")
	int32 NumberOfLaps;

	UPROPERTY(BlueprintReadWrite, Category = "Game Settings")
	int32 RacePayout;

	UPROPERTY(BlueprintReadWrite, Category="Game Settings")
	TSubclassOf<ARaceCarPawn> SelectedCar;
};
