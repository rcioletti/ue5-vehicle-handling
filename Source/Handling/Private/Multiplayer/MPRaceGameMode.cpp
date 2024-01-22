// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameMode.h"
#include <Net\UnrealNetwork.h>
#include <Multiplayer\MPRaceGameState.h>
#include <Multiplayer\LobbyPlayerController.h>
#include <Player\RacePlayerState.h>

AMPRaceGameMode::AMPRaceGameMode() {

	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	DefaultPawnClass = nullptr;
	bReplicates = true;
}

void AMPRaceGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

    int32 ServerIndex = Players.Add(NewPlayer);
    
    ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(NewPlayer);

    PC->Server_SetPlayerID(ServerIndex);
    PC->Server_DisplayCarInLobby(0);
}

void AMPRaceGameMode::OpenRaceLevel()
{
	UWorld* World = GetWorld();
	bUseSeamlessTravel = true;
	World->ServerTravel("/Game/Maps/RaceTrack?listen");
}

void AMPRaceGameMode::CheckEveryoneReady()
{
	bool EveryoneReady = false;

	for (int i = 1; i < Players.Num(); i++) {
		ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(Players[i]);
		ARacePlayerState* PS = Cast<ARacePlayerState>(PC->PlayerState);

		if (PS->isReady) {
			EveryoneReady = true;
		}
		else {
			EveryoneReady = false;
			break;
		}
	}

	if (EveryoneReady) {
		OpenRaceLevel();
	}
}
