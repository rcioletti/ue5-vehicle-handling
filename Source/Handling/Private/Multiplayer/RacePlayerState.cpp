// Fill out your copyright notice in the Description page of Project Settings.

#include <Multiplayer\RacePlayerState.h>
#include <Net\UnrealNetwork.h>

ARacePlayerState::ARacePlayerState() 
{
}

void ARacePlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	
	if (ARacePlayerState* PS = Cast<ARacePlayerState>(PlayerState))
	{
		PS->SelectedCarIndex = SelectedCarIndex;
	}
}

void ARacePlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARacePlayerState, isReady);
	DOREPLIFETIME(ARacePlayerState, SelectedCarIndex);
}