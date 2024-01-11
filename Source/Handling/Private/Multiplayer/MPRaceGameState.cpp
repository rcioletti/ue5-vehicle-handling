// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameState.h"
#include <Engine.h>
#include <Core\GameData.h>
#include <Net\UnrealNetwork.h>

void AMPRaceGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPRaceGameState, LastAddedPlayer);
}

void AMPRaceGameState::OnRep_LastAddedPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Replicated")));

	UpdateAllDisplayedCars();
}

void AMPRaceGameState::UpdateAllDisplayedCars()
{

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BPCarShowcase, AllCarShowcaseInWorld);

	//FCars* CarData = UGameData::GetInstance()->GetCars()[0];

	for (auto* lol : UGameData::GetInstance()->GetCars()) {

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Car: %s"), *lol->CarModelName.ToString()));
	}

	if (!AllCarShowcaseInWorld.IsEmpty() /** && CarData != nullptr**/) {
		for (int i = 0; i <= LastAddedPlayer; i++) {

			UpdateDisplayedCar(AllCarShowcaseInWorld[i]->GetComponentByClass<USkeletalMeshComponent>(), nullptr);
			
		}
	}
}

void AMPRaceGameState::UpdateDisplayedCar(USkeletalMeshComponent* CarShowcaseSkeletalMeshComponent, USkeletalMesh* CarSkeletalMesh)
{
	CarShowcaseSkeletalMeshComponent->SetSkeletalMeshAsset(CarSkeletalMesh);
}