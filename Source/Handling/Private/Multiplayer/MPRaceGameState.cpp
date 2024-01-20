// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameState.h"
#include <Engine.h>
#include <Core\GameData.h>
#include <Net\UnrealNetwork.h>
#include <Core\RaceGameInstance.h>

void AMPRaceGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AMPRaceGameState, LastAddedPlayer);
}

//void AMPRaceGameState::OnRep_LastAddedPlayer()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Replicated")));
//
//	UpdateAllDisplayedCars();
//}

void AMPRaceGameState::SetNewCarIndex(bool isAdding, APlayerController* PC)
{
	if (AllCarShowcaseInWorld.IsEmpty()) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), BPCarShowcase, AllCarShowcaseInWorld);
	}

	URaceGameInstance* GI = Cast<URaceGameInstance>(GetGameInstance());

	TArray<FCarData*> CarData = GI->GetGameData()->GetCars();

	if (isAdding && SelectedCar[PC] + 1 < CarData.Num()) {
		SelectedCar[PC] = SelectedCar[PC] + 1;
	}
	else if (!isAdding && SelectedCar[PC] - 1 >= 0) {
		SelectedCar[PC] = SelectedCar[PC] - 1;
	}

	int32 i = 0;

	for (auto& Elem : SelectedCar) {
		if (Elem.Key == PC) {
			
			if (SelectedCar[PC]) {

				UpdateDisplayedCar(AllCarShowcaseInWorld[i]->GetComponentByClass<USkeletalMeshComponent>(), CarData[SelectedCar[Elem.Key]]->CarSkeletalMesh);
			}
		}

		i++;
	}
}

void AMPRaceGameState::UpdateAllDisplayedCars()
{

	if (AllCarShowcaseInWorld.IsEmpty()) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), BPCarShowcase, AllCarShowcaseInWorld);
	}

	URaceGameInstance* GI = Cast<URaceGameInstance>(GetGameInstance());

	TArray<FCarData*> CarData = GI->GetGameData()->GetCars();

	int32 i = 0;

	for (auto& Elem : SelectedCar) {

		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Element value: %s"), *FString::FromInt(Elem.Value)));

		UpdateDisplayedCar(AllCarShowcaseInWorld[i]->GetComponentByClass<USkeletalMeshComponent>(), CarData[SelectedCar[Elem.Key]]->CarSkeletalMesh);
		i++;
	}
}

void AMPRaceGameState::UpdateDisplayedCar(USkeletalMeshComponent* CarShowcaseSkeletalMeshComponent, USkeletalMesh* CarSkeletalMesh)
{
	CarShowcaseSkeletalMeshComponent->SetSkeletalMeshAsset(CarSkeletalMesh);
}