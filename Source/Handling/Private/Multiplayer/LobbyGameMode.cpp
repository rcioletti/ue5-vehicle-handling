// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/LobbyGameMode.h"
#include <Net\UnrealNetwork.h>
#include <Multiplayer\LobbyPlayerController.h>
#include <Multiplayer\RacePlayerState.h>

ALobbyGameMode::ALobbyGameMode() {

	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	DefaultPawnClass = nullptr;
	bReplicates = true;
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

    int32 ServerIndex = Players.Add(NewPlayer);
    
    ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(NewPlayer);

    PC->Server_SetPlayerID(ServerIndex);
	PC->Server_DisplayCarInLobby(0);
}

void ALobbyGameMode::OpenRaceLevel()
{
	UWorld* World = GetWorld();
	World->ServerTravel("RaceTrack?listen&game=/Game/Core/BMPRaceGameMode.BMPRaceGameMode_C");
}

void ALobbyGameMode::CheckEveryoneReady()
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
