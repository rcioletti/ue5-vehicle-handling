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

	UPROPERTY()
	TArray<AActor*> AllCarShowcaseInWorld;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LastAddedPlayer)
	int32 LastAddedPlayer;

	UFUNCTION()
	void OnRep_LastAddedPlayer();

	UFUNCTION()
	void UpdateAllDisplayedCars();

	UFUNCTION()
	void UpdateDisplayedCar(USkeletalMeshComponent* CarShowcaseSkeletalMeshComponent, USkeletalMesh* CarSkeletalMesh);

private:

	bool bIsInLobby;

	bool bIsInRace;

};
