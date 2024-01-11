// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameMode.h"
#include <Net\UnrealNetwork.h>
#include <Multiplayer\MPRaceGameState.h>

AMPRaceGameMode::AMPRaceGameMode() {

	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	DefaultPawnClass = nullptr;
	bReplicates = true;
}

void AMPRaceGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

    AMPRaceGameState* MPGameState = GetWorld()->GetGameState<AMPRaceGameState>();

    MPGameState->LastAddedPlayer = Players.Add(NewPlayer);

    MPGameState->OnRep_LastAddedPlayer();

    /*FUniqueNetIdRepl UniqueNetIdRepl;
    if (NewPlayer->IsLocalPlayerController())
    {
        ULocalPlayer* LocalPlayer = NewPlayer->GetLocalPlayer();
        if (IsValid(LocalPlayer))
        {
            UniqueNetIdRepl = LocalPlayer->GetPreferredUniqueNetId();

            GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Valid Local Player netid")));
        }
        else
        {
            UNetConnection* RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
            check(IsValid(RemoteNetConnection));
            UniqueNetIdRepl = RemoteNetConnection->PlayerId;

            GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Not Valid Local Player netid")));
        }
    }
    else
    {
        UNetConnection* RemoteNetConnection = Cast<UNetConnection>(NewPlayer->Player);
        check(IsValid(RemoteNetConnection));
        UniqueNetIdRepl = RemoteNetConnection->PlayerId;

        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Not Locally Controlled")));
    }*/
}
