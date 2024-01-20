// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameState.h"
#include <Engine.h>
#include <Core\GameData.h>
#include <Net\UnrealNetwork.h>
#include <Core\RaceGameInstance.h>
#include <Multiplayer\LobbyPlayerController.h>

void AMPRaceGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AMPRaceGameState, SelectedCar);
}

//void AMPRaceGameState::OnRep_LastAddedPlayer()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Replicated")));
//
//	UpdateAllDisplayedCars();
//}

void AMPRaceGameState::SetNewCarIndex_Implementation(bool isAdding, APlayerController* PC)
{
	URaceGameInstance* GI = Cast<URaceGameInstance>(GetGameInstance());

	TArray<FCarData*> CarData = GI->GetGameData()->GetCars();

	if (isAdding && SelectedCar[PC] + 1 < CarData.Num()) {
		SelectedCar[PC] = SelectedCar[PC] + 1;
	}
	else if (!isAdding && SelectedCar[PC] - 1 >= 0) {
		SelectedCar[PC] = SelectedCar[PC] - 1;
	}
}