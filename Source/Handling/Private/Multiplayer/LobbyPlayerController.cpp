// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/LobbyPlayerController.h"
#include <Core\RaceGameInstance.h>
#include <Multiplayer\LobbyShowcaseCar.h>
#include <Kismet\GameplayStatics.h>
#include <Multiplayer\MPRaceGameState.h>

void ALobbyPlayerController::Server_SetPlayerID_Implementation(int32 ID)
{
	PlayerID = ID;
	Client_SetPlayerID(ID);
}

void ALobbyPlayerController::Client_SetPlayerID_Implementation(int32 ID)
{
	PlayerID = ID;
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyPlayerController::Server_SelectNewCar_Implementation(bool isAdding)
{
	URaceGameInstance* GI = Cast<URaceGameInstance>(GetGameInstance());

	TArray<FCarData*> AllCarData = GI->GetGameData()->GetCars();

	if (isAdding && SelectedCarIndex + 1 < AllCarData.Num()) {
		SelectedCarIndex++;
		Server_DisplayCarInLobby(SelectedCarIndex);
	}
	else if (!isAdding && SelectedCarIndex - 1 >= 0) {
		SelectedCarIndex--;
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
