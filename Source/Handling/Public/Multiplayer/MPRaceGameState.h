// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MPRaceGameState.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API AMPRaceGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	UPROPERTY(BlueprintReadWRite, EditAnywhere)
	TSubclassOf<AActor> BPCarShowcase;

	//UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LastAddedPlayer)
	//int32 LastAddedPlayer;

	UPROPERTY(BlueprintReadOnly)
	TMap<APlayerController*, int32> SelectedCar;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetNewCarIndex(bool isAdding, APlayerController* PC);

private:

	bool bIsInLobby;

	bool bIsInRace;

};
