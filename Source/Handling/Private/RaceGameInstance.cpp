// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameInstance.h"
#include "Kismet/GameplayStatics.h"

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
