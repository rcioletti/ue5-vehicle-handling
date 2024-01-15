// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameState.h"
#include <Engine.h>
#include <Core\GameData.h>
#include <Net\UnrealNetwork.h>
#include <Core\RaceGameInstance.h>

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

	URaceGameInstance* GI = Cast<URaceGameInstance>(GetGameInstance());

	TArray<FCarData*> CarData = GI->GetGameData()->GetCars();

	if (!AllCarShowcaseInWorld.IsEmpty()) {
		for (int i = 0; i <= LastAddedPlayer; i++) {

			UpdateDisplayedCar(AllCarShowcaseInWorld[i]->GetComponentByClass<USkeletalMeshComponent>(), CarData[0]->CarSkeletalMesh);
			
		}
	}
}

void AMPRaceGameState::UpdateDisplayedCar(USkeletalMeshComponent* CarShowcaseSkeletalMeshComponent, USkeletalMesh* CarSkeletalMesh)
{
	CarShowcaseSkeletalMeshComponent->SetSkeletalMeshAsset(CarSkeletalMesh);
}