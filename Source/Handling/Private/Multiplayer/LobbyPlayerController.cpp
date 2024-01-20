// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/LobbyPlayerController.h"

void ALobbyPlayerController::Server_SetPlayerID_Implementation(int32 ID)
{
	Client_SetPlayerID(ID);
}

void ALobbyPlayerController::Client_SetPlayerID_Implementation(int32 ID)
{
	PlayerID = ID;
}
