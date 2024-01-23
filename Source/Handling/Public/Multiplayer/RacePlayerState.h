// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RacePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API ARacePlayerState : public APlayerState
{
	GENERATED_BODY()

	ARacePlayerState();

	virtual void CopyProperties(APlayerState* PlayerState);
	
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

public:

	UPROPERTY(BlueprintReadOnly, Replicated)
	int32 SelectedCarIndex = 0;

	UPROPERTY(BlueprintReadOnly, Replicated)
	bool isReady = false;
};
