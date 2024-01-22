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
	
	//virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadOnly)
	int32 PlayerID;

	UFUNCTION(BlueprintCallable)
	bool GetIsServer() { return HasAuthority() ? true : false; };

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SetPlayerID(int32 ID);

	UFUNCTION(BlueprintCallable, Client, Reliable)
	void Client_SetPlayerID(int32 ID);

	UFUNCTION(Server, Reliable)
	void Server_DisplayCarInLobby(int32 CarIndex);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SelectNewCar(bool isAdding);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ToggleIsReady();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_CheckIsEveryoneReady();
};
