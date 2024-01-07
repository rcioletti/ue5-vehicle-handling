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

void AMPRaceGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

    FUniqueNetIdRepl UniqueNetIdRepl;
    if (NewPlayer->IsLocalPlayerController())
    {
        ULocalPlayer* LocalPlayer = NewPlayer->GetLocalPlayer();
        if (IsValid(LocalPlayer))
        {
            UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();
        }
        else
        {
            UNetConnection* RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
            check(IsValid(RemoteNetConnection));
            UniqueNetIdRepl = RemoteNetConnection->PlayerId;
        }
    }
    else
    {
        UNetConnection* RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
        check(IsValid(RemoteNetConnection));
        UniqueNetIdRepl = RemoteNetConnection->PlayerId;
    }
}
