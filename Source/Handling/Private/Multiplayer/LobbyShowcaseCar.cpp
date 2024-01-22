// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/LobbyShowcaseCar.h"
#include <Net\UnrealNetwork.h>

ALobbyShowcaseCar::ALobbyShowcaseCar() 
{
	bReplicates = true;

	CarSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarSkeletalMesh"));
	CarSkeletalMeshComponent->SetMobility(EComponentMobility::Static);
}

void ALobbyShowcaseCar::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyShowcaseCar, CarMesh);
}

void ALobbyShowcaseCar::OnRep_SelectedCar()
{
	CarSkeletalMeshComponent->SetSkeletalMesh(CarMesh);
}
