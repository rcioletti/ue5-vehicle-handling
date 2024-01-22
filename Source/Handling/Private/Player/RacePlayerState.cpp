// Fill out your copyright notice in the Description page of Project Settings.

#include <Player\RacePlayerState.h>
#include <Net\UnrealNetwork.h>

ARacePlayerState::ARacePlayerState() 
{
}

void ARacePlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARacePlayerState, isReady);
	DOREPLIFETIME(ARacePlayerState, SelectedCarIndex);
}