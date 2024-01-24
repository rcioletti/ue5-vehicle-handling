// Fill out your copyright notice in the Description page of Project Settings.


#include "Multiplayer/MPRaceGameMode.h"
#include <Kismet\GameplayStatics.h>
#include <Multiplayer\RacePlayerState.h>
#include <Core\GameData.h>
#include <Core\RaceGameInstance.h>

AMPRaceGameMode::AMPRaceGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;
	DefaultPawnClass = nullptr;
}

void AMPRaceGameMode::BeginPlay()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AllPlayerStartActor);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Map Name: %s"), *GetWorld()->GetMapName()));
}

void AMPRaceGameMode::GenericPlayerInitialization(AController* Controller)
{
	Super::GenericPlayerInitialization(Controller);

	if (APlayerController* PC = Cast<APlayerController>(Controller)) 
	{
		SpawnPlayer(PC);

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Player Spawned")));
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Failed to cast Controller to Player Controller")));
	}
}

TArray<FTransform> AMPRaceGameMode::FindAllPlayerStart()
{
	TArray<FTransform> AllPlayerStartTransform;

	if (AllPlayerStartActor.Num() <= 0) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AllPlayerStartActor);
	}

	for (AActor* PlayerStartActor : AllPlayerStartActor)
	{
		APlayerStart* PlayerStart = Cast<APlayerStart>(PlayerStartActor);
		AllPlayerStartTransform.Add(PlayerStart->GetTransform());
	}

	return AllPlayerStartTransform;
}

void AMPRaceGameMode::SpawnPlayer(APlayerController* PlayerController)
{
	TArray<FTransform> AllPlayerStartTransform = FindAllPlayerStart();

	if (PlayerController->GetPawn() != nullptr) {
		PlayerController->GetPawn()->Destroy();
	}

	if (PlayerController->PlayerState) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = PlayerController;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FVector SpawnLocation = AllPlayerStartTransform[Cars.Num()].GetLocation() - FVector(0, 0, 90);
		const FRotator SpawnRotation = AllPlayerStartTransform[Cars.Num()].Rotator();

		ARacePlayerState* PS = Cast<ARacePlayerState>(PlayerController->PlayerState);
		URaceGameInstance* GI = Cast<URaceGameInstance>(GetGameInstance());
		
		FCarData* CarData = GI->GetGameData()->GetCars()[PS->SelectedCarIndex];


		ARaceCarPawn* SpawnedPlayerCar = Cast<ARaceCarPawn>(GetWorld()->SpawnActor(CarData->CarPawn, &SpawnLocation, &SpawnRotation, SpawnParams));
		PlayerController->Possess(SpawnedPlayerCar);

		//SpawnedPlayerCar->ChaosWheeledVehicleMovementComponent->SetHandbrakeInput(1.0f);

		Cars.Add(SpawnedPlayerCar);
	}
}