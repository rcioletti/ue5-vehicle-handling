// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameInstance.h"
#include "Kismet/GameplayStatics.h"

URaceGameInstance::URaceGameInstance() {

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Game Instance Initialized")));
}

void URaceGameInstance::LoadGame()
{
	USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(SaveGameSlotName, 0);
	SaveGameObject = Cast<URaceSaveGame>(LoadedGame);

	if (!SaveGameObject) {

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Creating new save game")));

		SaveGameObject = Cast<URaceSaveGame>(UGameplayStatics::CreateSaveGameObject(URaceSaveGame::StaticClass()));

		const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameSlotName, 0);
	}
}

void URaceGameInstance::SaveGame()
{
	const bool IsSaved = UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveGameSlotName, 0);
}

void URaceGameInstance::SetCarCustomizations(FCarCustomizations CarMod)
{
	bool bWasSet = false;

	for (int i = 0; i < SaveGameObject->CarMods.Num(); i++) {
		
		if (SaveGameObject->CarMods[i].Car == CarMod.Car) {
			
			bWasSet = true;

			SaveGameObject->CarMods.RemoveAt(i);
			SaveGameObject->CarMods.Insert(CarMod, i);

			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Set custom mods")));
		}
	}
		
	if (!bWasSet) {

		SaveGameObject->CarMods.Add(CarMod);

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Set custom mods added new car")));
	}

	SaveGame();
}

FCarCustomizations URaceGameInstance::GetCarCustomizations(TSubclassOf<ARaceCarPawn> CarPawnReference)
{
	if (SaveGameObject != NULL) {
		for (int i = 0; i < SaveGameObject->CarMods.Num(); i++) {

			if (SaveGameObject->CarMods[i].Car == CarPawnReference) {

				return SaveGameObject->CarMods[i];
			}
		}
	}

	return FCarCustomizations();
}

void URaceGameInstance::AddMoney(int32 Money)
{
	SaveGameObject->Money += Money;
}

void URaceGameInstance::RemoveMoney(int32 Money)
{
	SaveGameObject->Money -= Money;
}

bool URaceGameInstance::SetNewBestTime(float Time, FString MapName)
{
	if (Time < SaveGameObject->BestLapTime) {
		
		SaveGameObject->BestLapTime = Time;

		return true;
	}

	return false;
}
