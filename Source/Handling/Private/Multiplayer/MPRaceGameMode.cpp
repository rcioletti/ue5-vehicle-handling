// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameMode.h"
#include <Net\UnrealNetwork.h>

AMPRaceGameMode::AMPRaceGameMode() {

	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	DefaultPawnClass = nullptr;
	bReplicates = true;
}

void AMPRaceGameMode::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(AMPRaceGameMode, isWaitingPlayers);
}