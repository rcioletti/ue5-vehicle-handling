// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HANDLING_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerID;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SetPlayerID(int32 ID);

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void Client_SetPlayerID(int32 ID);
};
