// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameMode.h"

AMPRaceGameMode::AMPRaceGameMode() {

	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	DefaultPawnClass = nullptr;
}