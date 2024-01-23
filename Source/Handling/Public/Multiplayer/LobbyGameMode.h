// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()

	ALobbyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

public:

	UPROPERTY(BlueprintReadWrite)
	TArray<APlayerController*> Players;

	UFUNCTION(BlueprintCallable)
	void OpenRaceLevel();

	UFUNCTION(BlueprintCallable)
	void CheckEveryoneReady();
};
