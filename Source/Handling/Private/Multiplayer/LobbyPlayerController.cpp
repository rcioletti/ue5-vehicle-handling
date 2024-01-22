// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/LobbyPlayerController.h"
#include <Core\RaceGameInstance.h>
#include <Multiplayer\LobbyShowcaseCar.h>
#include <Kismet\GameplayStatics.h>
#include <Multiplayer\MPRaceGameState.h>
#include <Multiplayer\MPRaceGameMode.h>
#include <Player\RacePlayerState.h>


void ALobbyPlayerController::Server_SetPlayerID_Implementation(int32 ID)
{
	PlayerID = ID;
}

void ALobbyPlayerController::Client_SetPlayerID_Implementation(int32 ID)
{
	PlayerID = ID;
}

void ALobbyPlayerController::Server_CheckIsEveryoneReady_Implementation()
{
	AMPRaceGameMode* GM = Cast<AMPRaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	GM->CheckEveryoneReady();
}

void ALobbyPlayerController::Server_ToggleIsReady_Implementation()
{
	ARacePlayerState* PS = Cast<ARacePlayerState>(PlayerState);

	PS->isReady = PS->isReady ? false : true;
}

void ALobbyPlayerController::Server_SelectNewCar_Implementation(bool isAdding)
{
	URaceGameInstance* GI = Cast<URaceGameInstance>(GetGameInstance());

	TArray<FCarData*> AllCarData = GI->GetGameData()->GetCars();

	int32 SelectedCarIndex = Cast<ARacePlayerState>(PlayerState)->SelectedCarIndex;

	if (isAdding && SelectedCarIndex + 1 < AllCarData.Num()) {
		SelectedCarIndex++;
		Cast<ARacePlayerState>(PlayerState)->SelectedCarIndex = SelectedCarIndex;
		Server_DisplayCarInLobby(SelectedCarIndex);
	}
	else if (!isAdding && SelectedCarIndex - 1 >= 0) {
		SelectedCarIndex--;
		Cast<ARacePlayerState>(PlayerState)->SelectedCarIndex = SelectedCarIndex;
		Server_DisplayCarInLobby(SelectedCarIndex);
	}
}

void ALobbyPlayerController::Server_DisplayCarInLobby_Implementation(int32 CarIndex)
{
	URaceGameInstance* GI = Cast<URaceGameInstance>(GetGameInstance());

	FCarData* CarData = GI->GetGameData()->GetCars()[CarIndex];

	TArray<AActor*> AllShowcaseCar;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALobbyShowcaseCar::StaticClass(), AllShowcaseCar);

	ALobbyShowcaseCar* Showcase = Cast<ALobbyShowcaseCar>(AllShowcaseCar[PlayerID]);

	Showcase->CarMesh = CarData->CarSkeletalMesh;
	Showcase->OnRep_SelectedCar();
}