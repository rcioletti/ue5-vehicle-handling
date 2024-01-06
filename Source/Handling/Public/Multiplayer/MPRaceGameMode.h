// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MPRaceGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API AMPRaceGameMode : public AGameMode
{
	GENERATED_BODY()

	AMPRaceGameMode();

	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

public:
	UPROPERTY(Replicated, BlueprintReadWrite)
	bool isWaitingPlayers = false;
};
